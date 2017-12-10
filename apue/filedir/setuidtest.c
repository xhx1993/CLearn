/*
 * the pro test whether file /usr/bin/passwd setuid bit is set
 */

#include "apue.h"

int main()
{
	struct stat buf;
	
	if (stat("/usr/bin/passwd", &buf) < 0)
		err_sys("stat error");
		
	if (S_ISUID & buf.st_mode)
		printf("setuid is OK\n");
	else
		printf("setuid is Error\n");

	return 0;
}
