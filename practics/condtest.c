#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

static pthread_mutex_t mut_num = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond_num = PTHREAD_COND_INITIALIZER;
static int num = 0;

#define THRNUM 4

static int next(int a)
{
	if (a + 1 == THRNUM)
		return 0;
	return a + 1;
}

void *thr_func(void *arg)
{
	int n = (int)arg;
	int ch = n + 'a';

	while (1)
	{
		pthread_mutex_lock(&mut_num);
		while (n != num)
			pthread_cond_wait(&cond_num, &mut_num);
		
		putchar(ch);
		num = next(n);
		pthread_cond_broadcast(&cond_num);
		pthread_mutex_unlock(&mut_num);
	}
	pthread_exit((void *)0);
}

int main()
{
	int i, err;
	pthread_t tid[THRNUM];

	for (i = 0; i < THRNUM; i++)
	{
		err = pthread_create(tid + i, NULL, thr_func, (void *)i);
		if (err != 0)
		{
			fprintf(stderr, "pthread_create error:%s\n", strerror(errno));
			exit(1);
		}
	}

	alarm(5);
	
	for (i = 0; i < THRNUM; i++)
		pthread_join(tid[i], NULL);

	exit(0);
}
