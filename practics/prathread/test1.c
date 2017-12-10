#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>

#define BUFSIZE 32

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

static void *thr_fn(void *p)
{
	int fd = -1;
	long long n = 0;
	char buf[BUFSIZE] = "";

	fd = open(p, O_RDWR | O_CREAT, 0664);
	if (fd < 0)
	{
		fprintf(stderr, "open error");
		exit(-1);
	}
	
	pthread_mutex_lock(&mutex);
	read(fd, buf, BUFSIZE);
	lseek(fd, 0, SEEK_SET);
	n = atoll(buf);
	snprintf(buf, BUFSIZE, "%lld\n", ++n);
	write(fd, buf, strlen(buf));
	close(fd);
	pthread_mutex_unlock(&mutex);

	pthread_exit(NULL);
}

int main(int argc, char **argv)
{
	pthread_t tids[20];
	int i = 0, ret;

	if (argc < 2)
	{
		fprintf(stderr, "Usage %s <filename>\n", argv[0]);
		return -1;
	}

	for (i = 0; i < 20; i++) 
	{
		ret =pthread_create(tids + i, NULL, thr_fn, argv[1]);
		if (ret != 0)
		{
			fprintf(stderr, "pthread_create error");
			return -2;
		}
	}
	
	for (i = 0; i < 20; i++)
		pthread_join(tids[i], NULL);
	
	return 0;
}
