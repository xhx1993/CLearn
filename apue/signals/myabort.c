#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void
myabort(void)
{
	sigset_t mask;
	struct sigaction action;

	sigaction(SIGABRT, NULL, &action);
	if (action.sa_handler == SIG_IGN) {
		action.sa_handler = SIG_DFL;
		sigaction(SIGABRT, &action, NULL);
	}
	if (action.sa_handler == SIG_DFL)
		fflush(NULL);

	sigfillset(&mask);
	sigdelset(&mask, SIGABRT);
	sigprocmask(SIG_SETMASK, &mask, NULL);
	printf("dd\n");
	if (0 != kill(getpid(), SIGABRT)) {
		printf("kill error");
	} else
		printf(" kill success\n");
	printf("捕捉了sigabrt,才会执行这里。不捕捉，上面就结束了\n");
	
	fflush(NULL);
	action.sa_handler = SIG_DFL;
	sigaction(SIGABRT, &action, NULL);
	sigprocmask(SIG_SETMASK, &mask, NULL);
	kill(getpid(), SIGABRT);
	exit(1);
}

static void
sig_abort(int signo)
{
	printf("here is sig_abort");
}

int
main(void)
{
	signal(SIGABRT, sig_abort);
	myabort();
}

