#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int data_t;

typedef struct link_stack{
	data_t data;
	struct link_stack* next;
}link_stack;

link_stack *create_link_stack()
{
	link_stack *top = (link_stack*)malloc(sizeof(link_stack));
	top->data = -1;
	top->next = NULL;
	return top;
}

int link_stack_is_empty(link_stack *top)
{
	return (top->next == NULL)? 1: 0;
}

int get_link_stack_length(link_stack *top)
{
	link_stack *p = top;
	int count = 0;
	while(p)
	{
		p = p->next;
		count++;
	}
	return count;
}

int push_link_stack(link_stack *top, data_t data)
{
	link_stack *p = (link_stack *)malloc(sizeof(link_stack));
	p->next = top->next;
	top->next = p;
	p->data = data;

	return 1;
}

int pop_link_stack(link_stack *top)
{
	if(link_stack_is_empty(top))
		return -1;
	int retdata = top->next->data;
	link_stack *p = top->next;
	top->next = p->next;
	free(p);
	p = NULL;
	return retdata;
}

int get_element(link_stack *top){
	link_stack *p, *q;
	p = top->next;
	return 1;
}

int main(int argc, const char *argv[])
{
	link_stack *ls = create_link_stack();
	if(NULL == ls)
	{
		printf("ERROR\n");
		return -1;
	}
	int i = 0;
	for(i=0; i<5; i++)
	{
		push_link_stack(ls, i);
	}
	printf("%5d\n",pop_link_stack(ls));
	printf("%5d\n",pop_link_stack(ls));
	return 0;
}
