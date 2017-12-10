#include "apue.h"
#include <fcntl.h>
#include <sys/mman.h>


int 
main(int argc, char *argv[])
{
	int fdin, fdout;
	void *src, *dst;

	if (argc != 3)
		err_quit("usage: %s <infile> <outfile>", argv[0]);

	if ((fdin = open(argv[1], O_RDONLY,
		FILE_MODE)) < 0)
		err_sys("can't creat %s\n", argv[1]);
	
	if ((fdout = open(argv[2], O_RDWR | O_CREAT,
		FILE_MODE)) < 0)
		err_sys("can't open %s\n", argv[2]);
	ftruncate(fdout, 20);
#define FILESIZE 30
	
	if ((src = mmap(0, 30, PROT_READ,
		MAP_SHARED, fdin, 0)) == MAP_FAILED)
		err_sys("mmap error for output");
	
	if ((dst = mmap(0, FILESIZE, PROT_READ | PROT_WRITE,
			MAP_SHARED, fdout, 0)) == MAP_FAILED)
		err_sys("mmap error for output");

	memcpy(dst, src, FILESIZE);
	
	munmap(src, 30);
	munmap(dst, FILESIZE);
	exit(0);
}
