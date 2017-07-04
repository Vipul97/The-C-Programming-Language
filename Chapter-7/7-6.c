#include <stdio.h>
#include <string.h>
#define MAXLINE 80

main(int argc, char* argv[])
{
    FILE *fp1, *fp2;
    void compare(FILE*, FILE*);

    if ((fp1 = fopen(*++argv, "r")) == NULL) {
        printf("compare: can't open %s\n", *argv);
        return 1;
    }
    if ((fp2 = fopen(*++argv, "r")) == NULL) {
        printf("compare: can't open %s\n", *argv);
        return 1;
    }
    compare(fp1, fp2);
    fclose(fp1);
    fclose(fp2);
    return 0;
}

void compare(FILE* fp1, FILE* fp2)
{
    char str1[MAXLINE], str2[MAXLINE];

    while (fgets(str1, MAXLINE, fp1) != NULL && fgets(str2, MAXLINE, fp2) != NULL)
        if (strcmp(str1, str2) != 0) {
            printf("%s%s", str1, str2);
            break;
        }
}
