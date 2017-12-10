#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXLINE  1024

int main(void)
{
	time_t t;
	struct tm *tmp;
	char buf[MAXLINE];

	time(&t);
	if ((tmp = localtime(&t)) == NULL)
		printf("localtime error");

	if (strftime(buf, MAXLINE, "%a %b %d %T %Z %Y", tmp) == 0)
		printf("strftime error");
	else
		printf("%s\n", buf);

	exit(0);
}
