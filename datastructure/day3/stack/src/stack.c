#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int data_t;
typedef struct stack{
	data_t *data;
	int maxlen;
	int top;
}stack;

stack* create_stack(int len)
{
	stack *s = (stack*)malloc(sizeof(stack));
	if(NULL == s)
		return;
	s->data = (data_t*)calloc(len,sizeof(data_t));
	if(NULL == s->data)
		return;
	s->top = -1;
	s->maxlen = len;
	return s;
}

int stack_is_empty(stack *s)
{
	return (s->top == -1)? 1: 0;
}


data_t get_stack_element(stack *s)
{
	return s->data[s->top];
}

int push(stack *s,data_t data)
{
	if(s->top  == s->maxlen-1)
		return -1;
	else
	{
		s->data[s->top] = data;
	}
	return 1;
}

data_t pop(stack *s)
{
	if(s->top != -1)
	{
		return s->data[s->top];
		s->top--;
	}
	return -1;
}

int main(int argc, const char *argv[])
{
	stack *s = create_stack(10);
	if(NULL == s)
		printf("create_stack success!\n");
	push(s, 1);
	push(s, 2);
	printf("%d\n",get_stack_element(s));
	
	printf("%d\n",pop(s));
	return 0;

}
