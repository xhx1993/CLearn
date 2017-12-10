#include "apue.h"
#include <sys/wait.h>

void pr_info(siginfo_t *infop)
{
	switch (infop->si_code) {
	
	case CLD_EXITED:
		printf("normal termination, exit status = %d\n", infop->si_status);
		break;

	case CLD_KILLED:
		printf("abnormal termination, signal number = %d\n", infop->si_status);
		break;

	case CLD_DUMPED:
		printf("abanormal termination, signal number = %d"
			"  (core file generated)\n", infop->si_status);
		break;

	case CLD_STOPPED:
		printf("child stopped, signal number = %d\n", infop->si_status);
		break;
	default:
		printf("default\n");
	}
}

int 
main(void)
{
	pid_t pid;
	siginfo_t info;

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid == 0)  /* child */
		exit(7);
	memset(&info, 0,  sizeof(siginfo_t));
	if (waitid(P_PID, pid, &info, WEXITED) != 0)
		err_sys("waitid error");
	pr_info(&info);

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid == 0)  // child 
		abort();   // generates SIGABRT 

	if (waitid(P_PID, pid, &info, WEXITED) != 0)
		err_sys("waitid error");
	pr_info(&info);

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid == 0) // child 
		pid /= 0;  // divide by 0 generates SIGFPE 

	if (waitid(P_PID, pid, &info, WEXITED) != 0)
		err_sys("waitid error");
	pr_info(&info);

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid == 0)
		pid /= 0;
	
	if (waitid(P_PID, pid, &info, WEXITED) != 0)
		err_sys("waitid error");
	pr_info(&info);
	exit(0);
}
