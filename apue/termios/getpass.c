#include <signal.h>
#include <stdio.h>
#include <termios.h>

#define MAX_PASS_LEN 8 /* max #chars for user to enter */

char *
getpass(const char *prompt)
{
	static char buf[MAX_PASS_LEN + 1]; /* null byte at end */
	sigset_t sig, osig;
	struct termios ts, ots;
	FILE *fp;
	char *ptr;
	int c;

	if ((fp = fopen(ctermid(NULL), "r+")) == NULL)
		return (NULL);
	setbuf(fp, NULL);
	
	sigemptyset(&sig);
	sigaddset(&sig, SIGINT);
	sigaddset(&sig, SIGTSTP);
	sigprocmask(SIG_BLOCK, &sig, &osig);

	tcgetattr(fileno(fp), &ts); /* save tty state */
	ots = ts;
	ts.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL);
	tcsetattr(fileno(fp), TCSAFLUSH, &ts);
	fputs(prompt, fp);

	ptr = buf;
	while ((c = getc(fp)) != EOF && c != '\n')
		if (ptr < &buf[MAX_PASS_LEN])
			*ptr++ = c;
	*ptr = 0;   /* null terminate */
	putc('\n', fp);  /* we echo a new line */

	tcsetattr(fileno(fp), TCSAFLUSH, &ots); /* restore TTY state */
	sigprocmask(SIG_SETMASK, &osig, NULL); /* restore mask */
	fclose(fp);   /* doen with /dev/tty */
	return (buf);
}

