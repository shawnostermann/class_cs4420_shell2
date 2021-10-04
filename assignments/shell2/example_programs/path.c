/* 
 * path.c - print my PATH
 */

#include <stdio.h>
#include <stdlib.h>


int
main(
    int argc,
    char *argv[])
{
    char *path;

    path = getenv("PATH");

    printf("PATH is '%s'\n",
	   path?path:"<undefined>");

    exit(0);
}
