/* example to redirect the INPUT of */
/* a program -- usage "prog infile" */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>

int
main(
    int argc,
    char *argv[])
{
    int fd_stdin;

    fd_stdin = open(argv[1],O_RDONLY);

    if (fork() == 0) {
	/* child */
	dup2(fd_stdin,0);
	close(fd_stdin);
	execl("/bin/cat","cat",0);
	perror("/bin/cat");
	_exit(1);
    }
    close(fd_stdin);
    wait(0);
}
