#include <stdio.h>

#define SIZE 'z' - ' ' + 1

main()
{
    int c, i, j;
    int nchar[SIZE];

    for (i = 0; i < SIZE; ++i)
        nchar[i] = 0;

    while ((c = getchar()) != EOF)
        if (c >= ' ' && c <= 'z')
            ++nchar[c - ' '];

    for (i = 0; i < SIZE; ++i) {
        printf("%c: ", i + ' ');
        for (j = 0; j < nchar[i]; ++j)
            printf("-");
        printf("\n");
    }
}
