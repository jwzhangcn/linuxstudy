#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[])
{

	char *p = "126";
	int num = 0;

	while(*p)
	{
		num = num*10;
		num += *p - '0';
		p++;
	}

	printf("num = %d\n", num);
	return 0;
}
			
