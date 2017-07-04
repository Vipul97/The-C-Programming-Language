/* The file name should be printed when a matching line is found. */

#include <stdio.h>
#include <string.h>
#define MAXLINE 80

int getline(char* line, int max);

/* find:  print lines that match pattern from 1st arg */
main(int argc, char* argv[])
{
    char line[MAXLINE], *pattern;
    long lineno = 0;
    int c, except = 0, number = 0, found = 0;
    FILE* fp;

    while (--argc > 0 && (*++argv)[0] == '-')
        while (c = *++argv[0])
            switch (c) {
            case 'x':
                except = 1;
                break;
            case 'n':
                number = 1;
                break;
            default:
                printf("find: illegal option %c\n", c);
                argc = 0;
                found = -1;
                break;
            }
    if (argc < 1)
        printf("Usage: find -x -n pattern\n");
    else if (argc == 1)
        while (getline(line, MAXLINE) > 0) {
            lineno++;
            if ((strstr(line, *argv) != NULL) != except) {
                if (number)
                    printf("%ld:", lineno);
                printf("%s", line);
                found++;
            }
        }
    else {
        pattern = *argv;
        while (--argc > 0) {
            if ((fp = fopen(*++argv, "r")) == NULL) {
                printf("find: can't open %s\n", *argv);
                continue;
            }
            lineno = 0;
            while (fgets(line, MAXLINE, fp) != NULL) {
                lineno++;
                if ((strstr(line, pattern) != NULL) != except) {
                    printf("%s:", *argv);
                    if (number)
                        printf("%ld:", lineno);
                    printf("%s", line);
                    found++;
                }
            }
            fclose(fp);
        }
    }
    return found;
}

int getline(char s[], int lim)
{
    int c, i;

    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}
