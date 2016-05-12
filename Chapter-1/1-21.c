#include <stdio.h>

void entab(int n);

main()
{
	entab(8);
	return 0;
}

void entab(int n)
{
	int	column, blanks, c;

	column = blanks = 0;
	while ((c = getchar()) != EOF) {
		if (c == ' ')
			blanks++;
		else if (c == '\t')
			blanks = blanks + n - (column + blanks) % n;
		else {
			while (blanks) {
				int	t;

				t = n - column % n;
				if (t <= blanks && t != 1) {
					column = column + t;
					putchar('\t');
					blanks = blanks - t;
				}
				else
					do {
						column++;
						putchar(' ');
					} while (--blanks);
			}
			putchar(c);
			if (c == '\n')
				column = 0;
			else
				column++;
		}
	}
}