/*
 * The pro copy file1 to file2
 */

#include "apue.h"

#define BUFFSIZE 4096

int main()
{
	int n;
	char buf[BUFFSIZE];

	if ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
		if (write(STDOUT_FILENO, buf, n) != n)
			err_sys("write err");

	if (n < 0)
		err_sys("read err");
	
	return 0;
}
