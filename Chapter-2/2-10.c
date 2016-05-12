int lower(int c)
{
	return c >= 'A' && c <= 'Z' ? 'a' + c - 'A' : c;
}