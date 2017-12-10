#include "apue.h"
#include <dirent.h>
#include <limits.h>

/* function type that is called for each filename */
typedef int Myfunc(const char *, const struct stat *, int);

static Myfunc myfunc;
static int	  myftw(char *, Myfunc *);
static int	  dopath(Myfunc *, char *);

static long nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;

int main(int argc, char *argv[])
{
	int ret; 
		
	if (argc != 2)
		err_quit("usage: ftw <starting-filename>");

	ret = myftw(argv[1], myfunc); /* does it all */

	ntot = nreg + ndir + nblk + nchr + nfifo + nslink + nsock;

	if (ntot == 0)
		ntot = 1; /* avoid divide  by 0; print 0 for all counts */

	printf("regular files  = %7ld, %5.2f %%\n", nreg,
	  nreg*100.0/ntot);
	printf("directories    = %7ld, %5.2f %%\n", ndir,
	  ndir*100.0/ntot);
	printf("block special  = %7ld, %5.2f %%\n", nblk,
	  nblk*100.0/ntot);
	printf("char special   = %7ld, %5.2f %%\n", nchr,
	  nchr*100.0/ntot);
	printf("FIFOs          = %7ld, %5.2f %%\n", nfifo,
	  nfifo*100.0/ntot);
	printf("symbolic links = %7ld, %5.2f %%\n", nslink,
	  nslink*100.0/ntot);
	printf("sockets        = %7ld, %5.2f %%\n", nsock,
	  nsock*100.0/ntot);
	
	return ret;
}


/*
 * Descend through the hierarchy, starting at "filename".
 * The caller's func() is called for every file.
 */
#define FTW_F 1	/* file other than directory */
#define FTW_D 2 /* directory */
#define FTW_DNR 3 /* directory that can't be read */
#define FTW_NS  4 /* file that we can't stat */

static int	/* we return whatever func() returns */
myftw(char *filename, Myfunc *func)
{
	return (dopath(func, filename));
}


static int
myfunc(const char *filename, const struct stat *statptr, int type)
{
	switch (type) {
		case FTW_F:
			switch (statptr->st_mode & S_IFMT) {	
				case S_IFREG: nreg++; break;
				case S_IFBLK: nblk++; break;
				case S_IFCHR: nchr++; break;
				case S_IFIFO: nfifo++; break;
				case S_IFLNK: nslink++; break;
				case S_IFSOCK: nsock++; break;
				case S_IFDIR: /* directories should have type = FTW_D */
					err_dump("for S_IFDIR for %s", filename);
			}
			break;
		case FTW_D:
			ndir++;	
			break;
		case FTW_DNR:
			err_ret("can't read directory %s", filename);
			break;
		case FTW_NS:
			err_ret("stat error for %s", filename);
			break;
		default:
			err_dump("unknown type %d for filename %s", type, filename);
	}
	return 0;
}

/*
 * Descend through the hierarchy, starting at "filename".
 * If "filename" is anything other than a directory, we lstat() it,
 * call func(), and return. For a directory, we call ourself
 * recursively for each name in the directory.
 */
static int dopath(Myfunc *func, char *filename)
{
	struct stat statbuf;
	struct dirent *dirp;
	DIR	*dp;
	int ret;
	
	if (lstat(filename, &statbuf) < 0) /* stat error */
		return (func(filename, &statbuf, FTW_NS));
	if (S_ISDIR(statbuf.st_mode) == 0) /* not a directory */
		return (func(filename, &statbuf, FTW_F));

	/*
	 * It's a directory. First call func() for the directory,
	 * then process each filename in the directory.
	 */
	if ((ret = func(filename, &statbuf, FTW_D)) != 0)
		return ret; 

	if ((dp = opendir(filename)) == NULL) /* can't read directory */
		return (func(filename, &statbuf, FTW_DNR));
	
	chdir(filename);

	while ((dirp = readdir(dp)) != NULL) {	
		if (strcmp(dirp->d_name, ".") == 0 || 
			strcmp(dirp->d_name, "..") == 0)
			continue; /* ignore dot and dot-dot */
		if ((ret = dopath(func, dirp->d_name)) != 0) /* recursive */
			break; /* time to leave; */
	}
	chdir("..");
		
	if (closedir(dp) < 0)
		err_ret("can't close directory %s", filename);
	return ret;
}
