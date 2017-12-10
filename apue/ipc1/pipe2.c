#include "apue.h"
#include <sys/wait.h>

#define DEF_PAGER "/usr/bin/more"	/* default paper program */

int main(int argc, char *argv[])
{
	int fd[2];
	pid_t pid;
	FILE *fp = NULL;
	int n;
	char line[MAXLINE];
	char *pager, *argv0;

	if (argc != 2)
		err_sys("usage: a.out <pathname>");
	
	if ((fp = fopen(argv[1], "r")) == NULL)
		err_sys("can't open %s", argv[1]);

	if (pipe(fd) < 0)
		err_sys("pipe error");

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid > 0) { // parent
		close(fd[0]);

		while (fgets(line, MAXLINE, fp) != NULL) {
			n = strlen(line);
			if (write(fd[1], line, n) != n)
				err_sys("write error to pipe");
		}
		if (ferror(fp))
			err_sys("fgets error");

		fclose(fp);
		close(fd[1]);

		if (waitpid(pid, NULL, 0) < 0)
			err_sys("waitpid error");
		exit(0);
	} else { // child
		close(fd[1]);

		if (fd[0] != STDIN_FILENO) {
			if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO)
				err_sys("dup2 error to stdin");
			close(fd[0]);
		}
		
		/* get arguments for execl() */
		if ((pager = getenv("PAGER")) == NULL)
			pager = DEF_PAGER; /* mac pager=less */
		/*argv 0 == filename */
		if ((argv0 = strrchr(pager, '/')) != NULL)
			argv0++;
		else
			argv0 = pager;
		printf("pager:%s, argv0:%s\n", pager, argv0);

		if (execlp(pager, argv0, (char *)0) < 0)
			err_sys("execlp error for less");

		//if (execl(pager, argv0, (char *)0) < 0)
		//	err_sys("execl error for /usr/bin/more");
	}
	exit(0);
}
