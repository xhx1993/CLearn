/**************************************
 > File Name: myshell1.c
 > Author: xhx1993
 > Created Time: 六  4/22 09:44:10 2017
**************************************/
#include "apue.h"
#include <stdio.h>

static void sig_ini(int);

int main()
{
	char buf[MAXLINE];
	pid_t pid;
	int status;
	
	/*捕捉信号*/
	if (signal(SIGINT, sig_ini) == SIG_ERR)
		err_sys("signal error");

	printf("%% ");
	while (fgets(buf, MAXLINE, stdin) != NULL) {
		if (buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] = 0;
		if ((pid = fork()) < 0) {
			err_sys("fork error");
		} else if (pid == 0) { /* child */
			execlp(buf, buf, (char *)0);
			err_ret("couldn't execute: %s", buf);
			exit(127);
		}
		/* parent */
		if ((pid = waitpid(pid, &status, 0)) < 0)
			err_sys("waitpid error");
		printf("%% ");
	}
	exit(0);
}

void sig_ini(int signo)
{
	printf("interrupt\n%%");
}
