/* Since EOF is defined to be -1, it is an integer type. Therefore, to handle a pushed-back EOF correctly, buf should be of int data type. */

#define BUFSIZE 100

char buf[BUFSIZE] = 0;  /* buffer for ungetch */
int bufp = 0;           /* next free position in buf */

int getch(void) /* get a (possibly pushed back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
