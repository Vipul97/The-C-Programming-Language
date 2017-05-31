void reverse(char s[])
{
    static int i;
    int j = strlen(s) - i - 1, c;

    if (i < j) {
        c = s[i];
        s[i++] = s[j];
        s[j] = c;
        reverse(s);
    }
}
