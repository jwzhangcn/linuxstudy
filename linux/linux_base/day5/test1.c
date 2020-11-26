#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *mystrcpy(char* src, char* dest)
{
	if(src == NULL || dest == NULL)
	{
		return NULL;
	}
	
	char *p = dest;

	while(*src)
	{
		*dest++ = *src++;
	}

	return p;
}

int main(int argc, const char *argv[])
{
	char a[] = "abc";
	char b[] = "";
	puts(mystrcpy(a, b));
	return 0;
}
