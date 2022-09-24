#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSIZE 1024

int
main(int argc, char *argv[])
{
    int fd, n;
    char buf[BUFSIZE];
    if ((fd = open("potato.txt", O_RDONLY) < 0)) {
        printf("Failed to open file.\n");
        exit(1);
    }

    while ((n = read(fd, buf, BUFSIZE)) > 0) {
        if (write(STDOUT_FILENO, buf, n) != n) {
            printf("write error\n");
            exit(1);
        }
    }
    printf("Done printing!\n");

    close(fd);
    return 0;
}
