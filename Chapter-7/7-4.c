#include <stdarg.h>

void minscanf(char *fmt, ...)
{
    va_list ap;   /* points to each unnamed arg in turn */
    char *p, *sval;
    int *ival;
    float *fval;
    unsigned int *uval;

    va_start(ap, fmt); /* make ap point to 1st unnamed arg */
    for (p = fmt; *p; p++) {
        if (*p != '%')
            continue;
        switch (*++p) {
        case 'd':
        case 'i':
            ival = va_arg(ap, int *);
            scanf("%d", ival);
            break;
        case 'o':
            uval = va_arg(ap, int *);
            scanf("%o", uval);
            break;
        case 'u':
            uval = va_arg(ap, int *);
            scanf("%u", uval);
            break;
        case 'x':
            uval = va_arg(ap, int *);
            scanf("%x", uval);
            break;
        case 'c':
            sval = va_arg(ap, char *);
            scanf("%c", sval);
            break;
        case 's':
            sval = va_arg(ap, char *);
            scanf("%s", sval);
            break;
        case 'e':
            fval = va_arg(ap, float *);
            scanf("%e", fval);
            break;
        case 'f':
            fval = va_arg(ap, float *);
            scanf("%f", fval);
            break;
        case 'g':
            fval = va_arg(ap, float *);
            scanf("%g", fval);
            break;
        default:
            break;
        }
    }
    va_end(ap);   /* clean up when done */
}
