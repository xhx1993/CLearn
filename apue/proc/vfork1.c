#include "apue.h"

int globvar = 6; /* external variable in initialized data */

int main(void)
{
	int var;   /* automatic variable on the stack */
	pid_t pid;

	var = 88;
	printf("before vfork\n"); /* we don't flush stdio */
	if ((pid = vfork()) < 0) {
		err_sys("vfork error");
	} else if (pid == 0) {  /* child */
		globvar++;  /* modify parent's variables */
		var++;
		_exit(0);
	}

	/* parent continues here */
	int ret = 0;
	ret = printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar,
		var);
	if (ret == -1)
		fprintf(stderr, "printf return value: %d\n", ret);
	exit(0);
}
