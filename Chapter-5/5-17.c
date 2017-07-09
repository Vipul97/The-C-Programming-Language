#include <stdio.h>
#include <string.h>

#define MAXLINES 5000     /* max #lines to be sorted */
#define MAXSTR 5000
char *lineptr[MAXLINES];  /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort(void *lineptr[], int left, int right,
           int (*comp)(void *, void *));
int strcmp(char *, char *);
int numcmp(char *, char *);
void sortstr(char *, char *, int);

int numeric, reverse, fold, directory;
int pos1 = pos2 = 0;

/* sort input lines */
main(int argc, char* argv[])
{
    int nlines;           /* number of input lines read */
    int c;
    numeric = reverse = fold = directory = 0;

    while (--argc > 0 && (*++argv)[0] == '-')
        while (c = *++argv[0])
            switch (c) {
            case 'n':
                numeric = 1;
                break;
            case 'r':
                reverse = 1;
                break;
            case 'f':
                fold = 1;
                break;
            case 'd':
                directory = 1;
                break;
            default:
                printf("sort: illegal option %c\n", c);
                argc = 0;
                break;
            }
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort((void **)lineptr, 0, nlines-1,
            (int (*)(void*,void*))(numeric ? numcmp : strcmp));
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}

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

#define ALLOCSIZE 10000 /* size of available space */

static char allocbuf[ALLOCSIZE];  /* storage for alloc */
static char *allocp = allocbuf;   /* next free position */

char *alloc(int n)  /* return pointer to n characters */
{
    if (allocbuf + ALLOCSIZE - allocp >= n) { /* it fits */
        allocp += n;
        return allocp - n; /* old p */
    } else      /* not enough room */
        return 0;
}

#define MAXLEN 1000   /* max length of any input line */
int getline(char *, int);
char *alloc(int);

/* readlines:  read input lines */
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = getline(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len-1] = '\0'; /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    return nlines;
}

/* writelines:  write output lines */
void writelines(char *lineptr[], int nlines)
{
    int i;

    for (i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

/* qsort:  sort v[left]...v[right] into increasing order */
void qsort(void *v[], int left, int right,
           int (*comp)(void *, void *))
{
    int i, last;
    void swap(void *v[], int, int);

    if (left >= right)   /* do nothing if array contains */
        return;          /* fewer than two elements */
    swap(v, left, (left + right)/2);
    last = left;
    if (reverse) {
        for (i = left+1; i <= right; i++)
            if ((*comp)(v[i], v[left]) > 0)
                swap(v, ++last, i); 
    } else {
        for (i = left+1; i <= right; i++)
            if ((*comp)(v[i], v[left]) < 0)
                swap(v, ++last, i);
    }
    swap(v, left, last);
    qsort(v, left, last-1, comp);
    qsort(v, last+1, right, comp);
}

#include <ctype.h>

/* strcmp:  return <0 if s<t, 0 if s==t, >0 if s>t */
int strcmp(char *s, char *t)
{
    if (directory) {
        while (*s && !isalnum(*s) && !isspace(*s))
            s++;
        while (*s && !isalnum(*t) && !isspace(*t))
            t++;
    }
    while (fold ? tolower(*s) == tolower(*t) : *s == *t) {
        if (*s == '\0')
            return 0;
        s++;
        t++;
        if (directory) {
            while (*s && !isalnum(*s) && !isspace(*s))
                s++;
            while (*s && !isalnum(*t) && !isspace(*t))
                t++;
        }
    }
    return fold ? tolower(*s) - tolower(*t) : *s - *t;
}

#include <stdlib.h>

/* numcmp:  compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
    double v1, v2;
    char str[MAXSTR];

    sortstr(s1, str, MAXSTR);
    v1 = atof(s1);
    sortstr(s2, str, MAXSTR);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

void swap(void *v[], int i, int j)
{
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void sortstr(char *s, char *t, int maxstr)
{
    int i, j, len;

    len = strlen(s);
    if (pos2 > 0 && len > pos2)
        len = pos2;
    else if (pos2 > 0 && len < pos2) {
        printf("substr: string too short\n");
        return;
    }
    for (i = 0, j = pos1; j < len; i++, j++)
        t[i] = s[j];
    t[i] = '\0';
}
