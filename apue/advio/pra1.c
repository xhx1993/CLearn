#include "apue.h"
#include <fcntl.h>
#include <errno.h>


int 
main(void)
{
	int fd;
	pid_t pid;
	

	if ((fd = open("pra_file", O_RDWR | O_CREAT | O_TRUNC,
				 FILE_MODE)) < 0)
		err_sys("open error");

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) { // child
		if (read_lock(fd, 0, SEEK_SET, 0) != 0)
			err_sys("first read_lock error");
		else
			printf("%ld: get read lock success\n", (long long)getpid());
		while(1)
			;
	} 
	/* let's get the readlock */
	sleep(1);

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) { // child
		
		sleep(2); // let's other get write lock
		
		if (read_lock(fd, 0, SEEK_SET, 0) != 0)
			err_sys("second read_lock error");
		else
			printf("%d: second read_lock success\n", getpid());
		while(1)
			;
	} else { // parent
		printf("%d: try to get write lock\n", getpid());
		if (writew_lock(fd, 0, SEEK_SET, 0) != 0)
			err_sys("write lock error");
		else
			printf("get write lock succsee\n");
	}
	exit(0);
}

