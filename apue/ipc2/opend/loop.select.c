#include "opend.h"
#include <sys/select.h>

void
loop(void)
{
	int listenfd, clifd;
	int rval, i, nr;
	int maxi, maxfd;
	uid_t uid;
	fd_set rset, allset;
	char buf[MAXLINE];

	/* obtain fd to listen for client request on */
	if ((listenfd = serv_listen(CS_OPEN)) < 0) 
		log_sys("serv_listen error");

	FD_ZERO(&allset);
	FD_SET(listenfd, &allset);
	maxfd = listenfd;
	maxi = -1;
	
	for (;;) {
		rset = allset;              /* rset get modified each time around */
		rval = select(maxfd + 1, &rset, NULL, NULL, NULL);
		if (rval < 0) 
			log_sys("select error");

		if (FD_ISSET(listenfd, &rset)) {
			/* accept new client request */
			if ((clifd = serv_accept(listenfd, &uid)) < 0)
				log_sys("serv_accept error");
			i = client_add(clifd, uid);
			FD_SET(clifd, &allset);
			if (i > maxi)
				maxi = i;
			if (clifd > maxfd)
				maxfd = clifd;
			log_msg("new connection: uid %d, fd %d", uid, clifd);
			continue;
		}
		for (i = 0; i <= maxi; i++) {
			if (client[i].fd == -1)
				continue;
		
			if (FD_ISSET(client[i].fd, &rset)) {
				/* read argument buffer from client */
				if ((nr = read(client[i].fd, buf, MAXLINE)) < 0) {
					log_sys("read error on fd %d", clifd);
				} else if (nr == 0) {
					log_msg("closed: uid %d, fd %d",
						client[i].uid, clifd);
					client_del(client[i].fd);  /* client has closed cxn */
					FD_CLR(clifd, &allset);
					close(clifd);
				} else {  /* process client's request */
					handler_request(buf, nr, clifd, client[i].uid);
				}
			}	
		}
	}
}
