#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void delch(char *p,char ch)
{
	char *pch;
	while (*p != '\0')
	{
		if (*p == ch)
		{
			for (pch = p;* pch != '\0'; pch++)
				*pch =* (pch+1);
		}
		p++;
	}
}


int main(int argc, const char *argv[])
{
	
	char a[]="abbcdef";
	char ch;
	scanf("%c",&ch);
	delch(a,ch);
	puts(a);
	return 0;
}
