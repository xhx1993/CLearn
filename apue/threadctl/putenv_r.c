#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

extern char **environ;

pthread_mutex_t env_mutex;

static pthread_once_t init_done = PTHREAD_ONCE_INIT;


static void thread_init(void)
{
	pthread_mutexattr_t attr;

	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&env_mutex, &attr);
	pthread_mutexattr_destroy(&attr);	
}

int getkey(const char *string, char *key)
{
	int i, len;

	len = strlen(string);
	for (i = 0; i < len && string[i] != '='; i++)
			key[i] = string[i];
	if (i < len)
		return 0;
	return -1;		
}

int putenv_r(char *string)
{
	int i, len, olen, klen, ret;
	char *key = NULL;

	len = strlen(string);
	key = (char *)malloc(len);
	if ((ret = getkey(string, key)) != 0)
		err_quit("getkey error");
	pthread_mutex_lock(&env_mutex);
	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(key, environ[i], olen) == 0 &&
			environ[i][olen] == '=') // found
		{
			olen = strlen(&environ[i][len + 1]);
			if (olen >= klen)
			{
				strcpy(environ[i], string);
				pthread_mutex_unlock(&lock);
				return (0);
			}
			else
				; //堆分配空间,指针指向这里
		}
	}
	// not found, append the string, 在堆里分配空间
	// 拷贝整张environ数组，然后把新分配的地址加在新数组里
	strcpy(environ[i], string);
	pthread_mutex_unlock(&lock);
	return (0);
} 
