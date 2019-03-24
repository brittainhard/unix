#ifndef __FORK_H
#define __FORK_H

#include "apue.h"
#include <termios.h>

pid_t pty_fork(int *ptrfdm, char *slave_name, int slave_namesz);

#endif /* ifndef __FORK_H */
