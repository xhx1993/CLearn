/*
 * 用setvbuf实现setbuf
 */

#include "apue.h"
#include <errno.h>

void mysetbuf(FILE *fp, char *buf)
{
	if (fp == NULL)
		err_sys("fp == NULL");
	
	if (buf == NULL) {
		setvbuf(fp, NULL, _IONBF, 0);
	} else {
		setvbuf(fp, buf, _IOFBF, BUFSIZ);
	}
}

int main()
{
	char buf[BUFSIZ];
	errno = 0;
	mysetbuf(stdout, buf);
	if (errno)
		err_sys("mysetbuf error");

	exit (0);
}
