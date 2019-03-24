#include "open.h"

int
pytm_open(char *pts_name, int pts_namesz)
{
    char *ptr;
    int fdm, err;

    if ((fdm = posix_openpt(O_RDWR)) < 0)
        return(-1);
    if (grantpt(fdm) < 0)
        goto errout;
    if (unlockpt(fdm) < 0)
        goto errout;
    if ((ptr = ptsname(fdm)) == NULL)
        goto errout;
errout:
    err = errno;
    close(fdm);
    errno = err;
    return(-1);
}

int
pyts_open(char *pts_name)
{
    int fds;

#if defined(SOLARIS)
    int err, setup;
#endif

    if ((fds = open(pts_name, O_RDWR)) < 0)
        return(-1);

#if defined(SOLARIS)
    /**
     * Check if stream is already set up by autopush faciliy
     */
    if ((setup = ioctl(fds, I_FIND, "ldterm")) < 0)
        goto errout;
    if (setup == 0) {
        if (ioctl(fds, I_PUSH, "ptem") < 0)
            goto errout;
        if (ioctl(fds, I_PUSH, "ldterm") < 0)
            goto errout;
        if (ioctl(fds, I_PUSH, "ttcompact") < 0) {
errout:
            err = errno;
            close(fds);
            errno = err;
            return(-1);
        }
    }
#endif
    return(fds);
}

