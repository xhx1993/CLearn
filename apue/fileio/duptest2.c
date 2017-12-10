#include "apue.h"
#include <fcntl.h>

int main1(void)
{
	int fd, sava_fd;
	char msg[] = "This is a test\n";

	if ((fd = open("somefile", O_RDWR | O_CREAT | O_TRUNC, FILE_MODE)) < 0)
		err_sys("open error");

	sava_fd = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	//sava_fd 执行stdout, STDOUT_FILENO 指向fd
	
	write(STDOUT_FILENO, msg, strlen(msg));
	dup2(sava_fd, STDOUT_FILENO);
	write(STDOUT_FILENO, msg, strlen(msg));
	close(sava_fd);
	return 0;
}

int main(void)
{
	int fd, save_fd;
	char msg[] = "This is a test\n";

	if ((fd = open("somefile", O_RDWR | O_CREAT | O_TRUNC, FILE_MODE)) < 0)
		err_sys("open error");

	save_fd = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	write(STDOUT_FILENO, msg, strlen(msg));
	dup2(save_fd, STDOUT_FILENO);
	write(STDOUT_FILENO, msg, strlen(msg));
	close(save_fd);
	return 0;
}
