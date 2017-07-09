#include <stdio.h>
#define TABSIZE 8

main()
{
    int column, blanks, c;

    column = 1;
    blanks = 0;
    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\t') {
            if (c == ' ')
                blanks++;
            else
                blanks = blanks + TABSIZE - (blanks + column - 1) % TABSIZE;
            if (blanks == TABSIZE - (column - 1) % TABSIZE) {
                putchar('\t');
                column = column + TABSIZE - (column - 1) % TABSIZE;
                blanks = 0;
            }
        } else {
            while (blanks) {
                putchar(' ');
                column++;
                blanks--;
            }
            putchar(c);
            if (c == '\n')
                column = 1;
            else
                column++;
        }
    }
    return 0;
}
