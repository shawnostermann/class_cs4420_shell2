/* Shawn's fstat program */
/* Version 1.0 - Thu Jun 10, 1999 */
/* Version 1.0.1 - Nov 18, 2021 - updated to modern standards */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/statvfs.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <time.h>


static char *FileModeString(mode_t mode);
static char *OwnerString(uid_t owner);
static char *GroupString(uid_t group);
static char *TimeString(time_t date);
static void RunStat(char *filename);

/* nice macros */
#define ITYPE_IS(MODE,TYPE) ((MODE & IFMT) == (TYPE))

static int lookatlink = 0;

int
main(
    int argc,
    char *argv[])
{

    if (argc == 1) {
		fprintf(stderr,"usage: %s [-l] file ...\n", argv[0]);
		exit(-1);
    }
    
    for (int i=1; i < argc; ++i) {
		if (strcmp(argv[i],"-l") == 0) {
			lookatlink = 1;
			continue;
		}
		RunStat(argv[i]);
    }

    exit(0);
}


void
RunStat(
    char *filename)
{
    struct stat statbuf;
    int ret;
    int ftype;

    if (lookatlink)
		ret = lstat(filename,&statbuf);
    else
		ret = stat(filename,&statbuf);

    if (ret != 0) {
		perror(filename);
		return;
    }


    ftype = statbuf.st_mode & S_IFMT;

    printf("File: %s  <%s>\n",
	   filename,
	   (ftype == S_IFIFO)?"fifo":
	   (ftype == S_IFCHR)?"character special":
	   (ftype == S_IFDIR)?"directory":
	   (ftype == S_IFBLK)?"block special":
	   (ftype == S_IFREG)?"regular file":
	   (ftype == S_IFLNK)?"symbolic link":
	   (ftype == S_IFSOCK)?"socket":
	   "UNKNOWN/OTHER");

    printf("Mode: %s   owner: %s(%d)  group: %s(%d)\n",
	   FileModeString(statbuf.st_mode),
	   OwnerString(statbuf.st_uid), (int)statbuf.st_uid,
	   GroupString(statbuf.st_gid), (int)statbuf.st_gid);

    printf("Phys: inode %lld, %u link, %lld blocks\n",
	   statbuf.st_ino,
	   statbuf.st_nlink,
	   statbuf.st_blocks);

    printf("Size: %lld bytes, I/O block size %d\n",
	   statbuf.st_size,
	   statbuf.st_blksize);
	   
    printf("Access: %s\n", TimeString(statbuf.st_atime));
    printf("Change: %s\n", TimeString(statbuf.st_mtime));
    printf("Status: %s\n", TimeString(statbuf.st_ctime));
}


static char *
FileModeString(
    mode_t mode)
{
    static char buf[100];
    
    sprintf(buf,
	    "%c%c%c%c%c%c%c%c%c",

	    (mode & (S_IREAD))? 'r':'-',
	    (mode & (S_IWRITE))?'w':'-',
	    (mode & (S_IEXEC))?
  	      ((mode & S_ISUID)?'s':'x'):'-',

	    (mode & (S_IREAD>>3))? 'r':'-',
	    (mode & (S_IWRITE>>3))?'w':'-',
	    (mode & (S_IEXEC>>3))?
  	      ((mode & S_ISGID)?'s':'x'):'-',

	    (mode & (S_IREAD>>6))? 'r':'-',
	    (mode & (S_IWRITE>>6))?'w':'-',
	    (mode & (S_IEXEC>>6))? 'x':'-'

	);

    return(buf);
}


static char *
TimeString(
    time_t date)
{
    static char buf[100];
    char *pch;

    pch = ctime(&date);
    pch[24] = '\00';

    sprintf(buf,"%s", pch);

    return(buf);
}


static char *
OwnerString(
    uid_t owner)
{
    struct passwd *ppass;

    if ((ppass = getpwuid(owner)) == NULL)
		return("NOUSER");

    return(strdup(ppass->pw_name));
}

static char *
GroupString(
    uid_t group)
{
    struct group *pgroup;

    if ((pgroup = getgrgid(group)) == NULL)
		return("NOGROUP");

    return(strdup(pgroup->gr_name));
}
