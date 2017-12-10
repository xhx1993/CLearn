#include "apue.h"
#include <fcntl.h>
#include <sys/mman.h>

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
	int i, counter;
	pid_t pid;
	void *area;

	if ((area = mmap(0, SIZE, PROT_WRITE | PROT_READ,
		MAP_ANON | MAP_SHARED, -1, 0)) == MAP_FAILED)
		err_sys("mmap error");

	TELL_WAIT();

	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid > 0) { // parent 
		for (i = 0; i < NLOOPS; i += 2) {
			if ((counter = update((long *)area)) != i)
				err_quit("parent: expected %d, got %d", i, counter);

			TELL_CHILD(pid);
			WAIT_CHILD();
		}
	} else { // child
		for (i = 1; i < NLOOPS; i += 2) {
			WAIT_PARENT();
			
			if ((counter = update((long *)area)) != i)
				err_quit("child: expected %d, got %d", i, counter);

			TELL_PARENT(getppid());
		}
	}
	exit(0);
}
