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

    int protection = PROT_READ | PROT_WRITE;
    
    // MAP_SHARED to share memory between parent and child.
    // MAP_ANONYMOUS to prevent third-party processes from finding it.
    int visibility = MAP_SHARED | MAP_ANONYMOUS;
    // memcpy(shared, parent, sizeof(parent)); 
    Potato *shared = mmap(NULL, 128, protection, visibility, -1, 0);
    
    shared->a = 1;

    int a = 0;
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
