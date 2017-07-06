void* bfree(void* p, unsigned n)
{
    void free(void*);
    unsigned nunits;
    Header* ptr;

    ptr = (Header*)p;
    nunits = n / sizeof(Header);
    if (nunits <= 1)
        return NULL;
    if (freep == NULL) {
        base.s.ptr = freep = &base;
        base.s.size = 0;
    }
    ptr->s.size = nunits;
    free((void*)(ptr + 1));
    return (void*)(ptr + 1);
}
