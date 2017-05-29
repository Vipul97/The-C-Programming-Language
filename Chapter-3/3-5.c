void itob(int n, char s[], int b)
{
    int i, sign;

    sign = n;
    i = 0;
    do {
        s[i++] = abs(n % b) + '0';
    } while ((n /= b) != 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}
