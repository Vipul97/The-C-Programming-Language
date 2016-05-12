#include <stdio.h>
#define MAXLINE	1000	/* maximum input line size */

int getline(char line[], int maxline);
void copy(char to[], char from[]);

/* print longest input line */
main()
{
	int	len;			/* current line length */
	int	max;			/* maximum length seen so far */
	char line[MAXLINE];		/* current input line */
	char longest[MAXLINE];	/* longet line saved here */

	max = 0;
	while ((len = getline(line, MAXLINE)) > 0)
		if (len > max) {
			max = len;
			copy(longest, line);
		}
	if (max > 0)	/* there was a line */
		printf("%s", longest);
	return 0;
}

/* getline: read a line into s, return length */
int getline(char s[], int lim)
{
	int	c, i;

	for (i = 0; (c = getchar()) != EOF && c != '\n'; ++i)
		if (i < lim - 2)
			s[i] = c;

	if (i < lim - 1)
	{
		s[i] = '\n';
		s[i + 1] = '\0';
	}
	else
	{
		s[lim - 2] = '\n';
		s[lim - 1] = '\0';
	}

	if (c == '\n')
		++i;
	return i;
}

void copy(char to[], char from[])
{
	int	i;

	i = 0;
	while ((to[i] = from[i]) != '\0')
		++i;
}