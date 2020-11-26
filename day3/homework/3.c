#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[])
{
	char str[100] = "I LOVE YOU !";
	char *p = str;
	char *p1 = p + strlen(str);
	char temp[10] = '';
	char str1[100] = '';
	int n;

	while(str == *p1)
	{
		if(*p1 != ' ')
		{
			n++;
			
		}
		p1--;
	}

.
	return 0;
}
