#include "myhead.h"
int main(int argc, const char *argv[])
{
	dlinklist *p = create_dlinklist();
	if(NULL != p)
		printf("creat dlinklist success..\n");
	int i;
	puts("create dlinklist");
	for(i=0; i<10; i++)
	{
		insert_dlinklist_by_pos(p, i, i+1);
	}
	print_dlinklist(p);
	/*
	   delete_dlinklist_by_pos(p, 1);
	   puts("delete dlinklist pos 1");
	   print_dlinklist(p);

	   printf("%d\n",find_by_pos(p, 3));
	   puts("");
	   puts("update dlinklist pos 3");
	   if(update_dlinklist_by_pos(p, 3, 666))
	   print_dlinklist(p);
	   */	
	return 0;
}
