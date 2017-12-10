#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <signal.h>

#include <pthread.h>

pthread_mutex_t mylock = PTHREAD_MUTEX_INITIALIZER;

void whichtype(int type)
{
	switch (type)
	{
	case PTHREAD_MUTEX_NORMAL:
		printf("PTHREAD_MUTEX_NORMAL\n");
		break;
	case PTHREAD_MUTEX_ERRORCHECK:
		printf("PTHREAD_MUTEX_ERRORCHECK\n");
		break;
	case PTHREAD_MUTEX_RECURSIVE:
		printf("PTHREAD_MUTEX_RECURSIVE\n");
		break;
	default:
		printf("unknown type\n");
	}
}
int myfunc() {
	int ret = 0;
	int type = 0;
	pthread_mutexattr_t attr;
	if ((ret = pthread_mutexattr_init(&attr)) != 0)
	{
		printf("pthread_mutexattr_init error: %s\n", strerror(ret));       
		return ret; 
	}
	if ((ret = pthread_mutexattr_gettype(&attr, &type)) != 0)
	{
		printf("gettype error\n");
		return ret;
	}
	whichtype(type);

	if ((ret = pthread_mutexattr_destroy(&attr)) != 0)
	{
		printf("destroy error\n");
		return ret;
	}
    return 0;
}

int main()
{

        myfunc();
		while(1)
			;
        return 0;
}
