#ifndef __OPEN_H
#define __OPEN_H

#include "apue.h"
#include <errno.h>
#include <fcntl.h>

#if defined(SOLARIS)
#include <stropts.h>
#endif

int ptym_open(char *ptsname, int ptsnamesz);
int ptys_open(char *pts_name);

#endif /* ifndef __OPEN_H */
