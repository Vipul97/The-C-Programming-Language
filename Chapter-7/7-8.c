#include <stdio.h>
#include <string.h>
#define MAXLINE 80
#define PAGELINE 20

main(int argc, char* argv[])
{
    char line[MAXLINE], *pattern;
    long lineno, pageno;
    FILE* fp;

    if (argc == 1) {
        printf("error: no files are named as arguments\n");
        return -1;
    } else {
        while (--argc > 0) {
            if ((fp = fopen(*++argv, "r")) == NULL) {
                printf("find: can't open %s\n", *argv);
                continue;
            }
            lineno = 0;
            pageno = 1;
            printf("%s:\nPage %ld:\n", *argv, pageno);
            while (fgets(line, MAXLINE, fp) != NULL) {
                lineno++;
                printf("%s", line);
                if (lineno == PAGELINE) {
                    lineno = 0;
                    pageno++;
                    printf("\nPage %ld:\n", pageno);
                }
            }
            printf("\n");
            pageno++;
        }
        fclose(fp);
    }
    return pageno;
}
