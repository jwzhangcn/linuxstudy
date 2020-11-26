#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void* sort(void *args)
{
	int str[strlen((int)args)] = (int)args;
	int i,j;
	for(i = 0; i < strlen(str); i++)
	{
		for(j = i; j < strlen(str); j++)
		{
			if(str[j] > str[j + 1])
			{
				str[j] ^= str[j + 1];
				str[j + 1] ^= str[j];
				str[j] ^= str [j+1];
			}
		}
	}
	return (void*)str
}

int main(int argc, const char *argv[])
{
	int str[10] = {4,3,5,6,2,1,8,9,7,0};
	pthread_t tid;
	pthread_create(&tid, NULL, sort, (void*)str);
	for(i = 0; i < 10, i++)
	{}
	return 0;
}
