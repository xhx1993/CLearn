#include "apue.h"

/*
 * Used when we had planned to send an fd using send_fd(),
 * but encountered an error instead. We sen the error back
 * using the send_fd()/recv_fd() protocol.
 */
int
send_err(int fd, int errcode, const char *msg)
{
	int n;
	
	if ((n = strlen(msg)) > 0)
		if (write(fd, msg, n) != n) /* send the error_msg */
			return (-1);

	if (errcode >= 0)
		errcode = -1;  
	
	if (send_fd(fd, errcode) < 0)
		return (-2);

	return (0);
}
