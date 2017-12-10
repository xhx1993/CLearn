#include "apue.h"
#include <sys/msg.h>
#include <sys/wait.h>

struct mymesg {
	long mtype;
	char mtext[512];
};

int 
main(void)
{
	int queue_id;
	pid_t pid;
	char buf[MAXLINE];
	int n;

	queue_id = msgget(IPC_PRIVATE, 0600);
	if (queue_id == -1)
		err_sys("msgget error");

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid > 0) { // parent
		struct mymesg mesg;
		mesg.mtype = 5;
		strncpy(mesg.mtext, "heddllo", n = strlen("heddllo"));
		if (msgsnd(queue_id, &mesg, n, 0) == -1)
			err_sys("msgsnd error");
		
		if (waitpid(pid, NULL, 0) == -1)
			err_sys("waitpid error");

	} else { // child
		if (msgrcv(queue_id, buf, MAXLINE, 0, 0) == -1)
			err_sys("msgrcv error");
		printf("%s\n", (*(struct mymesg *)&buf).mtext);
	}
	exit(0);
}
