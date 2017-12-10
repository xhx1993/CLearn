#include "apue.h"

static void
sig_alrm(int signo)
{
	// nothing to do, just returning wakes up sigsuspend()
}

unsigned int 
sleep(unsigned int seconds)
{
	unsigned int unslept;
	struct sigaction act, oact;
	sigset_t alrmmask, oldmask, wakemask;
	
	act.sa_handler = sig_alrm;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	if (sigaction(SIGALRM, &act, &oact) < 0)
		err_sys("sigaction(SIGALRM) error");
	
	sigemptyset(&alrmmask);
	sigaddset(&alrmmask, SIGALRM);
	if (sigprocmask(SIG_BLOCK, &alrmmask, &oldmask) < 0)
		err_sys("sigprocmask(SIG_BLOCK) error");

	alarm(seconds);

	wakemask = alrmmask;
	sigdelset(&wakemask, SIGALRM);

	if (sigsuspend(&wakemask) != -1)
		err_sys("sigsuspend error");
		
	unslept = alarm(0);

	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		err_sys("sigprocmask(SIG_SETMASK) error");
	if (sigaction(SIGALRM, &oact, NULL) < 0)
		err_sys("sigaction(SIGALRM) error");

	return unslept;
}
