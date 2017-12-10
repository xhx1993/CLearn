#include "apue.h"
#include <sys/socket.h>
#include <sys/un.h>

int
main(void)
{
	int fd;
	socklen_t size;
	struct sockaddr_un un;

	if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
		err_sys("socket failed");

	un.sun_family = AF_UNIX;
	strcpy(un.sun_path, "foo.socket");
	size = offsetof(struct sockaddr_un, sun_path) + strlen(un.sun_path);
	if (bind(fd, (struct sockaddr *)&un, size) < 0)
		err_sys("bind failed");
	printf("UNIX domain socket bound\n");
	exit(0);
}
