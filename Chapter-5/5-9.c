/* day_of_year:  set day of year from month & day */
int day_of_year(int year, int month, int day)
{
    int leap;
    char *p;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    p = daytab[leap];
    if (month < 1 || month > 12)
        return -1;
    if (day < 1 || day > *(p + month))
        return -1;
    while (month--)
        day += *p++;
    return day;
}

/* month_day:  set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int leap;
    char *p1, *p2;

    if (year < 1 || yearday < 1) {
        *pmonth = -1;
        *pday = -1;
        return;
    }
    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    if ((leap == 0 && yearday > 365) || (leap == 1 && yearday > 366)) {
        *pmonth = -1;
        *pday = -1;
        return;
    }
    p1 = daytab[leap];
    p2 = p1;
    while (yearday > *p1)
        yearday -= *p1++;
    *pmonth = p1 - p2;
    *pday = yearday;
}
