#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 20
int main(int argc, const char *argv[])
{
	int i,j;
	for(i = 1; i <= N; i++)
	{
		for(j = 1; j <= N; j++)
		{
			if(i < N/2)
			{
				if(j > N/2-i && j < N/2+i)
					printf("*");
				else
					printf(" ");
			}
			else
			{
				if(j > i - N/2 && j < N/2 + i)
					printf("*");
				else
					printf(" ");
			}
		}
		printf("\n");
	}
	return 0;
}
