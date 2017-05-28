unsigned rightrot(unsigned x, int n)
{
    while (n > 0) {
        if ((x & 1) == 1)
            x = (x >> 1) | ~(~0U >> 1);
        else
            x >>= 1;
        n--;
    }
    return x;
}
