#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, const char *argv[])
{
	int count = 0;

	while(1)
	{
		if(NULL == fopen("../datastructure/day4/link_stack/src/link_stack.c","r"))
		{
			printf("%d\n",count);
			break;
		}
		count++;
	}
	return 0;
}
