/* To save space */
int isupper(int c)
{
    return c >= 'A' && c <= 'Z';
}

/* To save time */
#define isupper(c) (c >= 'A' && c <= 'Z') ? 1 : 0
