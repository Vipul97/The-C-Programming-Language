#include <stdio.h>
#define TABSIZE 8

main()
{
    int column, c;

    column = 1;
    while ((c = getchar()) != EOF)
        if (c == '\t') {
            putchar(' ');
            column++;
            while ((column - 1) % TABSIZE) {
                putchar(' ');
                column++;
            }
        } else {
            putchar(c);
            if (c == '\n')
                column = 1;
            else
                column++;
        }
    return 0;
}
