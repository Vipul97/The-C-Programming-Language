#include <math.h>
#include <stdio.h>
#include <stdlib.h>   /* for atof() */
#include <string.h>

#define MAXOP       100   /* max size of operand or operator */
#define NUMBER      '0'   /* signal that a number was found */
#define IDENTIFIER  '1'

int getop(char []);
void push(double);
double pop(void);
double top(void);
void clear(void);
void func(char []);

/* reverse Polish calculator */
main()
{
    int type, i;
    double op1, op2, v;
    char s[MAXOP];
    double variable[26] = { 0 };

    while ((type = getop(s)) != EOF) {
        switch (type) {
        case NUMBER:
            push(atof(s));
            break;
        case IDENTIFIER:
            func(s);
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: zero divisor\n");
            break;
        case '%':
            op2 = pop();
            if (op2 != 0.0)
                push((int)pop() % (int)op2);
            else
                printf("error: zero divisor\n");
            break;
        case '?':
            printf("\t%.8g\n", top());
            break;
        case '#':
            op2 = pop();
            push(op2);
            push(op2);
            break;
        case '~':
            op1 = pop();
            op2 = pop();
            push(op1);
            push(op2);
            break;
        case '!':
            clear();
            break;
        case '=':
            variable[i] = pop();
            break;
        case '\n':
            v = pop();
            printf("\t%.8g\n", v);
            break;
        default:
            if (type >= 'A' && type <= 'Z') {
                push(variable[type - 'A']);
                i = type - 'A';
            } else
                printf("error: unknown command %s\n", s);
            break;
        }
    }
    return 0;
}

#define MAXVAL  100   /* maximum depth of val stack */

int sp = 0;           /* next free stack position */
double val[MAXVAL];   /* value stack */

/* push:  push f onto value stack */
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop:  pop and return top value from stack */
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

double top(void)
{
    if (sp > 0)
        return val[sp - 1];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

void clear(void)
{
    sp = 0;
}

void func(char s[])
{
    double op2;

    if (strcmp(s, "sin") == 0)
        push(sin(pop()));
    else if (strcmp(s, "exp") == 0)
        push(exp(pop()));
    else if (strcmp(s, "pow") == 0) {
        op2 = pop();
        push(pow(pop(), op2));
    } else
        printf("error: unknown command %s\n", s);
}

#include <ctype.h>

/* getop:  get next operator or numeric operand */
int getop(char s[])
{
    int i;

    i = 0;
    scanf("%s", s);
    if (islower(s[i])) {
        while (islower(s[++i]))
            ;
        s[i] = '\0';
        return IDENTIFIER;
    }
    if (!isdigit(s[i]) && s[i] != '.' && s[i] != '-')
        return s[i];     /* not a number */
    if (s[i] == '-')
        if (!isdigit(s[++i]))
            return '-';
    if (isdigit(s[i]))   /* collect integer part */
        while (isdigit(s[++i]))
            ;
    if (s[i] == '.')     /* collect fraction part */
        while (isdigit(s[++i]))
            ;
    s[i] = '\0';
    return NUMBER;
}
