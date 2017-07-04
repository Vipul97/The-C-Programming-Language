#include <ctype.h>
#include <stdio.h>
#include <string.h>

main(int argc, char* argv[])
{
    int c;

    if (strcmp(argv[0], "./tolower") == 0)
        while ((c = getchar()) != EOF)
            putchar(tolower(c));
    else if (strcmp(argv[0], "./toupper") == 0)
        while ((c = getchar()) != EOF)
            putchar(toupper(c));
    else
        printf("Unknown Parameter.\n");
    return 0;
}
