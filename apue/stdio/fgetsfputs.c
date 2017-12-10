#include "apue.h"


int main(void)
{
	char   buf[MAXLINE];
	
	printf("MAXLINE: %d\n", MAXLINE);

	while (fgets(buf, MAXLINE, stdin) != NULL)
		if (fputs(buf, stdout) == EOF)
			err_sys("fputs error");

	if (ferror(stdin))
		err_sys("fgets error");
	
	exit(0);	
}
