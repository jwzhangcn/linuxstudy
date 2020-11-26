#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, const char *argv[])
{
	char a[100] = "";
	gets(a);
	char *p = a;

	int alpha, digit;

	alpha = digit = 0;
	while(*p)
	{
		if(isalpha(*p))
			alpha++;

		if(isdigit(*p))
			digit++;

		p++;
	}
	printf("字母有%d个，数字有%d个\n",alpha,digit);
}
