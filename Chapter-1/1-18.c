#include <stdio.h>
#define MAXLINE 1000

int getline(char line[], int maxline);

main()
{
    int len;
    char line[MAXLINE];

    while ((len = getline(line, MAXLINE)) > 0) {
        while (len > 1 && (line[len-1] == ' ' || line[len-1] == '\t' || line[len-1] == '\n'))
            len--;

        if (len > 1) {
            line[len] = '\n';
            line[len+1] = '\0';
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
