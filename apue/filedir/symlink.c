#include "apue.h"

int main(void)
{
	if (symlink("/no/such/file", "myfile") < 0)
		err_sys("symlink error");

	char buf[1024];
	ssize_t n;
	
	if ((n = readlink("myfile", buf, 1024)) > 0)
		printf("link content: %s\n", buf);

	if (n < 0)
		err_sys("readlink error");
	
	return 0;
}
