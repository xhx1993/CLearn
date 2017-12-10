#include "apue.h"

#define BUFFSIZE 1024

int main()
{
	if (symlink("/no/such/file", "myfile") < 0)
		err_sys("symlink error");
	
	char buf[BUFFSIZE];
	ssize_t n;
	
	memset(buf, 0, BUFFSIZE);

	if ((n = readlink("myfile", buf, BUFFSIZE)) > 0)
		printf("syslink file content: %s\n", buf);
	
	if (n < 0)
		err_sys("readlink error");
	
	return 0;
}
