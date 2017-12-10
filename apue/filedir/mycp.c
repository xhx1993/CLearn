/*
 * The pro implement the function cp, but don't cp the zero of a hole file
 */

#include "apue.h"
#include <fcntl.h>

#define BUFFSIZE 4096

int main(int argc, char *argv[])
{
	int ffd, tfd;
	int n, i;
	char readbuf[BUFFSIZE];

	if (argc != 3)
		err_sys("usage: mycp <from> <to>");
	
	if ((ffd = open(argv[1], O_RDONLY)) < 0)
		err_sys("open error");

	if ((tfd = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, FILE_MODE)) < 0)
		err_sys("open error");

	while ((n = read(ffd, readbuf, BUFFSIZE)) > 0)
	{
		for (i = 0; i < n; i++)
			if (readbuf[i] != 0)
				if (write(tfd, &readbuf[i], 1) != 1)
					err_sys("write error");
	}
	
	if (n < 0)
		err_sys("read error");
	
	return 0;
}
