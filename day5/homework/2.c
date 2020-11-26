#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define NUM_THREADS 3

pthread_mutex_t mutex[NUM_THREADS];

void *thread(void *args)
{
	pthread_mutex_lock(&mutex[(int)args]);
	while(1)
	{
		printf("线程%d 运行 ： %c \n", (int)args + 1,'A' + (int)args);
		sleep(1);
	}
	pthread_mutex_unlock(&mutex[(int)args]);
}


int main(int argc, const char *argv[])
{
	int i;
	pthread_t tids[NUM_THREADS];
	for(i = 0; i < NUM_THREADS; i++)
	{
		printf("%d" , i);
		pthread_create(&tids[i], NULL, thread, (void*)i);
	}
	while(1)
	{
		printf("main\n");
		sleep(1);
	}
	return 0;
}
