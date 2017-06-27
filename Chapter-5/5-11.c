#include <stdio.h>
#include <stdlib.h>

#define MAX 1000
#define DEFAULT_TAB 8

main(int argc, char* argv[])
{
    int tab[MAX], i, j, column, blanks, c, n;

    if (argc > 1)
        for (i = 0; --argc != 0; i++)
            tab[i] = atoi(*++argv);
    tab[i] = DEFAULT_TAB;
    j = 0;
    n = tab[j];
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
                if (j < i)
                    n = tab[++j];
            }
        } else {
            while (blanks) {
                putchar(' ');
                column++;
                blanks--;
            }
            putchar(c);
            if (j < i && column - 1 >= n)
                n = tab[++j];
            if (c == '\n') {
                j = 0;
                n = tab[j];
                column = 1;
            } else
                column++;
        }
    }
}

#include <stdio.h>
#include <stdlib.h>

#define MAX 1000
#define DEFAULT_TAB 8

main(int argc, char* argv[])
{
    int tab[MAX], i, j, column, c, n;

    if (argc > 1)
        for (i = 0; --argc != 0; i++)
            tab[i] = atoi(*++argv);
    tab[i] = DEFAULT_TAB;
    j = 0;
    n = tab[j];
    column = 1;
    while ((c = getchar()) != EOF)
        if (c == '\t') {
            do {
                putchar(' ');
                column++;
                if (j < i && column - 1 > n)
                    n = tab[++j];
            } while ((column - 1) % n);
        } else {
            putchar(c);
            if (c == '\n') {
                j = 0;
                n = tab[j];
                column = 1;
            } else
                column++;
        }
}
