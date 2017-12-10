#include "apue.h"
#include <pthread.h>

pthread_mutex_t qlock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t qready = PTHREAD_COND_INITIALIZER;
int num = 1;

void *
thr_func(void *arg)
{
	int i = (int)arg;
	char ch = 'a' + i;
	
	for (;;)
	{
		pthread_mutex_lock(&qlock);
		while (num != i) {
			pthread_cond_wait(&qready, &qlock);
		}
		putchar(ch);
		if (++num > 4)
			num = 1;
		pthread_mutex_unlock(&qlock);			
		pthread_cond_broadcast(&qready);
	}
	return ((void *)0);
}

int
main(void)
{
	int ret;
	pthread_t tid[4];

	//create threads
	if ((ret = pthread_create(tid + 0, NULL, thr_func, (void *)1)) != 0)
		err_exit(ret, "can't create thread 1");
	if ((ret = pthread_create(tid + 1, NULL, thr_func, (void *)2)) != 0)
		err_exit(ret, "can't create thread 2");
	if ((ret = pthread_create(tid + 2, NULL, thr_func, (void *)3)) != 0)
		err_exit(ret, "can't create thread 3");
	if ((ret = pthread_create(tid + 3, NULL, thr_func, (void *)4)) != 0)
		err_exit(ret, "can't create thread 4");

	alarm(5);

	// end
	if ((ret = pthread_join(tid[0], NULL)) != 0)
		err_exit(ret, "can't join with tid1");
	if ((ret = pthread_join(tid[1], NULL)) != 0)
		err_exit(ret, "can't join with tid2");
	if ((ret = pthread_join(tid[2], NULL)) != 0)
		err_exit(ret, "can't join with tid3");
	if ((ret = pthread_join(tid[3], NULL)) != 0)
		err_exit(ret, "can't join with tid4");
	
	exit(0);
}
