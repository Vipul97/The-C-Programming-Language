void expand(char s1[], char s2[])
{
    int i, j, k;

    for (i = 0, j = 0; s1[i] != '\0'; i++) {
        s2[j++] = s1[i];
        if ((s1[i] >= 'a' && s1[i] <= 'z') || (s1[i] >= 'A' && s1[i] <= 'Z') || (s1[i] >= '0' && s1[i] <= '9'))
            if (s1[i + 1] == '-' && s1[i + 2] > s1[i]) {
                for (k = 1; s2[j - 1] < s1[i + 2]; k++)
                    s2[j++] = s1[i] + k;
                j--;
                i++;
            }
    }

    s2[j] = '\0';
}
