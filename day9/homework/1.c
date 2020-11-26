#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10

int *del(int *src,int n)
{
	int i;
	for(i = n; i < N; i++)
		src[i] = src[i+1];
	src[N] = '\0';
	return src;
}

int main(int argc, const char *argv[])
{
	int a[N] = {1,52,44,95,62,47,63,24,72,48};
	int i,n;
	printf("源整型数组：  ");
	
	for(i = 0; i < N; i++)
	{
		printf("a[%d] = %d ",i,a[i]);
	}
	printf("\n");

	printf("删除下标n：");
	scanf("%d",&n);

	del(a,n);

	printf("删除后的数组：");
	for(i = 0; i < N-1; i++)
	{
		printf("a[%d] = %d ",i,a[i]);
	}
	return 0;
}
