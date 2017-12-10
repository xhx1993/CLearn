#include "apue.h"
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <sys/stat.h>        /* For mode constants */
#define NLOOPS 1000
#define SIZE sizeof(long)

static int
update(long *ptr)
{
	return ((*ptr)++);
}

int
main(void)
{
	int fd, i, counter;
	pid_t pid;
	void *area;
	sem_t *sem1, *sem2;

	if ((fd = open("/dev/zero", O_RDWR)) < 0)
		err_sys("open error");
	if ((area = mmap(0, SIZE, PROT_WRITE | PROT_READ,
		MAP_SHARED, fd, 0)) == MAP_FAILED)
		err_sys("mmap error");
	close(fd);
	
	if ((sem1 = sem_open(".123456", O_CREAT, S_IRWXU, 1)) == SEM_FAILED)
		err_sys("sem_open error");
	sem_unlink(".123456");

	if ((sem2 = sem_open(".1234567", O_CREAT, S_IRWXU, 1)) == SEM_FAILED)
		err_sys("sem_open error");
	sem_unlink(".1234567");

	sem_wait(sem2); //父进程先行`

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid > 0) { // parent 
		for (i = 0; i < NLOOPS; i += 2) {
			sem_wait(sem1);
			if ((counter = update((long *)area)) != i)
				err_quit("parent: expected %d, got %d", i, counter);
			sem_post(sem2);
		}
	} else { // child
		for (i = 1; i < NLOOPS; i += 2) {
			sem_wait(sem2);
			if ((counter = update((long *)area)) != i)
				err_quit("child: expected %d, got %d", i, counter);
			sem_post(sem1);
		}
	}
	sem_close(sem1);
	sem_close(sem2);
	exit(0);
}
