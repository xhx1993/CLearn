#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void myabort()
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
	kill(getpid(), SIGABRT);

	printf("My Program Caught SIGABRT signal\n");
	fflush(NULL);
	action.sa_handler = SIG_DFL;
	sigaction(SIGABRT, &action, NULL);
	sigprocmask(SIG_SETMASK, &mask, NULL);
	kill(getpid(), SIGABRT);
	exit(1);
}

static void sig_myabort(int signo)
{
	printf("SIGABRT caughted\n");
}

int main()
{
//	signal(SIGABRT, sig_myabort);
	myabort();
	return 0;
}
