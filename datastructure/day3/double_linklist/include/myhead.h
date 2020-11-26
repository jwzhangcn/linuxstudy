#ifndef _MYHEAD_H_
#define _MYHEAD_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int data_t;

typedef struct double_link_list
{
	data_t data;
	struct double_link_list *next;
	struct double_link_list *prev;
}dlinklist;


dlinklist *create_dlinklist();
int get_dlinklist_length(dlinklist *);
void print_dlinklist(dlinklist *head);
int insert_dlinklist_by_pos(dlinklist *, int, data_t);
int delete_dlinklist_by_pos(dlinklist *, int );
int find_by_pos(dlinklist *, int );
int update_dlinklist_by_pos(dlinklist *, int , data_t);
int destory_dlinklist(dlinklist *);
#endif
