#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/time.h>
#include <sys/types.h>

#include <unistd.h>

int 
main(void)
{	
	fd_set rfds;
	struct timeval tv;
	int retval;
	char buf[100];
	
	while (1) {
		/* Watch stdin (fd 0) to see when it has input. */
		FD_ZERO(&rfds);
		FD_SET(STDIN_FILENO, &rfds);
		
		/* Wait up to five seconds. */
		tv.tv_sec = 5;
		tv.tv_usec = 0;

		retval = select(1, &rfds, NULL, NULL, &tv);
		/* Don't rely on the value of tv now */
		
		if (retval == -1)
			perror("select()");
		else if (retval) {
			printf("Data is available now.\n");
			memset(buf, 0, 100);
			read(STDIN_FILENO, buf, 100);
			printf("read data: %s", buf);
		} else 
			printf("No data within five seconds.\n");
	}
	exit(0);
}
	
