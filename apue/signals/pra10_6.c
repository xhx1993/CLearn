#include "apue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

void write_to_file(char *procname, int fd)
{
	int buf[10];
	int n, num;

	lseek(fd, 0, SEEK_SET);
	memset(buf, 0, 10);
	while ((n = read(fd, buf, sizeof(buf)-1) < 0))
	{
		if (errno == EINTR)
			continue;
		err_sys("read error");
	}
	if (n < 0)
		err_sys("read error");
	num = atoi(buf);
	num += 1;
	lseek(fd, 0, SEEK_SET);
	memset(buf, 0, 10);
	sprintf(buf, "%d", num);
	if (write(fd, buf, strlen(buf)) != strlen(buf))
		printf("write error\n");
	printf("%s %d -> %d\n",procname, num-1, num);
}

void Write(char *name, int fd)
{
	char buf[10];
	int n, num;
	lseek(fd, 0, SEEK_SET);
	if ((n = read(fd, buf, 10)) > 0) {
		num = atoi(buf);
		num++;
		if (num > 20)
			exit(0);
		sprintf(buf, "%d", num);
		lseek(fd, 0, SEEK_SET);
		if (write(fd, buf, strlen(buf)) != strlen(buf))
			printf("write error");
		printf("%s write %d\n", name, num);
	} 
	if (n < 0)
		printf("read error");
}

int 
main(void)
{
	pid_t pid;
	int fd;
	int n = 0;
	char buf[10];
	
	TELL_WAIT();
	if ((fd = open("XXX.txt", O_RDWR | O_CREAT, 
					S_IRUSR | S_IWUSR)) < 0)
		printf("open error");

	sprintf(buf, "%d", n);
	write(fd, buf, strlen(buf));

	if ((pid = fork()) < 0)
		printf("fork error");
	else if (pid == 0) { /* child */
		while (1) {
			WAIT_PARENT();
			write_to_file("child ", fd);
			TELL_PARENT(getppid());
		}
	} else { /* parent */
		while (1) {
			write_to_file("parent", fd);
			TELL_CHILD(pid);
			WAIT_CHILD();
		}
	}
	TELL_WAIT_END();
	exit(0);
}
