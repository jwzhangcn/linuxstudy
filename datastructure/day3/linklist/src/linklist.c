#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int data_t;

typedef struct link_list
{
	data_t data;
	struct link_list *next;
}linklist;

linklist *create_linklist()
{
	linklist *head = (linklist*)malloc(sizeof(linklist));
	if(NULL == head)
		return NULL;
	head->data = -1;
	head->next = NULL;
	return head;
}
int get_linklist_length(linklist *head)
{
	if(NULL == head)
		return -1;
	linklist *p = head->next;
	int length = 0;
	while(p)
	{
		p = p->next;
		length++;
	}
	return length;
}

void print_linklist(linklist *head)
{
	linklist *p = head->next;
	while(p)
	{
		printf("%d\n",p->data);
		p = p->next;
	}
	puts("");
}


int insert_linklist_by_pos(linklist *head, int pos, data_t data)
{
	if(NULL == head)
		return -1;
	if(pos < 0 || pos > get_linklist_length(head) + 1)
		return -1;
	linklist *p = head;
	while(pos--)
	{
		p = p->next;
	}
	linklist *new = (linklist*)malloc(sizeof(linklist));
	new->data = data;
	new->next = p->next;
	p->next = new;
	return 1;
}

int delete_linklist_by_pos(linklist *head, int pos)
{
	if(NULL == head)
		return -1;
	if(pos < 0 || pos > get_linklist_length(head))
		return -1;
	linklist *p, *q;
	p = q = head;
	while(pos--)
		p = p->next;
	q = p -> next;
	p->next = q->next;
	free(q);
	q = NULL;
	return 1;
}

int find_by_pos(linklist *head, int pos)
{
	linklist *p = head;
	if(NULL == head)
		return -1;
	if(pos < 0 || pos > get_linklist_length(head))
		return -1;
	while(pos--)
		p = p->next;
	return p->next->data;
}

int update_linklist_by_pos(linklist *head, int pos, data_t data)
{
	linklist *p = head;
	if(NULL == head)
		return -1;
	if(pos < 0 || pos > get_linklist_length(head))
		return -1;
	while(pos--)
		p = p->next;
	p = p->next;
	p->data = data;
	return 1;
}

int destory_linklist(linklist *head)
{
	linklist *q = *p = head;
	while(p)
	{
		p = p->next;
		free(q);
		q = p;
	}
	p = q = NULL;
	return 1;
}

int main(int argc, const char *argv[])
{
	linklist *p = create_linklist();
	if(NULL != p)
		printf("creat linklist success..\n");
	int i;
	puts("create linklist");
	for(i=0; i<10; i++)
	{
		insert_linklist_by_pos(p, i, i+1);
	}
	print_linklist(p);

	delete_linklist_by_pos(p, 1);
	puts("delete linklist pos 1");
	print_linklist(p);

	printf("%d\n",find_by_pos(p, 3));
	puts("");
	puts("update linklist pos 3");
	if(update_linklist_by_pos(p, 3, 666))
		print_linklist(p);
	return 0;
}
