#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static void int_handler(int s)
{
	write(1, "!", 1);
}	

int main()
{
	int i, j;
	sigset_t nmask, omask, smask;

	signal(SIGINT, int_handler);

	sigemptyset(&nmask);
	sigaddset(&nmask, SIGINT);
	sigprocmask(SIG_BLOCK, &nmask, &omask); //屏蔽SIGINT

	smask = omask;
	sigdelset(&smask, SIGINT);

	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 5; j++)
		{
			write(1, "*", 1);
			sleep(1);
		}
		write(1, "\n", 1);
		sigsuspend(&smask);
	}
	
	sigprocmask(SIG_SETMASK, &omask, NULL);
	return 0;
}
