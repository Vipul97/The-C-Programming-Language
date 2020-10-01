/* itoa:  convert n to characters in s */
void itoa(int n, char s[], int w)
{
    int i, sign;

    sign = n;            /* record sign */
    i = 0;
    do {       /* generate digits in reverse order */
        s[i++] = abs(n % 10) + '0';   /* get next digit */
    } while ((n /= 10) != 0);         /* delete it */
    if (sign < 0)
        s[i++] = '-';
    while (i < w)
        s[i++] = ' ';
    s[i] = '\0';
    reverse(s);  /* reverse is a predefined function */
}
