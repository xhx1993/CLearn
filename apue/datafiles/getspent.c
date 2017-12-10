/*
 * The pro print contents in /etc/shadow
 */

#include "apue.h"
#include <shadow.h>
#include <errno.h>

int main()
{
	struct spwd *ptr;

	errno = 0;

	setspent();
	while ((ptr = getspent()) != NULL) {
		printf("name: %s, passwd: %s \n", ptr->sp_namp, ptr->sp_pwdp);;
	}
	
	if (errno)
		err_sys("error");

	endspent();
	return 0;
}
