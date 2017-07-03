char buf = 0;   /* buffer for ungetch */

int getch(void) /* get a (possibly pushed back) character */
{
    int c;

    if (buf != 0) {
        c = buf;
        buf = 0;
        return c;
    }
    return getchar();
}

void ungetch(int c) /* push character back on input */
{
    if (buf != 0)
        printf("ungetch: too many characters\n");
    else
        buf = c;
}
