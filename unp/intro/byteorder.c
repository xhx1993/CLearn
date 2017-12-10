#include	"unp.h"

int
main1(int argc, char **argv)
{
	union {
	  short  s;
      char   c[sizeof(short)];
    } un;

	un.s = 0x0102;
	printf("%s: ", CPU_VENDOR_OS);
	if (sizeof(short) == 2) {
		if (un.c[0] == 1 && un.c[1] == 2)
			printf("big-endian\n");
		else if (un.c[0] == 2 && un.c[1] == 1)
			printf("little-endian\n");
		else
			printf("unknown\n");
	} else
		printf("sizeof(short) = %d\n", sizeof(short));

	exit(0);
}

int main(int argc, char **argv)
{
	uint32_t i = 0x04030201;
	unsigned char *cp = (unsigned char *)&i;

	if (*cp == 1)
		printf("little-endian\n");
	else if (*cp == 4)
		printf("big-endian\n");
	else
		printf("who knows?\n");
	exit(0);
}
