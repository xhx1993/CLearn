#include "apue.h"
#include <pthread.h>
#include <sys/socket.h>
#include <sys/msg.h>
#include <poll.h>


#define NQ 3
#define QKEY 0x123

#define MAXMSZ 512
struct mymesg {
	long mtype;
	char mtext[MAXMSZ];
};

struct thread_arg {
	int fd;
	int qid;
};

void *
thr_fn(void *arg) 
{
	int fd, n;
	int qid;
	struct mymesg m;
	struct thread_arg *ta;

	ta = (struct thread_arg *)arg;
	fd = ta->fd;
	qid = ta->qid;
	for (;;) {
		memset(&m, 0, sizeof(m));
		if ((n = msgrcv(qid, &m, MAXMSZ, 0, MSG_NOERROR)) < 0)
			err_sys("msgrcv error");
		if (write(fd, m.mtext, n) != n)
			err_sys("write error");
	}
}

int
main(void)
{
	int i,n;
	int fd[2];
	int qid[NQ];
	pthread_t tid[NQ];
	struct thread_arg targ[NQ];
	struct pollfd pfd[NQ];
	char buf[MAXMSZ];

	for (i = 0; i < NQ; i++) {
		if ((qid[i] = msgget((QKEY + i), IPC_CREAT | 0666)) < 0)
			err_sys("msgget error");
		printf("queue ID %d is %d\n", i, qid[i]);

		if (socketpair(AF_UNIX, SOCK_DGRAM, 0, fd) < 0)
			err_sys("socketpair error");
		targ[i].fd = fd[0];
		targ[i].qid = qid[i];	
		pfd[i].fd = fd[1];
		pfd[i].events = POLLIN;
		if (pthread_create(tid+i, NULL,	thr_fn, targ+i) < 0)
			err_sys("pthread_create error");
	}

	while (1) {
		if (poll(pfd, NQ, -1) < 0)
			err_sys("poll error");
		for (i = 0; i < NQ; i++) {
			if (pfd[i].revents & POLLIN) {
				if ((n = read(pfd[i].fd, buf, MAXMSZ)) < 0)
					err_sys("read error");
				buf[n] = 0;
				printf("queue id %d, message %s\n", qid[i], buf);
			}
		}
	}
	exit(0);
}
