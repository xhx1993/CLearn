/*
 * The pr print the groups of current user.
 */

#include "apue.h"


int main()
{
	int gidsetsize = 16;
	int i, n;
	gid_t grouplist[gidsetsize];
	
	if ((n =getgroups(gidsetsize, grouplist)) == -1)
		err_sys("getgroups error");
	
	for (i = 0; i < n; i++)
		printf("%d ", grouplist[i]);
	
	exit(0);
}
