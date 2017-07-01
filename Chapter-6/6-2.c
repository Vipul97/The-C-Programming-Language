#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
#define DEFAULT 6

enum { NO,
    YES };

struct tnode *addtree(struct tnode *, char *, int, int);
void treeprint(struct tnode *);
int getword(char *, int);

struct tnode {        /* the tree node: */
    char *word;           /* points to the text */
    int match;
    struct tnode *left;   /* left child */
    struct tnode *right;  /* right child */
};

main(int argc, char* argv[])
{
    struct tnode *root;
    char word[MAXWORD];
    int n = DEFAULT;

    if (argc == 2)
        n = atoi(*++argv);
    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]) && strlen(word) >= n)
            root = addtree(root, word, n, NO);
    treeprint(root);
    return 0;
}

struct tnode *talloc(void);
char *strdup(char *);

/* addtree:  add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w, int n, int found)
{
    int cond;

    if (p == NULL) {    /* a new word has arrived */
        p = talloc();   /* make a new node */
        p->word = strdup(w);
        p->match = found ? YES : NO;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) < 0) { /* less than into left subtree */
        if (strncmp(p->word, w, n) == 0)
            p->match = found = YES;
        p->left = addtree(p->left, w, n, found);
    } else if (cond > 0) {  /* greater than into right subtree */
        if (strncmp(p->word, w, n) == 0)
            p->match = found = YES;
        p->right = addtree(p->right, w, n, found);
    }
    return p;
}

/* treeprint:  in-order print of tree p */
void treeprint(struct tnode *p)
{
    if (p != NULL) {
        treeprint(p->left);
        if (p->match)
            printf("%s\n", p->word);
        treeprint(p->right);
    }
}

#include <stdlib.h>

/* talloc:  make a tnode */
struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

char *strdup(char *s)   /* make a duplicate of s */
{
    char *p;

    p = (char *) malloc(strlen(s)+1);  /* +1 for '\0' */
    if (p != NULL)
        strcpy(p, s);
    return p;
}

/* getword:  get next word or character from input */
int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))
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
    else if (c == '/')
        if ((c = getch()) == '*') {
            while ((c = getch()) != EOF)
                if (c == '*' && (c = getch()) == '/')
                    break;
        } else
            ungetch(c);
    else if (c == '#')
        while ((c = getch()) != '\n')
            if (c == '\\')
                c = getch();
    if (!isalpha(c) && c != '_') {
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
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
