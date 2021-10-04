/* example of interpreting wait */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int
main(
    int argc, char *argv[])
{
    int ret,pid;

    if (argc != 2) {
	fprintf(stderr,"Usage: %s filename\n", argv[0]);
	exit(-1);
    }
    
    if (fork() == 0) {
        /* child */
        execl("/bin/cat","cat",argv[1],NULL);
        perror("/bin/cat");
        _exit(1);
    }

    pid = wait(&ret);
    printf("Child pid %d had exit status %d (actually %d)\n",
	   pid, ret, ret>>8);

    exit(0);
}
