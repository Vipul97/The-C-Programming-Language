void itoa(int n, char s[])
{
    static int i;

    if (n < 0)
        s[i++] = '-';
    if (n / 10)
        itoa(abs(n) / 10, s);
    s[i++] = abs(n) % 10 + '0';
    s[i] = '\0';
}
