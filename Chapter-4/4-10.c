#include <math.h>
#include <stdio.h>
#include <stdlib.h>   /* for atof() */
#include <string.h>

#define MAXOP       100   /* max size of operand or operator */
#define NUMBER      '0'   /* signal that a number was found */
#define IDENTIFIER  '1'
#define MAXLINE     1000

int getop(char []);
void push(double);
double pop(void);
double top(void);
void clear(void);
void func(char []);
int getline(char [], int);

/* reverse Polish calculator */
main()
{
    int type, i;
    double op1, op2, v;
    char s[MAXOP];
    double variable[26] = {0};

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
            push(variable[i] = pop());
            pop();
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

int lp = 0;
char line[MAXLINE];

/* getop:  get next operator or numeric operand */
int getop(char s[])
{
    int i, c;

    if (line[lp] == '\0')
        if (getline1(line, MAXLINE) == 0)
            return EOF;
        else
            lp = 0;

    while ((s[0] = c = line[lp++]) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    i = 0;
    if (islower(c)) {
        while (islower(s[++i] = c = line[lp++]))
            ;
        s[i] = '\0';
        lp--;
        return IDENTIFIER;
    }
    if (!isdigit(c) && c != '.' && c != '-')
        return c;     /* not a number */
    if (c == '-')
        if (!isdigit(s[++i] = c = line[lp++])) {
            c = line[--lp];
            return '-';
        }
    if (isdigit(c))   /* collect integer part */
        while (isdigit(s[++i] = c = line[lp++]))
            ;
    if (c == '.')     /* collect fraction part */
        while (isdigit(s[++i] = c = line[lp++]))
            ;
    s[i] = '\0';
    lp--;
    return NUMBER;
}

int getline(char s[], int lim)
{
    int i, c;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}
