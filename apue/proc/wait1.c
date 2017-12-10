#include "apue.h"
#include <sys/wait.h>

void
pr_exit1(int status)
{
	if (WIFEXITED(status))
		printf("normal termination, exit status = %d\n",
				WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		printf("abnornal termination, signal number = %d %s\n",
			WTERMSIG(status),
#ifdef WCOREDUMP
			WCOREDUMP(status) ? " (core file generated)" : "");
#else
			jj"");
#endif
	else if (WIFSTOPPED(status))
		printf("child stopped, signal number = %d\n",
			WSTOPSIG(status));
}

int 
main(void)
{
	pid_t pid;
	int status;

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid == 0)  /* child */
		exit(7);

	if (wait(&status) != pid)  /* wait for child */
		err_sys("wait error");
	pr_exit1(status);   /* and print its status */

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid == 0)  /* child */
		abort();   /* generates SIGABRT */

	if (wait(&status) != pid) /* wait for child */
		err_sys("wait error");
	pr_exit1(status);

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid == 0) /* child */
		status /= 0;  /* divide by 0 generates SIGFPE */

	if (wait(&status) != pid) /* wait for child */
		err_sys("wait error");
	pr_exit1(status);   /* and print its status */

	exit(0);
}
