#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int main(int argc, const char *argv[])
{
	char str[100] = "a1b4e5";
	char str1[100] = "";
	int i;

	char *p = str;
	char *p1 = str1;

	while(*p)
	{
		if(isalpha(*p))
		{
			for(i = 0; i < *(p+1)-'0'; i++)
			{
				*p1++ = *p;
			}
		}
		p++;
	}
	puts(str1);
	return 0;
}
