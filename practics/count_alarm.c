#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


long long count = 0;
static volatile int flag = 1;

void alarm_handler(int s)
{
	flag = 0;
}

int main(void)
{
	signal(SIGALRM, alarm_handler);
	alarm(5);

	flag = 1;

	while (flag)
	{
		count++;
	}
	
	printf("%lld\n", count);
	return 0;
}
