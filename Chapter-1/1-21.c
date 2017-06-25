#include <stdio.h>

void entab(int n);

main()
{
    entab(8);
    return 0;
}

void entab(int n)
{
    int column, blanks, c;

    column = 1;
    blanks = 0;
    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\t') {
            if (c == ' ')
                blanks++;
            else
                blanks += n - (blanks + column - 1) % n;
            if (blanks == n - (column - 1) % n) {
                putchar('\t');
                column += n - (column - 1) % n;
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
}
