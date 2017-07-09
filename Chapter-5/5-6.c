int getline(char* s, int lim)
{
    int c;
    char* t;

    for (t = s; lim-- && (c=getchar()) != EOF && c != '\n'; s++)
        *s = c;
    if (c == '\n') {
        *s = c;
        ++s;
    }
    *s = '\0';
    return s - t;
}

int atoi(char* s)
{
    int n;

    n = 0;
    while (*s >= '0' && *s <= '9')
        n = 10 * n + (*s++ - '0');
    return n;
}

void itoa(int n, char* s)
{
    int sign;
    char* t;

    sign = n;
    t = s;
    do {
        *s++ = abs(n % 10) + '0';
    } while ((n /= 10) != 0);
    if (sign < 0)
        *s++ = '-';
    *s = '\0';
    reverse(t);
}

void reverse(char* s)
{
    int c;
    char* j;

    for (j = s + strlen(s) - 1; s < j; s++, j--) {
        c = *s;
        *s = *j;
        *j = c;
    }
}

int strindex(char* s, char* t)
{
    char *i, *j, *k;

    for (i = s; *i != '\0'; i++) {
        for (j = i, k = t; *k != '\0' && *j == *k; j++, k++)
            ;
        if (k > t && *k == '\0')
            return i - s;
    }
    return -1;
}

int getop(char* s)
{
    int c;
    static int ungetch = 0;

    if (ungetch == 0)
        c = getch();
    else {
        c = ungetch;
        ungetch = 0;
    }
    while ((*s = c = getch()) == ' ' || c == '\t')
        ;
    *(s + 1) = '\0';
    if (islower(c)) {
        while (islower(*++s = c = getch()))
            ;
        *s = '\0';
        if (c != EOF)
            ungetch = c;
        return IDENTIFIER;
    }
    if (!isdigit(c) && c != '.' && c != '-')
        return c;
    if (c == '-')
        if (!isdigit(*++s = c = getch())) {
            ungetch = c;
            return '-';
        }
    if (isdigit(c))
        while (isdigit(*++s = c = getch()))
            ;
    if (c == '.')
        while (isdigit(*++s = c = getch()))
            ;
    *s = '\0';
    if (c != EOF)
        ungetch = c;
    return NUMBER;
}
