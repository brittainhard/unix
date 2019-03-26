#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
    pid_t pid;
    int status;

    pid = fork();
    printf("%d\n", pid);
    waitpid(pid, &status, 0);
    printf("%d\n", pid);
    return 0;
}
