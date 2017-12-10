#include "apue.h"
#include <pwd.h>

static void
my_alarm(int signo)
{
	struct passwd *rootptr;
	
	signal(SIGALRM, my_alarm);

	printf("in signal handler\n");
	//if ((rootptr = getpwnam("root")) == NULL)
	//	err_sys("getpwnam(root) error");
	//else
//		printf("Signal Func get name:%s\n", rootptr->pw_name);
	printf("Hello world\n");
	alarm(1);
}

int 
main(void)
{
	struct passwd *ptr;
	
	signal(SIGALRM, my_alarm);
	alarm(1);

	while (1) {
		if ((ptr = getpwnam("xuhongxiang")) == NULL)
			err_sys("getpwnam error");
		if (strcmp(ptr->pw_name, "xuhongxiang") != 0)
			printf("return value corrupted!, pw_name = %s\n",
				ptr->pw_name);
		else 
			printf("pw_name = %s\n", ptr->pw_name);
	}
}
