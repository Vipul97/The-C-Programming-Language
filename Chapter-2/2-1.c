#include <limits.h>
#include <stdio.h>

main()
{
    signed char sc;
    unsigned char uc = 0;
    signed short ss;
    unsigned short us = 0;
    signed int si;
    unsigned int ui = 0;
    signed long sl;
    unsigned long ul = 0;
    float f;
    double d;
    long double ld;
    printf("%f, %f, %Lf\n", f, d, ld);
    printf("By Printing Appropriate Values from Standard Headers:\n");
    printf("Range of signed char: %d - %d\n", SCHAR_MIN, SCHAR_MAX);
    printf("Range of unsigned char: %u - %u\n", 0, UCHAR_MAX);
    printf("Range of signed short: %d - %d\n", SHRT_MIN, SHRT_MAX);
    printf("Range of unsigned short: %u - %u\n", 0, USHRT_MAX);
    printf("Range of signed int: %d - %d\n", INT_MIN, INT_MAX);
    printf("Range of unsigned int: %u - %u\n", 0, UINT_MAX);
    printf("Range of signed long: %ld - %ld\n", LONG_MIN, LONG_MAX);
    printf("Range of unsigned long: %d - %lu\n", 0, ULONG_MAX);

    printf("\nBy Direct Computation:\n");
    printf("Range of signed char: ");
    for (sc = 0; sc <= 0; sc--)
        ;
    printf("%d - %d\n", ++sc, sc);
    printf("Range of unsigned char: %u - %u\n", 0, --uc);
    printf("Range of signed short: ");
    for (ss = 0; ss <= 0; ss--)
        ;
    printf("%d - %d\n", ++ss, ss);
    printf("Range of unsigned short: %u - %u\n", 0, --us);
    printf("Range of signed int: ");
    for (si = 0; si <= 0; si--)
        ;
    printf("%d - ", ++si);
    printf("%d\n", --si);
    printf("Range of unsigned int: %u - %u\n", 0, --ui);
    printf("Range of signed long");
    for (sl = 0; sl <= 0; sl--)
        ;
    printf("%ld - %ld\n", ++sl, sl);
    printf("Range of unsigned long: %d - %lu\n", 0, --ul);
    printf("Range of float: ");
    printf("%f\n", f);
    for (f = 0; f <= 0; f -= 0.000001)
        ;
    printf("%f - %f\n", f += 0.1, f);
    printf("Range of double: ");
    for (d = 0; d <= 0; d -= 0.000001)
        ;
    printf("%f - %f\n", d += 0.000001, d);
    printf("Range of long double: ");
    for (ld = 0; ld <= 0; ld -= 0.000001)
        ;
    printf("%Lf - %Lf\n", ld += 0.000001, ld);
    return 0;
}
