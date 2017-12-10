#include <stdio.h>
#include <stdlib.h>

#define MOVEUP(x) printf("\033[%dA", (x))
#define MOVEDOWN(x) printf("\033[%dB", (x))
#define MOVELEFT(y) printf("\033[%dD", (y))
#define MOVERIGHT(y) printf("\033[%dC", (y))

void printLine(int count)
{
	int i;
	
	if (count <= 0)
		return;

	for (i = 0; i < count; i++)
	{
		MOVEUP(1);
		printf("|");
		MOVELEFT(1);
	}
	MOVEDOWN(count);
}

int main()
{
	int i;

	for (i = 0; i < 9; i++)
		printf("     aaaa\n");
	printf("     aaaa");	

	printLine(8);
	exit(0);
}
