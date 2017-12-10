#include "apue.h"
#include <sys/wait.h>

char *env_init[] = { "USER=unknown", "PATH=/Users/xuhongxiang/Test/Git/c-learning/apue/proc", NULL };

int main(void)
{
	pid_t pid;

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) { /* specify pathname, specify environment */
		if (execle("/Users/xuhongxiang/Test/Git/c-learning/apue/proc/echoall", "echoall-argv0", "myarg1",
			"MY ARG2", (char *)0, env_init) < 0)
			err_sys("execle error");
	}

	if (waitpid(pid, NULL, 0) < 0)
		err_sys("wait error");

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid == 0) { /* specify filename, inherit environment */
		if (execlp("echoall", "echoall-argv0", "only 1 arg", (char *)0) < 0)
			err_sys("execlp error");
	}
	
	exit(0);
}
