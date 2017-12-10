#include "apue.h"
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>

#define CLI_PATH "/var/tmp/"
#define CLI_PERM S_IRWXU    /* rwx for user only */

/*
 * Create a client endpoint and connect to a server.
 * Return fd if all OK, < 0 on error.
 */
int
cli_conn(const char *name)
{
	int fd, err, rval, size;
	int dol_unlink = 0;
	struct sockaddr_un sun, un;
	
	if (strlen(name) >= sizeof(un.sun_path)) {
		errno = ENAMETOOLONG;
		return (-1);
	}
	
	/* create a unix domain stream socket */
	if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) 
		return (-2);
	
	/* fill socket address structure with our address */
	memset(&un, 0, sizeof(un));
	un.sun_family = AF_UNIX;
	sprintf(un.sun_path, "%s%05ld", CLI_PATH, (long)getpid());
	size = offsetof(struct sockaddr_un, sun_path) + strlen(un.sun_path);
	
	unlink(un.sun_path); /* in case it already exists */
	if (bind(fd, (struct sockaddr *)&un, size) < 0) {
		rval = -3;
		goto errout;
	}
	if (chmod(un.sun_path, CLI_PERM) < 0) {
		rval = -4;
		do_unlink = 1;
		goto errout;
	}

	/* fill socket address structure with server's address */
	memset(&sun, 0, sizeof(sun));
	sun.sun_family = AF_UNIX;
	strcpy(sun.sun_path, name);
	size = offsetof(struct sockaddr_un, sun_path) + strlen(sun.sun_path);
	if (connect(fd, (struct sockaddr *)&un, size) < 0) {
		rval = -5;
		do_unlink = 1;
		goto errout;
	}
	return (fd);

errout:
	err = errno;
	close(fd);
	if (do_unlink)
		unlink(un.sun_path);
	errno = err;
	return (rval);
}
