#include <stdio.h>

main()
{
    int c, i, j;
    int nchar[100];

    for (i = 0; i < 100; ++i)
        nchar[i] = 0;

    i = 0;
    while ((c = getchar()) != EOF)
        if (c >= ' ' && c <= 'z')
            i++;
        else {
            nchar[i] = i;
            i = 0;
        }

    for (i = 0; i < 100; ++i) {
        for (j = 0; j < nchar[i]; ++j)
            printf("-");
        printf("\n");
    }
}
