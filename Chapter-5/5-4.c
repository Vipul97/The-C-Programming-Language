int strend(char* s, char* t)
{
    s += strlen(s) - strlen(t);

    while (*s++ == *t++)
        if (*s == '\0')
            return 1;
    return 0;
}
