#include "apue.h"
#include <fcntl.h>
#include <syslog.h>

int main()
{
	FILE *fp;
	char *logname;
	
	daemonize("getlog");
	logname = getlogin();
	fp = fopen("/tmp/getlog.out","w");
	// fp = fopen("getlog.out", "w"); 错误，此时当前目录为根目录，没有权限创建文件
	if (fp != NULL)
	{
		if (logname == NULL)
			fprintf(fp, "no login name\n");
		else
			fprintf(fp, "login name: %s\n", logname);
	}
	exit(0);	
}
