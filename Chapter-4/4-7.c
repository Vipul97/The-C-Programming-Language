/* ungets should just use ungetch as ungetch keeps track of buf and bufp. */

void ungets(char s[])
{
    int i = strlen(s) - 1;

    if (bufp + i + 1 >= BUFSIZE)
        printf("ungets: too many characters\n");
    else {
        while (i >= 0) {
            ungetch(s[i]);
            i--;
        }
    }
}
