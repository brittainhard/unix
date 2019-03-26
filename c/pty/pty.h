#ifndef __PTY_H
#define __PTY_H

#include "open.h"
#include "fork.h"
#include "apue.h"
#include <termios.h>

#ifndef LINUX
#define OPTSTR "+d:einv"
#else
#define OPTSTR "d:einv"
#endif

#endif /* ifndef __PTY_H */
