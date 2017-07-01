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
