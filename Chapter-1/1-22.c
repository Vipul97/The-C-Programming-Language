#include <stdio.h>
#define FOLDING_LENGTH 80
#define TABSIZE 8

void print_buffer(char buffer[], int length);

int main()
{
    int column, non_blanks, c;
    char buffer[FOLDING_LENGTH];

    column = 1;
    non_blanks = 0;
    while ((c = getchar()) != EOF)
        if (c == ' ' || c == '\t') {
            if (column + non_blanks <= FOLDING_LENGTH)
                column = column + non_blanks;
            else {
                putchar('\n');
                column = non_blanks + 1;
            }
            print_buffer(buffer, non_blanks);
            non_blanks = 0;
            putchar(c);
            if (c == '\t')
                column = column + TABSIZE - (column - 1) % TABSIZE;
            else
                column++;
            if (column > FOLDING_LENGTH) {
                putchar('\n');
                column = 1;
            }
        } else if (c == '\n') {
            if (column + non_blanks > FOLDING_LENGTH)
                putchar('\n');
            print_buffer(buffer, non_blanks);
            putchar('\n');
            column = 1;
            non_blanks = 0;
        } else if (non_blanks < FOLDING_LENGTH)
            buffer[non_blanks++] = c;
        else {
            if (column != 1)
                putchar('\n');
            print_buffer(buffer, FOLDING_LENGTH);
            putchar(c);
            while ((c = getchar()) != EOF && c != ' ' && c != '\t' && c != '\n')
                putchar(c);
            putchar('\n');
            column = 1;
            non_blanks = 0;
        }
    return 0;
}

void print_buffer(char buffer[], int length)
{
    int i;

    for (i = 0; i < length; i++)
        putchar(buffer[i]);
}
