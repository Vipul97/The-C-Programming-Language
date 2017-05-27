#include <stdio.h>

/* print Fahrenheit-Celsius table
    for fahr = 0, 20, ..., 300; floating-point version */
float celsius(int fahr);

int main()
{
    float fahr;
    int lower, upper, step;

    lower = 0;      /* lower limit of temperatre table */
    upper = 300;    /* upper limit */
    step = 20;      /* step size */

    fahr = lower;
    while (fahr <= upper) {
        printf("%3.0f %6.1f\n", fahr, celsius(fahr));
        fahr = fahr + step;
    }
    return 0;
}

float celsius(int fahr)
{
    return (5.0/9.0) * (fahr-32.0);
}
