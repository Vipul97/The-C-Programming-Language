#include <stdio.h>

/* readlines:  read input lines */
int readlines(char *lineptr[], int maxlines, char *buf)
{
    int len, nlines;
    char *p, line[MAXLEN], *bufstop;

    p = buf;
    bufstop = buf + BUFSIZE;
    nlines = 0;
    while ((len = getline(line, MAXLEN)) > 0)
        if (nlines >= maxlines || p + len > bufstop)
            return -1;
        else {
            line[len-1] = '\0'; /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
            p += len;
        }
    return nlines;
}
