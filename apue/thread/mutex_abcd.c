#include "apue.h"
#include <pthread.h>

pthread_mutex_t a = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t b = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t c = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t d = PTHREAD_MUTEX_INITIALIZER;

void *
thr_fn1(void *arg)
{
	while (1) {
		pthread_mutex_lock(&a);
		printf("a");
		pthread_mutex_unlock(&b);
	}
	return ((void *)0);
}

void *
thr_fn2(void *arg)
{
	while (1) {
		pthread_mutex_lock(&b);
		printf("b");
		pthread_mutex_unlock(&c);
	}
	return ((void *)0);
}

void *
thr_fn3(void *arg)
{
	while (1) {
		pthread_mutex_lock(&c);
		printf("c");
		pthread_mutex_unlock(&d);
	}
	return ((void *)0);
}

void *
thr_fn4(void *arg)
{
	while (1) {
		pthread_mutex_lock(&d);
		printf("d");
		pthread_mutex_unlock(&a);
	}
	return ((void *)0);
}

int
main(void)
{
	int ret;
	pthread_t tid1, tid2, tid3, tid4;

	//init mutex_t
	pthread_mutex_lock(&a);
	pthread_mutex_lock(&b);
	pthread_mutex_lock(&c);
	pthread_mutex_lock(&d);

	//create threads
	if ((ret = pthread_create(&tid1, NULL, thr_fn1, NULL)) != 0)
		err_exit(ret, "can't create thread 1");
	if ((ret = pthread_create(&tid2, NULL, thr_fn2, NULL)) != 0)
		err_exit(ret, "can't create thread 2");
	if ((ret = pthread_create(&tid3, NULL, thr_fn3, NULL)) != 0)
		err_exit(ret, "can't create thread 3");
	if ((ret = pthread_create(&tid4, NULL, thr_fn4, NULL)) != 0)
		err_exit(ret, "can't create thread 4");

	//start
	pthread_mutex_unlock(&a);
	
	alarm(5);

	// end
	if ((ret = pthread_join(tid1, NULL)) != 0)
		err_exit(ret, "can't join with tid1");
	if ((ret = pthread_join(tid2, NULL)) != 0)
		err_exit(ret, "can't join with tid2");
	if ((ret = pthread_join(tid3, NULL)) != 0)
		err_exit(ret, "can't join with tid3");
	if ((ret = pthread_join(tid4, NULL)) != 0)
		err_exit(ret, "can't join with tid4");
	
	exit(0);
}
