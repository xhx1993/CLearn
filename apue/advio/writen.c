#include "apue.h"

ssize_t
writen(int fd, void *ptr, size_t n) 
{
	size_t nleft;
	size_t nwrite;

	nleft = n;
	while (nleft > 0) {
		if ((nwrite = write(fd, ptr, nleft)) < 0) {
			if (nleft == n)
				return (-1);   /* error, return -1 */
			else
				break;       /* error, return amount write so far */
		} else if (nwrite == 0) {
			break;     /* EOF */
		}
		nleft -= nwrite;
		ptr += nwrite;
	}
	return (n - nleft);
}
