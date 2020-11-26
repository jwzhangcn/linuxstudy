#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 10
int main(int argc, const char *argv[])
{
	int a[N] = {0,1,2,3,9,5,6,7,8,4};
	int *p = a;
	int i, flag, max = 0;
	for(i = 0; i < N ; i++)
	{
		if(a[i] > max)
		{
			max = a[i];
		}
	}

	for(i = 0; i < N; i++)
	{
		if(a[i] == max)
			break;
	}
	
	printf("最大值：%d, 下标%d \n", max, i);
	return 0;
}
