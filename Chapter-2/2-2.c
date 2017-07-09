i=0;
while (i < lim-1) {
    if ((c=getchar()) != '\n')
        if (c != EOF) {
            s[i] = c;
        }
    ++i;
}
