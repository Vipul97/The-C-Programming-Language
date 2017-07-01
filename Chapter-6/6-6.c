#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
#define HASHSIZE 101

struct nlist {       /* table entry: */
    struct nlist *next;   /* next entry in chain */
    char *name;           /* defined name */
    char *defn;           /* replacement text */
};

static struct nlist *hashtab[HASHSIZE]; /* pointer table */

void skipspaces(void);
int getword(char *, int);
unsigned hash(char *);
struct nlist *install(char *, char *);
int undef(char *);
int getch(void);
void ungetch(int);

main()
{
    struct nlist *np;
    char word[MAXWORD], dir[MAXWORD], name[MAXWORD], def[MAXWORD];
    int i;

    while (getword(word, MAXWORD) != EOF) {
        if (strcmp(word, "#") == 0) {
            getword(dir, MAXWORD);
            if (strcmp(dir, "define") == 0) {
                if (!isalpha(getword(name, MAXWORD)))
                    printf("getdef: name is not alphabetical\n");
                else {
                    skipspaces();
                    for (i = 0; i < MAXWORD; i++)
                        if ((def[i] = getch()) == EOF || def[i] == '\n')
                            break;
                        else if (def[i] == '\\') {
                            getch();
                            i--;
                        }
                    def[i] = '\0';
                    if (i == 0)
                        printf("getdef: incomplete definition\n");
                    else
                        install(name, def);
                }
            } else if (strcmp(dir, "undef") == 0) {
                skipspaces();
                if (!isalpha(getword(name, MAXWORD)))
                    printf("getdef: name is not alphabetical\n");
                else {
                    if (undef(name) != 0)
                        printf("getdef: name not found\n");
                }
            } else
                printf("getdef: unknown command\n");
        }
        printf("Lookup Table:\n");
        for (i = 0; i < HASHSIZE; i++)
            for (np = hashtab[i]; np != NULL; np = np->next)
                printf("%s: %s\n", np->name, np->defn);
        printf("\n");
    }
    return 0;
}

void skipspaces(void)
{
    int c;

    while ((c = getch()) == ' ' || c == '\t')
        ;
    ungetch(c);
}

/* getword:  get next word or character from input */
int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()) && c != '\n')
        ;
    if (c != EOF)
        *w++ = c;
    if (c == '"') {
        while ((c = getch()) != EOF && c != '"')
            if (c == '\\')
                c = getch();
    } else if (c == '\'')
        while ((c = getch()) != EOF && c != '\'')
            ;
    else if (c == '/') {
        if ((c = getch()) == '*') {
            while ((c = getch()) != EOF)
                if (c == '*' && (c = getch()) == '/')
                    break;
        } else
            ungetch(c);
    }
    if (c == '#' || (!isalpha(c) && c != '_')) {
        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++)
        if (!isalnum(*w = getch()) && *w != '_') {
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];
}

/* hash:  form hash value for string s */
unsigned hash(char *s)
{
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

/* lookup:  look for s in hashtab */
struct nlist *lookup(char *s)
{
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;  /* found */
    return NULL;        /* not found */
}

struct nlist *lookup(char *);
char *strdup(char *);

/* install:  put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {  /* not found */
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else      /* already there */
        free((void *) np->defn);  /* free previous defn */
    if ((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
}

int undef(char *s)
{
    struct nlist *prev, *np;
    unsigned hashval = hash(s);

    if (lookup(s) == NULL)
        return 1;
    for (np = hashtab[hashval], prev = NULL; np != NULL; prev = np, np = np->next)
        if (strcmp(s, np->name) == 0) {
            if (prev == NULL)
                hashtab[hashval] = np->next;
            else
                prev->next = np->next;
            free((void *) np->name);
            free((void *) np->defn);
            free((void *) np);
            return 0;
        }
    return 1;
}

char *strdup(char *s)   /* make a duplicate of s */
{
    char *p;

    p = (char *) malloc(strlen(s)+1);  /* +1 for '\0' */
    if (p != NULL)
        strcpy(p, s);
    return p;
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
