/**************************************
 > File Name: ls2.c
 > Author: xhx1993
 > Created Time: 五  4/21 08:21:00 2017
**************************************/

#include "apue.h"
#include <dirent.h>

int main1(int argc, char **argv)
{
	DIR *dp;
	struct dirent *dirp;

	if (argc != 2)
		err_quit("usage: ls directory_name");

	if ((dp = opendir(argv[1])) == NULL)
		err_sys("can't open %s", argv[1]);
	while ((dirp = readdir(dp)) != NULL)
		printf("%s\n", dirp->d_name);
	closedir(dp);
	exit(0);
}


int main(int argc, char **argv)
{
	DIR *dp;
	struct dirent *dirp;

	if (argc != 2)
		err_quit("usage: %s directory_name",argv[0]);

	if ((dp = opendir(argv[1])) == NULL)
		err_sys("can't open dir:%s", argv[1]);

	while ((dirp = readdir(dp)) != NULL)
		printf("%s\n", dirp->d_name);

	closedir(dp);
	exit(0);
}
