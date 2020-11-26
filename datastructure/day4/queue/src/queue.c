#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 5
typedef int data_t;
typedef struct queue
{
	data_t data[SIZE];
	int front,rear;
}

queue *create_queue()
{
	queue *q = (queue*)malloc(sizeof(queue));
	memset(s->data, 0, sizeof(s->data));
	s->front = s->rear = 0;
	return q;
}

int queue_is_empty(queue *q)
{
	return (q->front == q->rear)? 1: 0;
}

int queue_is_full(queue *q)
{
	if(s->rear  > s->front ) //  没有循环时
		return ((s->rear - s->front == SIZE -1)? 1:0);  // r - f   ==  SIZE -1 ; 为 满

	if(s->rear  < s->front) // 循环时
		return((s->front  - s->rear == 1)?1:0); //   f - r  == 1 为 满
}

int main(int argc, const char *argv[])
{

	return 0;
}
