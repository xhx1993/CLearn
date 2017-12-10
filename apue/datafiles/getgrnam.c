/*
 * get group info by name, and print group users' name
 */

#include "apue.h"
#include <grp.h>


int main()
{
	struct group *gptr;
	char name[] = "bin";

	if ((gptr = getgrnam(name)) == NULL)
		err_sys("getgrnam error");
		
	printf("grname: %s\n", gptr->gr_name);
	printf("gpasswd: %s\n", gptr->gr_passwd);
	printf("gid: %d\n", gptr->gr_gid);
	
	// print group users' name
	int i = 0;
	char **grmem = gptr->gr_mem;

	printf("group user:\n");
	while (grmem[i] != NULL) {
		printf("%s\n", grmem[i++]);
	}

	return 0;
}
