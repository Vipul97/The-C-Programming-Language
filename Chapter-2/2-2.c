#include <stdio.h>
#define MAXLINE 100

Main()
{
	int i = 0, c;
	char s[MAXLINE];

	while (i < (MAXLINE - 1))
	{
		c = getchar();
		if (c == EOF)
			break;
		else if (c == '\n')
			break;
		s[i++] = c;
	}
	s[i] = '\0';
	return 0;
}