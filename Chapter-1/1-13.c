#include <stdio.h>

#define MAXLEN 10

main()
{
    int c, i, j;
    int nchar[MAXLEN];

    for (i = 0; i < MAXLEN; ++i)
        nchar[i] = 0;

    i = 0;
    while ((c = getchar()) != EOF) {
        if (c != ' ' && c != '\t' && c != '\n')
            i++;
        else {
            if (i < MAXLEN)
                nchar[i]++;
            i = 0;
        }
    }

    for (i = 1; i < MAXLEN; ++i) {
        printf("%d: ", i);
        for (j = 0; j < nchar[i]; ++j)
            printf("-");
        printf("\n");
    }
}
