/*
 * The pro tests function dup and dup2
 */

#include "apue.h"
#include <fcntl.h>

int main1()
{
	int fd, savafd;

	if ((fd = creat("temp", FILE_MODE)) < 0)
		err_sys("creat error");

	//savafd == 标准输出
	savafd = dup(STDOUT_FILENO);
	
	//stdout_fileno 指向fd
	dup2(fd, STDOUT_FILENO);

	write(savafd, "stdout", 6);
	write(STDOUT_FILENO, "somefile", 8);

	return 0;
}

int main()
{
	int fd, savafd;
	
	if ((fd = creat("temp", FILE_MODE)) < 0)
		err_sys("creat error");

	savafd = dup(STDOUT_FILENO);
	
	dup2(fd, STDOUT_FILENO);
	write(savafd, "stdout", 6);
	write(STDOUT_FILENO, "somefile", 8);

	return 0;
}
