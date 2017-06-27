#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000       /* max #lines to be sorted */
#define DEFAULT_LINES 10
#define BUFSIZE 5000

char *lineptr[MAXLINES];    /* pointers to text lines */

int readlines(char *lineptr[], int nlines, char *buf);
void writelines(char *lineptr[], int nlines, int tail);

main(int argc, char* argv[])
{
    int nlines;    /* number of input lines read */
    int tail = DEFAULT_LINES;
    char buf[BUFSIZE];

    if (--argc > 0 && (*++argv)[0] == '-')
        tail = atoi(++*argv);
    if ((nlines = readlines(lineptr, MAXLINES, buf)) >= 0) {
        writelines(lineptr, nlines, tail);
        return 0;
    } else {
        printf("error: input too big to tail\n");
        return 1;
    }
}

#define MAXLEN 1000   /* max length of any input line */
int getline(char *, int);

/* getline:  read a line into s, return length */
int getline(char s[], int lim)
{
    int c, i;

    for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        i++;
    }
    s[i] = '\0';
    return i;
}

/* readlines:  read input lines */
int readlines(char *lineptr[], int maxlines, char *buf)
{
    int len, nlines;
    char *p, line[MAXLEN], *bufstop;

    p = buf;
    bufstop = buf + BUFSIZE;
    nlines = 0;
    while ((len = getline1(line, MAXLEN)) > 0)
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

/* writelines:  write output lines */
void writelines(char *lineptr[], int nlines, int tail)
{
    while (nlines-- > 0)
        if (nlines < tail)
            printf("%s\n", *lineptr++);
        else
            lineptr++;
}
