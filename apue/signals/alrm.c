#include "apue.h"

int counts;
unsigned int seconds;

static void 
sig_alrm(int signo)
{
	counts--;
	if (counts > 0) {
		alarm(seconds);
	}
}

static void
sig_alrm2(int signo)
{
	counts--;
	if (counts > 0) {
		alarm(seconds);
	}
}

unsigned int myalrm2(unsigned s, int n)
{
	counts = n;
	seconds = s;

	if (signal(SIGALRM, sig_alrm2) == SIG_ERR)
		err_sys("signal(SIGALRM) error");
	if (counts > 0)
		alarm(seconds);
	while (counts)
		pause();
	printf("all time: %d s\n", s*n);
}

unsigned int
myalrm(unsigned s, int n)
{
	counts = n;
	seconds = s;
	
	if (signal(SIGALRM, sig_alrm) == SIG_ERR)
		err_sys("signal(SIGALRM) error");

	if (counts > 0)
		alarm(seconds);	
	while (counts)
		pause();
	//unslept = alarm(0) + counts * s;
	printf("all time: %d s\n", s * n);
}

int main(void)
{
	myalrm2(2,5);
	return 0;
}

int 
main1(void)
{
	myalrm(2, 5); //each alarm times 2 seconds, and 5 alarms.
	return 0;
}
