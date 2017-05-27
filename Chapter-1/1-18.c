#include <stdio.h>
#define MAXLINE 1000

int getline(char line[], int maxline);

main()
{
    int len;
    char line[MAXLINE];

    while ((len = getline(line, MAXLINE)) > 0) {
        len = len-2;
        if (len >= 0 && line[len] == '\n')
            len--;

        while (len >= 0 && (line[len] == ' ' || line[len] == '\t'))
            len--;

        if (len >= 0) {
            line[len+1] = '\n';
            line[len+2] = '\0';
            printf("%s", line);
        }
    }
    return 0;
}

int getline(char s[], int lim)
{
    int c, i;

    for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}
