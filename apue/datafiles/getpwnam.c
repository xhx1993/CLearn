/*
 * The pro implement the function of getpwnam
 */

#include "apue.h"
#include <pwd.h>

struct passwd *
mygetpwnam(const char *name)
{
	struct passwd *ptr;

	setpwent();
	while ((ptr = getpwent()) != NULL)
		if (strcmp(name, ptr->pw_name) == 0)
			break;		// found a match
	endpwent();
	return (ptr);  /* ptr is NULL if no match found */
}

int main(void)
{
	char name[] = "xuhongxiang";
	struct passwd *ptr;

	if ((ptr = mygetpwnam(name)) == NULL)
		err_sys("mygetpwnam error");

	printf("username: %s\n", ptr->pw_name);
	return 0;
}


