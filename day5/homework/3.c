#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void* sort(void *args)
{
	int *p = (int)args;
//	printf("%d",(int)args);
	int i;
	for(i = 0; i < 10; i++)
	{
		printf(" %d ", p[i]);
	}
}

int main(int argc, const char *argv[])
{
	int str[10] = {4,3,5,6,2,1,8,9,7,0};
	int i,j,n;

	n = sizeof(str)/sizeof(*str);

//	printf("%d",n);
	for(i = 0; i < n - 1;  i++)
	{
		for(j = 0; j < n - i -1; j++)
		{
			if(str[j] > str[j + 1])
			{
				str[j] ^= str[j + 1];
				str[j + 1] ^= str[j];
				str[j] ^= str [j+1];
			}
		}
	}

	pthread_t tid;
	pthread_create(&tid, NULL, sort, (void*)str);
	sleep(2);
	return 0;
}
