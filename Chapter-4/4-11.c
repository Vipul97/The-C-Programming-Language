/* getop:  get next operator or numeric operand */
int getop(char s[])
{
    int i, c;
    static int ungetch = 0;

    if (ungetch == 0)
        c = getch();
    else {
        c = ungetch;
        ungetch = 0;
    }
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    i = 0;
    if (islower(c)) {
        while (islower(s[++i] = c = getch()))
            ;
        s[i] = '\0';
        if (c != EOF)
            ungetch = c;
        return IDENTIFIER;
    }
    if (!isdigit(c) && c != '.' && c != '-')
        return c;     /* not a number */
    if (c == '-')
        if (!isdigit(s[++i] = c = getch())) {
            ungetch = c;
            return '-';
        }
    if (isdigit(c))   /* collect integer part */
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')     /* collect fraction part */
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetch = c;
    return NUMBER;
}
