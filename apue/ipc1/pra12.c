#include "apue.h"
#include <sys/msg.h>

#define NLOOPS 5

struct mymesg {
	long mtype;
	char mtext[512];
};

int
main(void)
{
	int i, msqid;
    key_t key;
	struct mymesg mesg;

	if ((key = ftok("/home/xhx1993/apue/ipc1/pra12.c", 3)) == (key_t)-1)
		err_sys("ftok error");

	for (i = 0; i < NLOOPS; i++) {
		if ((msqid = msgget(key, 0600 | IPC_CREAT)) == -1)
			err_sys("msgget error");
		printf("msqid: %d\n", msqid);
		if (msgctl(msqid, IPC_RMID, 0) == -1)
			err_sys("msgctl IPC_RMID error");
	}

	for (i = 0; i < NLOOPS; i++) {
		if ((msqid = msgget(IPC_PRIVATE, S_IRUSR | S_IWUSR)) == -1)
			err_sys("mseget error");
		mesg.mtype = 1;
		strcpy(mesg.mtext, "hello");
		if (msgsnd(msqid, &mesg, 5, 0) == -1)
			err_sys("msgsnd error");
	}
	exit(0);
}
