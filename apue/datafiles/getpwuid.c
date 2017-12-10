/*
 * The pro test the function :
 *	struct passwd *getpwuid(uid_t uid);
 */
#include "apue.h"
#include <pwd.h>

int main(void)
{	
	uid_t uid = 500;
	struct passwd *pw;

	if ((pw = getpwuid(uid)) == NULL)
		err_sys("getpwuid error");
	
	printf("username: %s\n", pw->pw_name);
	printf("passwd: %s\n", pw->pw_passwd);
	printf("uid: %d\n", pw->pw_uid);
	printf("gid: %d\n", pw->pw_gid);
	printf("description: %s\n", pw->pw_gecos);
	printf("home dir: %s\n", pw->pw_dir);
	printf("shell: %s\n", pw->pw_shell);

	return 0;
}
