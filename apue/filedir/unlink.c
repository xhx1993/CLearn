/*
 * The pro open an file, then unlink it, the pro sleep for 15 sec.
 */

#include "apue.h"
#include <fcntl.h>

int main(void)
{
	if (open("tempfile", O_RDWR) < 0)
		err_sys("open error");
	
	if (unlink("tempfile") < 0)
		err_sys("unlink error");
	
	printf("file unlinked\n");
	sleep(15);
	printf("done\n");
	return 0;
}
