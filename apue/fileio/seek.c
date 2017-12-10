/*
 * The pro test whether lseek is effective to stdin 
 */
#include "apue.h"

int main1(void)
{
	off_t currpos;
	if ((currpos = lseek(STDIN_FILENO, 0, SEEK_CUR)) == -1)
		printf("cannot seek\n");
	else
		printf("seek OK\n");
	printf("currpos is %ld\n", currpos);
	exit(0);
}

int main(void)
{
	off_t currpos;
	if ((currpos = lseek(STDIN_FILENO, 0, SEEK_CUR)) == -1)
		printf("cannot seek\n");
	else
		printf("seek OK\n");
	printf("currpos is %lld\n", currpos);
	exit(0);
}
