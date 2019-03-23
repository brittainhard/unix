#include <stdio.h>

/**
 * This is the guaranteed limit of possible open files.
 */

int
main(int argc, const char *argv[])
{
    printf("%d\n", FOPEN_MAX - 1);
    return 0;
}
