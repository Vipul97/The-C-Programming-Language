#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100

struct tnode {        /* the tree node: */
    char *word;           /* points to the text */
    int count;
    struct tnode *left;   /* left child */
    struct tnode *right;  /* right child */
};
struct word {
    char *word;
    int count;
};

struct tnode *addtree(struct tnode *, char *);
int getword(char *, int);
void qsort(struct word *, int, int);
int wordcount = 0;

main()
{
    struct tnode *root;
    char word[MAXWORD];
    void fillarray(struct tnode *, struct word *);
    int i;

    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            root = addtree(root, word);
    struct word wordlist[wordcount];
    fillarray(root, wordlist);
    qsort(wordlist, 0, wordcount - 1);
    for (i = 0; i < wordcount; i++)
        printf("%4d: %s\n", wordlist[i].count, wordlist[i].word);
    return 0;
}

struct tnode *talloc(void);
char *strdup(char *);

/* addtree:  add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;

    if (p == NULL) {    /* a new word has arrived */
        p = talloc();   /* make a new node */
        p->word = strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
        wordcount++;
    } else if ((cond = strcmp(w, p->word)) == 0)
        p->count++;       /* repeated word */
    else if (cond < 0)    /* less than into left subtree */
        p->left = addtree(p->left, w);
    else if (cond > 0)    /* greater than into right subtree */
        p->right = addtree(p->right, w);
    return p;
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

void fillarray(struct tnode *p, struct word wordlist[])
{
    static int i;

    if (p != NULL) {
        fillarray(p->left, wordlist);
        wordlist[i++] = (struct word) { p->word, p->count };
        fillarray(p->right, wordlist);
    }
}

/* qsort:  sort v[left]...v[right] into increasing order */
void qsort(struct word v[], int left, int right)
{
    int i, last;
    void swap(struct word v[], int, int);

    if (left >= right)   /* do nothing if array contains */
        return;          /* fewer than two elements */
    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
        if (v[i].count > v[left].count)
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last-1);
    qsort(v, last+1, right);
}

void swap(struct word v[], int i, int j)
{
    struct word temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
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
