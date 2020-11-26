#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 10
void insert(int *src, int num, int n)
{
	int i;
	
	for(i = N-1; i > n; i--)
	{
	//	printf("%d", i);
		src[i] = src[i-1];
	}

	src[n] = num;
}

int main(int argc, const char *argv[])
{
	int a[N]={12,23,34,45,56,67,78,89,11};
	int num, i, j = 9;

	printf("输入要插入的数字：");
	scanf("%d", &num);
	puts("");
	printf("输入要插入的位置：");
	scanf("%d", &i);
	puts("");
	
	insert(a, num, i);

	for(i = 0; i < N; i++)
	{
		printf("a[%d] = %d ", i, a[i]);
	}
	puts("");
	return 0;
}
