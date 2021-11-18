#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>

int main(
    int argc,
    char *argv[])
{
    DIR *dp;
    struct dirent *dirp;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s directory_name\n", argv[0]);
        exit(-1);
    }

    if ((dp = opendir(argv[1])) == NULL) {
        perror(argv[1]);
        exit(-1);
    }

    while ((dirp = readdir(dp)) != NULL)
        printf("%s\n", dirp->d_name);

    if (closedir(dp) == -1)
        perror("closedir");

    exit(0);
}
