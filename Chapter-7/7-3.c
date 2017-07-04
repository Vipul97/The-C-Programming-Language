#include <stdarg.h>

/* minprintf:  minimal printf with variable argument list */
void minprintf(char *fmt, ...)
{
    va_list ap;   /* points to each unnamed arg in turn */
    char *p, *sval;
    int ival;
    double dval;
    unsigned int uval;
    void *pval;

    va_start(ap, fmt); /* make ap point to 1st unnamed arg */
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        switch (*++p) {
        case 'd':
        case 'i':
            ival = va_arg(ap, int);
            printf("%d", ival);
            break;
        case 'o':
            uval = va_arg(ap, int);
            printf("%o", uval);
            break;
        case 'x':
            uval = va_arg(ap, int);
            printf("%x", uval);
            break;
        case 'X':
            uval = va_arg(ap, int);
            printf("%X", uval);
            break;
        case 'u':
            uval = va_arg(ap, int);
            printf("%u", uval);
            break;
        case 'c':
            ival = va_arg(ap, int);
            printf("%c", ival);
            break;
        case 's':
            for (sval = va_arg(ap, char *); *sval; sval++)
                putchar(*sval);
            break;
        case 'f':
            dval = va_arg(ap, double);
            printf("%f", dval);
            break;
        case 'e':
            dval = va_arg(ap, double);
            printf("%e", dval);
            break;
        case 'E':
            dval = va_arg(ap, double);
            printf("%E", dval);
            break;
        case 'g':
            dval = va_arg(ap, double);
            printf("%g", dval);
            break;
        case 'G':
            dval = va_arg(ap, double);
            printf("%G", dval);
            break;
        case 'p':
            pval = va_arg(ap, void *);
            printf("%p", pval);
            break;
        default:
            putchar(*p);
            break;
        }
    }
    va_end(ap);   /* clean up when done */
}
