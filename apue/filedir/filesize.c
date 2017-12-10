#include "apue.h"
#include <fcntl.h>


int main(int argc, char *argv[])
{
	struct stat buf;
	
	if (argc != 2)
		err_sys("usage: filesize <file>");

	if (lstat(argv[1], &buf) < 0)
		err_sys("lsat error");
	else
		printf("file %s size_t is %ld\n", argv[1], buf.st_size);
	
	return 0;
}
