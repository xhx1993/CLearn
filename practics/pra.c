#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[])
{
	
	int n = atoi(argv[1]);
	int i;
	int data = 1 << 31;

	if (n < 0)
	{
		n = ~n + 1;
		n = n | data;
	}

	for (i = 0; i < 32; i++) 
	{
		if (data & (n << i))
			putchar('1');
		else
			putchar('0');
	}
	printf("\n");
	return 0;
}
