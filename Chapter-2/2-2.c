i=0;
while (i < lim-1) {
    if ((c=getchar()) != '\n')
        if (c != EOF) {  //EOF is a predefined MACRO with the value of -1
            s[i] = c;
        }
    ++i;
}
