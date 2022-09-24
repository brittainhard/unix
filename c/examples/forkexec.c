#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid == 0){
        printf("I am the child!\n");
        sleep(1);
    } else {
        wait(NULL);
        printf("Child complete\n");
    }
    return 0;
}
