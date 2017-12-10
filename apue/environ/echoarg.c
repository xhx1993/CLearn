#include "apue.h"

int main(int argc, char *argv[])
{
	int i;
	
	for (i = 0; i < argc; i++) /* echo all command-line args */
		printf("argv[%d]: %s\n", i, argv[i]);

	printf("-----------------------\n");

	for (i = 0; argv[i] != NULL; i++)
		printf("argv[%d]: %s\n", i, argv[i]);

	exit (0);
}

int main1(int argc, char *argv[])
{
	int i;

	for (i = 0; i < argc; i++)
		printf("argv[%d]: %s\n", i, argv[i]);

	printf("-----------------------\n");

	for (i = 0; argv[i] != NULL; i++)
		printf("argv[%d]: %s\n", i, argv[i]);

	exit(0);
}
