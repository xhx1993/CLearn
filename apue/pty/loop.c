#include "apue.h"

#define BUFFSIZE 512

static void sig_term(int);
static volatile sig_atomic_t sigcaught; /* set by signal  handler */

void
loop(int ptym, int ignoreeof)
{
	pid_t child;
	int nread;
	char buf[BUFFSIZE];

	if ((child = fork()) < 0) {
		err_sys("fork error");
	} else if (child == 0) { /* child copies stdin to stdout */
		for (;;) {
			if ((nread = read(STDIN_FILENO, buf, BUFFSIZE)) < 0)
				err_sys("read error from stdin");
			else if (nread == 0)
				break;
			if (writen(ptym, buf, nread) != nread)
				err_sys("writen error to master pty");
		}

		/*
		 * We always terminate when we encounter an EOF.
		 * But we notify the parent only if ignoreeof is set.		
		 */
		if (ignoreeof == 0)
			kill(getppid(), SIGTERM);
		exit(0);
	}

	/*
     * Parent copies ptym to stdout.
     */
	 if (signal_intr(SIGTERM, sig_term) == SIG_ERR)
		err_sys("signal_intr error for SIGTERM");
	
	for (;;) {
		if ((nread = read(ptym, buf, BUFFSIZE)) <= 0)
			break;
		if (writen(STDOUT_FILENO, buf, nread) != nread)
			err_sys("writen error to stdout");
	}

	if (sigcaught == 0)
		kill(child, SIGTERM);

	/*
     * Parent returns to caller.
     */
}

static void
sig_term(int signo)
{
	sigcaught = 1;
}
		
