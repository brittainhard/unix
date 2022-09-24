#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <string.h>

int
main(int argc, char *argv[])
{
    pid_t pid;
    typedef struct Potatoes {
        int a;
    } Potato;

    Potato *shared = malloc(sizeof(Potato));

    shared->a = 1;

    pid = fork();
    if (pid < 0) {
        ;
        return 1;
    } else if (pid == 0){
        printf("Child read %d\n", shared->a);
        shared->a = 2;
        printf("Child wrote %d\n", shared->a);
    } else {
        printf("Parent read %d\n", shared->a);
        sleep(1);
        printf("Parent read later %d\n", shared->a);
    }
    return 0;
}
