#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[])
{
	int i,j;
	for(i = 0;i < 6;i++)
	{
		for(j = 0;j < i;j++)
			printf("_");
		for(j = 0;j <= i;j++)		
			printf("%c",'F' - j);
		puts("");
	}
	return 0;
}
