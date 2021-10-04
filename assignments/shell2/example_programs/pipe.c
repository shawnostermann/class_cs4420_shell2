/*
 *  pipe.c -- simple program to run the command "cat FILE | wc" 
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

#define PROG1 "/bin/cat"
#define PROG2 "/usr/ucb/wc"

int
main(
    int argc,
    char *argv[])
{
    int fd_pipe[2];

    if (argc != 2) {
	fprintf(stderr,"Usage: pipe2 infile\n"); exit(-1);
    }

    pipe(fd_pipe);

    if (fork() == 0) { /* child 1 */
	dup2(fd_pipe[1],1); /* connect standard output to pipe */
	/* close everything EXCEPT 0,1,2 */
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	execl(PROG1,PROG1,argv[1],0);
	perror(PROG1);
	_exit(1);
    }

    if (fork() == 0) { /* child 2 */
	dup2(fd_pipe[0],0); /* connect standard input to pipe */
	/* close everything EXCEPT 0,1,2 */
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	execl(PROG2,PROG2,0);
	perror(PROG2);
	_exit(1);
    }

    /* close everything EXCEPT 0,1,2 */
    close(fd_pipe[0]);
    close(fd_pipe[1]);

    wait(0); wait(0);

    exit(0);
}
