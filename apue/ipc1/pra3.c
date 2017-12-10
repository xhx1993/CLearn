#include "apue.h"
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
	FILE *fp;

	if (argc != 2)
		err_quit("usage a.out <cmd>");
	
	if ((fp = popen(argv[1], "w")) == NULL)
		err_sys("popen error");

	if (fputs("hello", fp) == EOF)
		err_sys("fputs error");

	if (pclose(fp) == -1)
		err_sys("pclose error");
	
	exit(0);
}
