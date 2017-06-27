#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_TAB 8

void entab(int m, int n);

main(int argc, char* argv[])
{
    int start = 0, tab = DEFAULT_TAB;

    while (--argc > 0)
        switch (**++argv) {
        case '-':
            start = atoi(++*argv);
            break;
        case '+':
            tab = atoi(++*argv);
            break;
        default:
            printf("entab: illegal option %c\n", **argv);
            argc = 0;
            break;
        }
    entab(start, tab);
}

void entab(int m, int n)
{
    int start, column, blanks, c;

    start = m;
    column = 1;
    blanks = 0;
    while ((c = getchar()) != EOF) {
        while (start >= n - (column - 1) % n) {
            putchar('\t');
            column += n - (column - 1) % n;
            start -= n - (column - 1) % n;
        }
        while (start) {
            putchar(' ');
            column++;
            start--;
        }
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
            if (c == '\n') {
                start = m;
                column = 1;
            } else
                column++;
        }
    }
}

#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_TAB 8

void detab(int m, int n);

main(int argc, char* argv[])
{
    int start = 0, tab = DEFAULT_TAB;

    while (--argc > 0)
        switch (**++argv) {
        case '-':
            start = atoi(++*argv);
            break;
        case '+':
            tab = atoi(++*argv);
            break;
        default:
            printf("detab: illegal option %c\n", **argv);
            argc = 0;
            break;
        }
    detab(start, tab);
}

void detab(int m, int n)
{
    int start, column, c;

    start = m;
    column = 1;
    while ((c = getchar()) != EOF) {
        while (start) {
            putchar(' ');
            column++;
            start--;
        }
        if (c == '\t') {
            do {
                putchar(' ');
                column++;
            } while ((column - 1) % n);
        } else {
            putchar(c);
            if (c == '\n') {
                start = m;
                column = 1;
            } else
                column++;
        }
    }
}
