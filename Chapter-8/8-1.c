#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include "syscalls.h"

#define BUFSIZ 1024

void error(char *, ...);

main(int argc, char *argv[])
{
    int fd;
    void filecopy(int, int);
    char *prog = argv[0]; /* program name for errors */

    if (argc == 1) /* no args; copy standard input */
        filecopy(0, 1);
    else
        while (--argc > 0)
            if ((fd = open(*++argv, O_RDONLY, 0)) == -1)
                error("%s: can't open %s\n",
                    prog, *argv);
            else {
                filecopy(fd, 1);
                close(fd);
            }
    exit(0);
}

/* filecopy:  copy file ifp to file ofp */
void filecopy(int ifp, int ofp)
{
    int n;
    char buf[BUFSIZ];

    while (n = read(ifp, buf, BUFSIZ) > 0)
        write(ofp, buf, n);
}

/* error:  print an error message and die */
void error(char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    fprintf(stderr, "error: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(1);
}
