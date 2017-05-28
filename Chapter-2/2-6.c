unsigned setbits(unsigned x, int p, int n, int y)
{
    return ((x & ~(~(~0 << n) << (p + 1 - n))) | ((y & ~(~0 << n)) << (p + 1 - n)));
}
