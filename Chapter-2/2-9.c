/* If x is odd, then the bit representation of (x-1) will be that of x except that the rightmost 1-bit will be 0. In this case, x &= (x-1) will result (x-1).
   If x is even, then the bit representation of (x-1) will be that of x except that the rightmost 0-bits of x to be 1 and the rightmost 1-bit of x to be 0. In this case, x &= (x-1) will result in setting the rightmost 1-bits from x and (x-1) to be 0. */

int bitcount(unsigned x)
{
    int b;

    for (b = 0; x != 0; x &= (x - 1))
        b++;
    return b;
}
