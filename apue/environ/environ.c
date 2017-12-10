#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int main()
{
	char *ptr = NULL;
	
	if (putenv("HOME=/home/xhx1993/apue") != 0)
		printf("putenv error");
	
	ptr = getenv("HOME");
	printf("HOME: %s\n", ptr);
/*
	int i = 0; 
	for (i = 0; environ[i] != NULL; i++)
		printf("%s\n", environ[i]);
*/
	return 0;
}
