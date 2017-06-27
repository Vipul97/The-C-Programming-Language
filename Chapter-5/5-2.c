/* getfloat returns int type as its function value. */

int getfloat(float* pn)
{
    int c, valsign, expsign = 0, sawsign, exp, sawe;
    float power;

    while (isspace(c = getch()))   /* skip white space */
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
        ungetch(c);    /* it's not a number */
        return 0;
    }
    valsign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        sawsign = c;
        c = getch();
        if (!isdigit(c)) {
            if (c != EOF)
                ungetch(c);
            ungetch(sawsign);
            return 0;
        }
    }
    for (*pn = 0.0; isdigit(c); c = getch())
        *pn = 10.0 * *pn + (c - '0');
    if (c == '.')
        c = getch();
    for (power = 1.0; isdigit(c); c = getch()) {
        *pn = 10.0 * *pn + (c - '0');
        power *= 10.0;
    }
    if (c == 'e' || c == 'E') {
        sawe = c;
        c = getch();
        expsign = (c == '-') ? -1 : 1;
        if (c == '+' || c == '-') {
            sawsign = c;
            c = getch();
            if (!isdigit(c)) {
                if (c != EOF)
                    ungetch(c);
                ungetch(sawe);
            }
        }
        for (exp = 0.0; isdigit(c); c = getch())
            exp = 10.0 * exp + (c - '0');
    }
    *pn *= valsign / power * pow(10, expsign * exp);
    if (c != EOF)
        ungetch(c);
    return c;
}
