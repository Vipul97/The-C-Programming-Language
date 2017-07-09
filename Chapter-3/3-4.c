/* int data type can only handle values between -(2^wordsize-1) to (2^wordsize-1) - 1, and if we make n having the largest negative number positive, it will result in an overflow. */

/* itoa:  convert n to characters in s */
void itoa(int n, char s[])
{
    int i, sign;

    sign = n;            /* record sign */
    i = 0;
    do {       /* generate digits in reverse order */
        s[i++] = abs(n % 10) + '0';   /* get next digit */
    } while ((n /= 10) != 0);         /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}
