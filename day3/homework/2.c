#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[])
{
	char str[100] = "";
	gets(str);

	char *p1 = str;
	char *p2 = p1;
	while(*p1)
	{
		if(*p1 != ' ')
		{
			*p2++ = *p1;
		}
		p1++;
	}
	*p2 = '\0';
	puts(str);
	return 0;
}
