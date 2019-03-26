#include "loop.h"

#define BUFFSIZE 512

static void sig_term(int);
static volatile sig_atomic_t sigcaught;

void
loop(int ptym, int ignoreeof)
{
    pid_t child;
    int nread;
    char buf[BUFFSIZE];

    if ((child = fork()) < 0) {
        err_sys("Fork error.");
    } else if (child == 0) {
        for (;;) {
            if ((nread = read(STDIN_FILENO, buf, BUFFSIZE)) < 0)
                err_sys("read error from stdin.");
            else if (nread == 0)
                break; // EOF, means we are done.
            if (writen(ptym, buf, nread) != nread)
                err_sys("writen error to master pty");
        }
        /**
         * Always terminate when encountering an EOF on stdin, but notify parent
         * only if the ignoreeof is 0.
         */
        if (ignoreeof == 0)
            kill(getppid(), SIGTERM);
        exit(0);
    }
    /**
     * Parent copies ptym to stdout.
     */
    if (signal_intr(SIGTERM, sig_term) == SIG_ERR)
        err_sys("signal_intr error for SIGTERM");

    for (;;) {
        if ((nread = read(ptym, buf, BUFFSIZE)) <= 0)
            break; // Signal caught, error, or EOF
        if (writen(STDOUT_FILENO, buf, nread) != nread)
            err_sys("writen error to stdout");
    }

    /**
     * There are three ways to get here: sig_term() below caught the SIGTERM
     * from the child, we read an EOF on the pty master (which means we have to
     * signal the child to stop), or an error.
     */
    if (sigcaught == 0) // Tell child if it didn't send us the signal.
        kill(child, SIGTERM);
    /**
     * Parent returns to caller.
     */
}

static void
sig_term(int signo)
{
    sigcaught = 1;
}
