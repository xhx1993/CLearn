/*
 * 程序测试使用了追加标志O_APPEND的文件描述符
 * (1) 能否使用lseek在任意位置开始读?
 * (2) 能否用lseek跟新文件中任何一部分的数据?
 */

#include "apue.h"
#include <fcntl.h>


int main(void)
{
	int fd;
	
	char buf[] = "0123456789";
	char readbuf[5] = {0};
	char writebuf[3] = "22";
	
	if ((fd = open("temp", O_RDWR | O_CREAT | O_APPEND, 
			FILE_MODE)) < 0)
		err_sys("open error");
	
	if (write(fd, buf, 10) != 10)
		err_sys("write error");
		
	if (lseek(fd, 3, SEEK_SET) == -1)
		err_sys("lseek error");
	/* offset 3 */
	if (read(fd, readbuf, 3) > 0)
		printf("%s\n", readbuf);
	else
		printf("read error");

	printf("curpos: %ld\n", lseek(fd, 0, SEEK_CUR));

	if (write(fd, writebuf, 2) != 2)
		err_sys("write error 2");
	return 0;
}
