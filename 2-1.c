#include <stdio.h>
#include <limits.h>

main()
{
	printf("Range of signed char: %d - %d\n", SCHAR_MIN, SCHAR_MAX);
	printf("Range of unsigned char: %u - %u\n", 0, UCHAR_MAX);
	printf("Range of signed short: %d - %d\n", SHRT_MIN, SHRT_MAX);
	printf("Range of unsigned short: %u - %u\n", 0, USHRT_MAX);
	printf("Range of signed int: %d - %d\n", INT_MIN, INT_MAX);
	printf("Range of unsigned int: %u - %u\n", 0, UINT_MAX);
	printf("Range of signed long: %ld - %ld\n", LONG_MIN, LONG_MAX);
	printf("Range of unsigned long: %d - %lu\n", 0, ULONG_MAX);
	return 0;
}