#include <stdio.h>

#define NOTHING 0
#define COMMENT 1
#define DOUBLE_QUOTE 2
#define SINGLE_QUOTE 3

int line;

void print_error(char s[]);

int main()
{
    int state, parentheses, brackets, braces, c;

    line = 1;
    state = NOTHING;
    parentheses = brackets = braces = 0;
    while ((c = getchar()) != EOF)
        if (state == NOTHING) {
            if (c == '/') {
                if ((c = getchar()) == '*')
                    state = COMMENT;
            } else {
                if (c == '\'')
                    state = SINGLE_QUOTE;
                else if (c == '\"')
                    state = DOUBLE_QUOTE;
                else if (c == '\n')
                    line++;
                else if (c == '(')
                    parentheses++;
                else if (c == ')') {
                    if (--parentheses < 0) {
                        print_error("Unbalanced parentheses");
                        return -1;
                    }
                } else if (c == '[')
                    brackets++;
                else if (c == ']') {
                    if (--brackets < 0) {
                        print_error("Unbalanced brackets");
                        return -1;
                    }
                } else if (c == '{')
                    braces++;
                else if (c == '}') {
                    if (--braces < 0) {
                        print_error("Unbalanced braces");
                        return -1;
                    }
                } else if (c == '*')
                    if ((c = getchar()) == '/')
                        print_error("Uninitialized comment");
            }
        } else if (state == COMMENT) {
            if (c == '\n')
                line++;
            else
                while (c == '*')
                    if ((c = getchar()) == '/')
                        state = NOTHING;
        } else {
            if (c == '\n') {
                print_error("Unbalanced single or double quote");
                return -1;
            } else if (c == '\\')
                c = getchar();
            else if ((state == DOUBLE_QUOTE && c == '\"') || (state == SINGLE_QUOTE && c == '\''))
                state = NOTHING;
        }
    if (state == COMMENT) {
        print_error("Unterminated comment");
        return -1;
    } else if (state == DOUBLE_QUOTE || state == SINGLE_QUOTE) {
        print_error("Unterminated single or double quote");
        return -1;
    }
    return 0;
}

void print_error(char s[])
{
    printf("error on line %d: %s\n", line, s);
}
