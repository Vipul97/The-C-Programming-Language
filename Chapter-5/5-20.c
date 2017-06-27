#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define  MAXTOKEN  100

enum { NAME, PARENS, BRACKETS };
enum { NO, YES };

void dcl(void);
void dirdcl(void);

int gettoken(void);
int tokentype;            /* type of last token */
char token[MAXTOKEN];     /* last token string */
char name[MAXTOKEN];      /* identifier name */
char datatype[MAXTOKEN];  /* data type = char, int, etc. */
char out[1000];           /* output string */
int errtoken = NO;

main()  /* convert declaration to words */
{
    while (gettoken() != EOF) {   /* 1st token on line */
        strcpy(datatype, token);  /* is the datatype */
        out[0] = '\0';
        dcl();      /* parse rest of line */
        if (tokentype != '\n')
            printf("syntax error\n");
        printf("%s: %s %s\n", name, out, datatype);
    }
    return 0;
}

int gettoken(void)  /* return next token */
{
    int c, getch(void);
    void ungetch(int);
    char *p = token;

    if (errtoken == YES) {
        errtoken = NO;
        return tokentype;
    }
    while ((c = getch()) == ' ' || c == '\t')
        ;
    if (c == '(') {
        if ((c = getch()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetch(c);
            return tokentype = '(';
        }
    } else if (c == '[') {
        for (*p++ = c; (*p++ = getch()) != ']'; )
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getch()); )
            *p++ = c;
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    } else
        return tokentype = c;
}

/* dcl:  parse a declarator */
void dcl(void)
{
    int ns;

    for (ns = 0; gettoken() == '*';)    /* count *'s */
        ns++;
    dirdcl();
    while (ns-- > 0)
        strcat(out, " pointer to");
}

/* dirdcl:  parse a direct declarator */
void dirdcl(void)
{
    int type;
    void paramdcl(void);

    if (tokentype == '(') {          /* ( dcl ) */
        dcl();
        if (tokentype != ')') {
            printf("error: missing )\n");
            errtoken = YES;
        }
    } else if (tokentype == NAME) {  /* variable name */
        if (name[0] == '\0')
            strcpy(name, token);
    } else {
        printf("error: expected name or (dcl)\n");
        errtoken = YES;
    }
    while ((type=gettoken()) == PARENS || type == BRACKETS || type == '(')
        if (type == PARENS)
            strcat(out, " function returning");
        else if (type == '(') {
            strcat(out, " function taking");
            paramdcl();
            strcat(out, " and returning");
        } else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
}

#include <stdlib.h>

void declspec(void);
int typespec(void);
int typedesc(void);

void paramdcl(void)
{
    do {
        declspec();
    } while (tokentype == ',');
    if (tokentype != ')') {
        printf("error: missing ) in declarator of parameters\n");
        errtoken = YES;
    }
}

void declspec(void)
{
    char temp[MAXTOKEN];

    temp[0] = '\0';
    gettoken();
    do {
        if (tokentype != NAME) {
            errtoken = YES;
            dcl();
        } else if (typespec() == YES || typedesc() == YES) {
            strcat(temp, " ");
            strcat(temp, token);
            gettoken();
        } else {
            printf("error: unknown type in the parameter list\n");
            errtoken = YES;
        }
    } while (tokentype != ',' && tokentype != ')');
    strcat(out, temp);
    if (tokentype == ',')
        strcat(out, ",");
}

int typespec(void)
{
    static char *types[] = { "char", "int", "void" };
    char *ptypes = token;
    int result, i;

    result = NO;
    for (i = 0; i < 3; i++)
        if (strcmp(ptypes, *(types + i)) == 0)
            return result = YES;
    return result;
}

int typedesc(void)
{
    static char *typed[] = { "const", "volatile" };
    char *ptd = token;
    int result, i;

    result = NO;
    for (i = 0; i < 2; i++)
        if (strcmp(ptd, *(typed + i)) == 0)
            return result = YES;
    return result;
}

#define BUFSIZE 100

char buf[BUFSIZE];  /* buffer for ungetch */
int bufp = 0;       /* next free position in buf */

int getch(void) /* get a (possibly pushed back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: to many characters\n");
    else
        buf[bufp++] = c;
}
