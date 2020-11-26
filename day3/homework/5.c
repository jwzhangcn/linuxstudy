#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[])
{
	char str[100] = "aabbbbbccceeeeee";
	char str1[100] = "";

	char *p = str;
	char *p1 = str1;

	int count = 1;

	while(*p)
	{
		if(*p == *(p+1) || *(p+1) == '\0')
		{
			*p1 = *p;
			count++;
		}
		else
		{
			*++p1 = count + '0';
			*p1++;
			count = 1;
		}
		p++;
	}
	puts(str1);
	return 0;
}
