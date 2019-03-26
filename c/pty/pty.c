#include "pty.h"

static void set_noecho(int fd);

int
main(int argc, char *argv[])
{
    int fdm, c, ignoreeof, interactive, noecho, verbose;
    pid_t pid;
    char *driver;
    char slave_name[20];
    struct termios orig_termios;
    struct winsize size;

    interactive = isatty(STDIN_FILENO);
    ifnoreeof = 0;
    noecho = 0;
    verbose = 0;
    driver = NULL;

    opterr = 0;
    while ((c = getopt(argc, argv, OPTSTR)) != EOF) {
        switch (c) {
            case 'd':
                driver = optarg;
                break;
            case 'e':
                noecho = 1;
                break;
            case 'i':
                ifnoreeof = 1;
                break;
            case 'n':
                interactive = 0;
                break;
            case 'v':
                verbose = 1;
                break;
            case '?':
                err_quit("unrecognized option -%c", optopt);
        }
    }

    if (optind >= argc)
        err_quit("usage: pty [ -d driver -einv ] program [ arg ... ]");
    if (interactive) { // Fetch current termios and window size.
        if (tcgetattr(STDIN_FILENO, &orig_termios) < 0)
            err_sys("tcgetattr error on stdin");
        if (ioctl(STDIN_FILENO, TIOCGWINSZ, (char *) &size) < 0)
            err_sys("TIOCGWINSZ error.");
        pid = pty_fork(&fdm, slave_name, sizeof(slave_name),
            &orig_termios, &size);
    } else {
        pid = pty_fork(&fdm, slave_name, sizeof(slave_name),
            NULL, NULL);
    }

    if (pid < 0) {
        err_sys("Fork error.");
    } else if (pid == 0) {
        if (noecho)
            set_noecho(STDIN_FILENO);

        if (execvp(argv[optind], &arg[optind]) < 0)
            err_sys("Can't execute: %s", argv[optind]);
    }

    if (verbose) {
        fprintf(stderr, "Slave name = %s\n", slave_name);
        if (driver != NULL)
            fprintf(stderr, "driver = %s\n", driver);
    }

    if (interactive && driver == NULL) {
        if (tty_raw(STDIN_FILENO) < 0) // User's tty to raw mode
            err_sys("tty raw error");
        if (atexit(tty_atexit) < 0)
            err_sys("atexit error");
    }

    if (driver)
        do_driver(driver);
    
    loop(fdm, ignoreeof);
    exit(0);
}

static void
set_noecho(int fd)
{
    struct termios stermios;
    if (tcgetattr(fd, &stermios) < 0)
        err_sys("tcgetattr error");

    stermios.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL);

    /**
     * Also turn off NL to CR/NL mapping on output.
     */
    stermios.c_oflag &= ~(ONLCR);
    if (tcsetattr(fd, TCSANOW, &stermios) < 0)
        err_sys("tcsetattr error");
}
