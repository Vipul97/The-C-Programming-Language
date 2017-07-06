void calloc(unsigned n, unsigned size)
{
    unsigned i;
    char* ptr;

    if ((ptr = malloc(n * size)) != NULL)
        for (i = 0; i < n * size; i++)
            ptr[i] = 0;
    return (void*)ptr;
}
