/*
 * The pro creates a hole file
 */

#include "apue.h"
#include <fcntl.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main()
{
	int fd;
	
	if ((fd = creat("file.hole", FILE_MODE)) < 0)
		err_sys("creat err");
	
	if (write(fd, buf1, 10) != 10)
		err_sys("write err");
	/* offset 10 */
	
	if (lseek(fd, 16384, SEEK_SET) == -1)
		err_sys("lseek err");
	/* offset 16384 */

	if (write(fd, buf2, 10) != 10)
		err_sys("write err");
	/* offset 16394 */
	
	return 0;
}
