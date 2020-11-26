#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 5
#define M 2

int main(int argc, const char *argv[])
{
	int i,j,a[N] = {1,2,3,4,5};
	int a1[N] ={0};
	for(i = 0; i < N; i++)
	{
		a1[i] = a[(i+M)%5];
	}
	for(j = 0;j < N; j++)
	{
		printf("a[%d] = %d\t",j,a1[j]);
	}
	return 0;
}
