#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int 
main(void)
{
	char *str;
	
	str = ctermid(NULL);
	printf("%s\n", str);
	exit(0);
}

