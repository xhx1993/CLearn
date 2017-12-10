#include "apue.h"
#include <errno.h>

static void
sig_hup(int signo)
{
	printf("SIGHUP received, pid = %ld\n", (long)getpid());
}

static void pr_ids(char *name)
{
	printf("%s: pid = %ld, ppid = %ld, pgrp = %ld, tpgrp = %ld\n",
		name, (long)getpid(), (long)getppid(), (long)getpgrp(),
		(long)tcgetpgrp(STDIN_FILENO));
	fflush(stdout);
}

static void sig_hup1(int signo)
{
	printf("SIGHUP received, pid = %ld\n", (long)getpid());
}

static void pr_ids2(char *name)
{
	printf("%s: pid = %ld, ppid = %ld, pgrp = %ld, tpgrp = %ld\n",
			name, (long)getpid(), (long)getppid(), (long)getgprp(),
			(long)tcgetpgrp(STDIN_FILENO));
	fflush(stdout);
}

int 
main1(void)
{	
	char c;
	pid_t pid;
	
	pr_ids("parent");
	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid > 0) { /* parent */
		sleep(5);   /* sleep to let child stop itself */
	} else { /* child */
		pr_ids("child");
		signal(SIGHUP, sig_hup);
		kill(getpid(), SIGTSTP);
		pr_ids("child"); /* printf only if we're continued */
		if (read(STDIN_FILENO, &c, 1) != 1)
			printf("read error %d on controlling TTY\n", errno);
	}
	exit(0);
}
int main()
{
	char c;
	pid_t pid;

	pr_ids("parent");
	if ((pid = fork())<0) {
		err_sys("fork error");
	} else if (pid > 0) { /* parend */
		sleep(5);
	} else {
		pr_ids("child");
		signal(SIGHUP, sig_hup);
		kill(getpid(), SIGTSTP);
		pr_ids("child");
		if (read(STDIN_FILENO, &c, 1) != 1)
			printf("read error %d on controlling TTY\n", errno);
	}
	exit(0);
}
