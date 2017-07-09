void strncpy(char* s, char* t, int n)
{
    while ((*s++ = *t++) && n--)
        ;
}

void strncat(char* s, char* t, int n)
{
    while (*s)
        s++;
    while ((*s++ = *t++) && n--)
        ;
    *s = '\0';
}

int strncmp(char* s, char* t, int n)
{
    for (; n--; s++, t++)
        if (*s != *t)
            return *s - *t;
    return 0;
}
