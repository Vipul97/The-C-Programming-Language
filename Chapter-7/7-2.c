#include <ctype.h>
#include <stdio.h>
#define MAXLINE 80

main(int argc, char* argv[])
{
    int c, len;

    len = 0;
    while ((c = getchar()) != EOF)
        if (c == '\n' || len == MAXLINE) {
            putchar('\n');
            len = 0;
        } else if (!isgraph(c)) {
            if (argv[1][0] == 'x')
                len += printf("0x%x", c);
            else if (argv[1][0] == 'o')
                len += printf("0%o", c);
        } else {
            putchar(c);
            len++;
        }
    return 0;
}
