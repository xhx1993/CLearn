#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <poll.h>
#include <unistd.h>


int 
main(void)
{
	struct pollfd pollfd;
	struct pollfd fdarray[10];
	int retval;
	char buf[100];


	/* initializer struct pollfd */
	pollfd.fd = STDIN_FILENO;
	pollfd.events |= POLLRDNORM;
	
	fdarray[0] = pollfd;

	while (1) {
		retval = poll(fdarray, 1, 5000);
		if (retval == -1) {
			perror("poll error");
		}
		if (fdarray[0].revents | POLLRDNORM) {
			memset(buf, 0, 100);
			read(fdarray[0].fd, buf, 100);
			printf("read data: %s", buf);	
		} else {
			printf("No data within five seconds.\n");
		}
	}
	exit(0);
}

