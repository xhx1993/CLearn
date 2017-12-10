#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#define THRNUM 4

static pthread_mutex_t mut_num = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond_num = PTHREAD_COND_INITIALIZER;
static int num = 0;

static int next(int a)
{
	if (a + 1 == THRNUM)
		return 0;
	return a + 1;
}

void *thr_func(void *arg)
{
	int i = (int)arg;
	char ch = i + 'a';

	while (1)
	{
		//先抢锁,能抢到锁就可以获得打印的机会
		pthread_mutex_lock(&mut_num);
		while (num != i)
		{
			//抢到锁但是发现不应该自己打印,那就释放出锁在让出调度器
			//让别人尝试抢锁
			pthread_cond_wait(&cond_num, &mut_num);
		}
		putchar(ch);
		num = next(num);
		/* 
         * 自己打印完了，通知别人你们抢锁吧
         * 因为不知道下一个应该运行的线程是谁,
         * 所以采用惊群的方式把他们全都唤醒,
         * 让他们自己检测是不是该自己运行了
         */
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
		//直接启动4个线程,让他们自己判断是否应该运行，而不用提前锁住它们
		err = pthread_create(tid + i, NULL, thr_func, (void *)i);
		if (err)
		{
			fprintf(stderr, "pthread_create(): %s\n", strerror(err));
			exit(1);
		}
	}

	alarm(5);

	for (i = 0; i < THRNUM; i++)
		pthread_join(tid[i], NULL);

	exit(0);
}
