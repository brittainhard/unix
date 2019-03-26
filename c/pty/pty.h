#ifndef __PTY_H
#define __PTY_H

#include "apue.h"
#include "open.h"
#include "fork.h"
#include "loop.h"
#include "driver.h"
#include <termios.h>

#ifndef LINUX
#define OPTSTR "+d:einv"
#else
#define OPTSTR "d:einv"
#endif

#endif /* ifndef __PTY_H */
