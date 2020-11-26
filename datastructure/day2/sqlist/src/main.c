#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlist.h"

int main()
{
	seqlist *seq =  createSeqlist();
	if(NULL == seq)
	{
		printf("malloc failed\n");
		return -1;
	}	
	int ret = seqlist_is_empty(seq);
	printf("%s:line:%d ret=%d\n",__func__,__LINE__, ret);

	ret = seqlist_is_full(seq);
	printf("line:%d ret=%d\n",__LINE__, ret);
	
	int num = getLengthSeqlist(seq);
	printf("line:%d num=%d\n",__LINE__, num);

	int i = 0;
	while(i<10)
	{	
		ret = insertSeqlistByPos(seq, i, i+1);
		i++;
	}
	printSeqlist(seq);
	ret = insertSeqlistByPos(seq, 5, 50);
	printSeqlist(seq);

	i = 0;
	while(i<5)
	{
		deleteSeqlistByPos(seq,0);
		i++;
	}
	printSeqlist(seq);

	destorySeqlist(&seq);//地址传参
	printf("%p\n",seq);

	return 0;
}
