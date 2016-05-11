#include <stdio.h>

double fahrenheit(int c);

int main()
{
	int i;

	for (i = 0; i <= 300; i += 20)
		printf("%3d %6.1f\n", i, fahrenheit(i));

	return 0;
}

double fahrenheit(int c)
{
	return (5.0 / 9.0)*(c - 32);
}