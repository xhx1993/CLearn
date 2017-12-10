#include "apue.h"

int sig2str1(int signo, char *str)
{
	char *p;
	p = strsignal(signo);
	if (strcpy(str, p) == NULL)
		return -1;
	return 0;
}

int 
sig2str(int signo, char *str)
{/*
	const char *p;
	char *q;
	p = sys_siglist[signo];
	q = str;

	while ( *p != '0')
		*q++ = *p++;

	return 0;
*/	
	char *p;
	p = strsignal(signo);
	if (strcpy(str, p) == NULL)
		return -1;
	return 0;
}

int 
main(int argc, char *argv[])
{
	if (argc != 2)
		err_quit("usage: sig2str <signo>");
	
	int signo;
	char buf[1024];

	signo = atoi(argv[1]);
	if (sig2str(signo, buf) != 0)
		err_sys("sig2str error");	
	
	printf("signo: %d  signal: %s\n", signo, buf);
	exit(0);
}
