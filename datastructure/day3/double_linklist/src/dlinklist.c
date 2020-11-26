#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myhead.h"

dlinklist *create_dlinklist()
{
	dlinklist *head = (dlinklist*)malloc(sizeof(dlinklist));
	if(NULL == head)
		return NULL;
	head->data = -1;
	head->next = NULL;
	head->prev = NULL;
	return head;
}
int get_dlinklist_length(dlinklist *head)
{
	if(NULL == head)
		return -1;
	dlinklist *p = head->next;
	int length = 0;
	while(p)
	{
		p = p->next;
		length++;
	}
	return length;
}

void print_dlinklist(dlinklist *head)
{
	dlinklist *p = head->next;
	while(p)
	{
		printf("%5d",p->data);
		p = p->next;
	}
	puts("");
}


int insert_dlinklist_by_pos(dlinklist *head, int pos, data_t data)
{
	if(NULL == head)
		return -1;
	if(pos < 0 || pos > get_dlinklist_length(head))
		return -1;
	dlinklist *p = head;
	while(pos--)
	{
		p = p->next;
	}
	dlinklist *new = (dlinklist*)malloc(sizeof(dlinklist));

	new->data = data;
	if(NULL != p->next)
	{
		new->next = p->next;
		new->prev = p->next->prev;
		p->next = new;
		new->next->prev = new;
	}
	else
	{
		new->prev = p;
		p->next = new;
	}
	return 1;
}

int delete_dlinklist_by_pos(dlinklist *head, int pos)
{
	if(NULL == head)
		return -1;
	if(pos < 0 || pos > get_dlinklist_length(head))
		return -1;
	dlinklist *p, *q;
	p = q = head;
	while(pos--)
		p = p->next;
	if(p->next->next != NULL)  
	{
		q = p->next;
		p->next = q->next;  
		q->next->prev = q->prev;

		free(q);
		q = NULL;
	}
	else  
	{
		q = p->next;
		p->next = NULL;

		free(q);
		q = NULL; 
	}
	return 0;
}

int find_by_pos(dlinklist *head, int pos)
{
	dlinklist *p = head;
	if(NULL == head)
		return -1;
	if(pos < 0 || pos > get_dlinklist_length(head))
		return -1;
	while(pos--)
		p = p->next;
	return p->next->data;
}

int update_dlinklist_by_pos(dlinklist *head, int pos, data_t data)
{
	dlinklist *p = head;
	if(NULL == head)
		return -1;
	if(pos < 0 || pos > get_dlinklist_length(head))
		return -1;
	while(pos--)
		p = p->next;
	p = p->next;
	p->data = data;
	return 1;
}

int destory_dlinklist(dlinklist *head)
{
	dlinklist *q,*p;
	p = q = head;
	while(p)
	{
		p = p->next;
		free(q);
		q = p;
	}
	p = q = NULL;
	return 1;
}

