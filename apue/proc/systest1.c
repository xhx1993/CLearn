#include "apue.h"
#include <sys/wait.h>

int 
main(int argc, char *argv[])
{
	if (argc != 2)
		err_quit("usage: systest1 cmd");

	int status;
	
	if ((status = system(argv[1])) < 0)
		err_sys("system() error");
	
	pr_exit(status);

	exit(0);
}
