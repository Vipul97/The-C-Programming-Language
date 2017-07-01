#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100

struct tnode *addtree(struct tnode *, char *, int);
void treeprint(struct tnode *);
int getword(char *, int);
int isnoiseword(char *);

struct linelist {
    int lineno;
    struct linelist *next;
};
struct tnode {        /* the tree node: */
    char *word;           /* points to the text */
    struct linelist *lines;
    struct tnode *left;   /* left child */
    struct tnode *right;  /* right child */
};

main()
{
    struct tnode *root;
    char word[MAXWORD];
    int line = 1;

    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]) && isnoiseword(word) == -1)
            root = addtree(root, word, line);
        else if (word[0] == '\n')
            line++;
    treeprint(root);
    return 0;
}

struct tnode *talloc(void);
struct linelist *lalloc(void);
char *strdup(char *);
void addline(struct tnode *, int);

/* addtree:  add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w, int line)
{
    int cond;

    if (p == NULL) {    /* a new word has arrived */
        p = talloc();   /* make a new node */
        p->word = strdup(w);
        p->lines = lalloc();
        p->lines->lineno = line;
        p->lines->next = NULL;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0)
        addline(p, line);
    else if (cond < 0)    /* less than into left subtree */
        p->left = addtree(p->left, w, line);
    else if (cond > 0)    /* greater than into right subtree */
        p->right = addtree(p->right, w, line);
    return p;
}

void addline(struct tnode *p, int line)
{
    struct linelist *temp;

    for (temp = p->lines; temp->next != NULL && temp->lineno != line; temp = temp->next)
        ;
    if (temp->lineno != line) {
        temp->next = lalloc();
        temp->next->lineno = line;
        temp->next->next = NULL;
    }
}

/* treeprint:  in-order print of tree p */
void treeprint(struct tnode *p)
{
    struct linelist *temp;

    if (p != NULL) {
        treeprint(p->left);
        printf("%10s:", p->word);
        for (temp = p->lines; temp != NULL; temp = temp->next)
            printf("%4d", temp->lineno);
        printf("\n");
        treeprint(p->right);
    }
}

#include <stdlib.h>

/* talloc:  make a tnode */
struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

struct linelist *lalloc(void)
{
    return (struct linelist *) malloc(sizeof(struct linelist));
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

int isnoiseword(char *w)
{
    char *list[] = { "I", "a", "an", "and", "are", "be", "but",
                "by", "he", "in", "is", "it", "of", "off", "on",
                "or", "she", "so", "that", "the", "they", "this",
                "to", "you" };
    int cond;
    int low, high, mid;

    low = 0;
    high = sizeof(list)/sizeof(char *) - 1;
    while (low <= high) {
        mid = (low+high) / 2;
        if ((cond = strcmp(w, list[mid])) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
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
