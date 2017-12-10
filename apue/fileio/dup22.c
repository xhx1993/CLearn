#include "apue.h"
#include <fcntl.h>

int dup22(int fd, int old_fd)
{
	int fda, i = 0;
	int *arry = (int*)malloc(sizeof(int) * old_fd);
	memset(arry, 0, old_fd);
	
	close(old_fd);
	//每次都分配最小的，直到old_fd
	do 
	{
		fda = dup(fd);
		arry[fda] = 1;
	}while(fda < old_fd);
	
	//关闭之前分配成功的
	for (i = 0; i < old_fd; i++)
		if (arry[i] == 1)
			close(i);

	if (fda != old_fd)
		return -1;
	return fda;
}

int main(void)
{
	int fd3, fd4, fd5;
	if ((fd3 = open("somefile", O_RDWR | O_CREAT, FILE_MODE)) < 0)
		err_sys("open error");
	
	if ((fd4 = open("somefile1", O_RDWR | O_CREAT, FILE_MODE)) < 0)
		err_sys("open error");

	//让fd5指向标准输出
	fd5 = dup(STDOUT_FILENO);
	close(STDOUT_FILENO);
	
	//让newfd复制fd5，并且值为fd4
	int newfd = dup22(fd5, fd4);
	printf("newfd: %d\n", newfd);
	
	write(fd4, "this", 4);
	return 0;
}

