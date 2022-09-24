#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <string.h>

int
main(int argc, char *argv[])
{
    // Buffer is readable and writeable.
    int protection = PROT_READ | PROT_WRITE;
    
    // MAP_SHARED to share memory between parent and child.
    // MAP_ANONYMOUS to prevent third-party processes from finding it.
    int visibility = MAP_SHARED | MAP_ANONYMOUS;

    char *shared = mmap(NULL, 128, protection, visibility, -1, 0);

    char child[] = "Potato";
    char parent[] = "Apple";

    memcpy(shared, parent, sizeof(parent)); 

    int a = 0;
    pid_t pid = fork();
    if (pid < 0) {
        ;
        return 1;
    } else if (pid == 0){
        printf("Child read %s\n", shared);
        memcpy(shared, child, sizeof(child)); 
        printf("Child wrote %s\n", shared);
    } else {
        printf("Parent read %s\n", shared);
        sleep(1);
        printf("Parent read later %s\n", shared);
    }
    return 0;
}
