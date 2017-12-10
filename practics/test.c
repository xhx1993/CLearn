#include <stdio.h>
#include <stdlib.h>
/*
int get_bitn(unsigned int n)
{
	int bit = 0;
	while (n)
	{
		if (n & 1)
			bit++;
		n >>= 1;
	}
	return bit;
}
*/

int get_bitn(unsigned int n)
{
	unsigned int res = (n & 0x55555555) + ((n >> 1) & 0x55555555);
	res = (res & 0x33333333) + ((res >> 2) & 0x33333333);
	res = (res & 0x0F0F0F0F) + ((res >> 4) & 0x0F0F0F0F);
	res = (res & 0x00FF00FF) + ((res >> 8) & 0x00FF00FF);
	return ((res & 0x0000FFFF) + ((res >> 16) & 0x0000FFFF));
}

int
main(int argc, char *argv[])
{
	int n;

	if (argc != 2)
	{
		printf("usage: %s <num>", argv[0]);
		return -1;
	}
	n = atoi(argv[1]);
	printf("%d has %d 1s in its binary\n", n, get_bitn(n));
	exit(0);
}
