#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void
print_signal(int signo)
{
	psignal(signo, "SIGNAL: ");
}

int main()
{
	sigset_t mask, omask, zeromask;
	sigemptyset(&zeromask);
	sigemptyset(&mask);
	sigaddset(&mask, SIGABRT);
	sigaddset(&mask, SIGKILL);
	sigaddset(&mask, SIGQUIT);
	sigaddset(&mask, SIGTERM);
	sigaddset(&mask, SIGINT);
	signal(SIGABRT,print_signal);
	signal(SIGKILL, print_signal);
	signal(SIGQUIT, print_signal);
	signal(SIGTERM, print_signal);
	signal(SIGINT, print_signal);
	if (sigprocmask(SIG_SETMASK, &mask, &omask) < 0) {
		printf("sigprocmask error\n");
		return -1;
	}

	while (1) {
		sigsuspend(&zeromask);
	}

	return 0;
}
