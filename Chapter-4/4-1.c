int strrindex(char s[], char t[])
{
    int i, j, k, match;

    for (i = 0, match = -1; s[i] != '\0'; i++) {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0')
            match = i;
    }
    return match;
}
