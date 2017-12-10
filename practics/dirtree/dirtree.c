#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <limits.h>
#include <errno.h>

//光标移动函数
#define MOVEUP(x) printf("\033[%dA", (x))
#define MOVEDOWN(x) printf("\033[%dB", (x))
#define MOVELEFT(y) printf("\033[%dD", (y))
#define MOVERIGHT(y) printf("\033[%dC", (y))

int line;    //记录当前打印的行数

/*
 * 往上画竖线，然后光标回到原位置
 *
 */
void printLine(int count)
{
	int i;
	
	if (count <= 0)
		return;
	for (i = 0; i < count; i++)
	{
		MOVEUP(1);
		printf("|");
		MOVELEFT(1);
	}
	MOVEDOWN(count);
	printf("count: %d ", count);
}


/*
 * 判断是否目录项
 * 是返回 1
 * 否则返回 0
 */
int is_directory(const char *filename)
{
	struct stat statbuf;
	
	if (lstat(filename, &statbuf) < 0)
	{
		printf("lstat %s error: %s\n", filename, strerror(errno));
		exit(-1);
	}
	
	return (S_ISDIR(statbuf.st_mode));
}

/*
 * 读取一个非 . 和 .. 的目录项， 空返回NULL
 */
struct dirent *read_dir(DIR *dp)
{
	struct dirent *dirp = NULL;
	
	dirp = readdir(dp);     
	// 循环， 直到读到一个非 . 和 .. 的项或者空
	while (dirp != NULL && (strcmp(dirp->d_name, ".") == 0 || 
			strcmp(dirp->d_name, "..") == 0))  
	{
			dirp = readdir(dp);/* ignore dot and dot-dot */
	}		
	
	return dirp;
}

/*
 * 递归打印出目录树
 */
int print_dirtree(const char *filename, int level)
{
	struct dirent *dirp, *dirpnext;
	DIR	*dp;
	int ret = 0, i;
	int top = line;    //top 记录第一个子项的行数
	
	if ((dp = opendir(filename)) == NULL) /* can't read directory */
	{
		ret = -1;
		printf("can't open directory %s : %s\n", filename, strerror(errno));
		return ret;
	}
    //	考虑readdir读取的都是相对路径，因此需要更改当前目录
    //	必须先opendir, 然后再chdir
	if (chdir(filename) < 0)
	{
		ret = -2;
		printf("chdir %s error: %s\n", filename, strerror(errno));
		return ret;
	}
	
	// 使用两个指针变量，遍历完所有子目录项
	// 使用dirpnext 判断当前目录项是否为最后一个
	dirp = NULL;
	dirpnext = read_dir(dp);
	while ((dirp = dirpnext) != NULL) {
		dirpnext = read_dir(dp);
			    
		for (i = 0; i < level; i++)  //使用空格打印出格式
			printf("    ");
		if (dirpnext == NULL)   //如果是最后一个目录， 往上画竖线, 光标回到原位
			printLine(line - top);
		line++;
		// 打印出当前目录项名称
		printf("|--%s\n", dirp->d_name);  //打印出子项名
		
		//如果是目录， 则对该目录进行递归处理
		if (is_directory(dirp->d_name)) { 
			if ((ret = print_dirtree(dirp->d_name, level+1)) != 0)
				return ret;
		}
	}
	// 更改当前目录为上一级目录
	if (chdir("..") < 0)
	{
		ret = -3;
		printf("chdir .. error: %s\n", strerror(errno));
		return ret;
	}
	if (closedir(dp) < 0)
	{
		ret = -4;
		printf("can't close directory %s : %s\n", filename, strerror(errno));
		return ret;
	}
	
	return ret;
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("usage: ./dirtree <pathname>\n");
		exit(-1);
	}
	printf("%s\n", argv[1]);
	if (print_dirtree(argv[1], 0) != 0)
		printf("print_dirtree error\n");
		
	exit(0);
}
