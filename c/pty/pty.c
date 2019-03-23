#include <termios.h>

#ifndef LINUX
#define OPTSTR "+d:einv"
#else
#define OPTSTR "d:einv"
#endif

int
main(int argc, char *argv[])
{
    return 0;
}
