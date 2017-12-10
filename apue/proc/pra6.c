#include "apue.h"

int 
main(void)
{
	pid_t pid;
	int status;	

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) { /* child */
		exit(0); /* zombile */
	}

	/* parent */
	sleep(2);   /* wait for child to exit */
	
	if ((status = system("ps")) < 0)
		err_sys("system error");
	pr_exit(status);
	exit(0);
}
