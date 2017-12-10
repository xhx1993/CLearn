#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <limits.h>
#include <errno.h>

#define DEPTH 100       //目录树的最大深度
int* stack[DEPTH];      //栈: 竖线(!NULL)  空格(NULL)
int depth;              //记录栈的大小

/*
 * 按格式打印子项: 栈保存格式 + 子项名
 */
void print_name(const char *name)
{
	int i;

	if (depth >= DEPTH)    //超出最大深度
		depth = DEPTH - 1;
	for (i = 0; i < depth; i++)
		if (stack[i] == NULL)
			printf("    ");
		else
			printf("|   ");
	printf("|--%s\n", name);
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
int print_dirtree(const char *filename)
{
	struct dirent *dirp, *dirpnext;
	DIR	*dp;
	int ret = 0;
	
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
	    
		// 打印出当前目录项名称
		print_name(dirp->d_name);
		
		//如果是目录， 则对该目录进行递归处理
		if (is_directory(dirp->d_name)) { 
			// 入栈， dirpnext 为空则代表这是最后一个目录
			// 在打印该项中的子项前，需要入栈 竖线(!NULL) 或 空格(NULL)
			stack[depth++] = (int *)dirpnext;
			if ((ret = print_dirtree(dirp->d_name)) != 0)
				return ret;
		}
	}
	// 处理完一个目录后， 出栈
	depth--;
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
	if (print_dirtree(argv[1]) != 0)
		printf("print_dirtree error\n");
		
	exit(0);
}
