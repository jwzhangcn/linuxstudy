#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlist.h"


//给顺序表开空间
seqlist * createSeqlist()
{
	seqlist *seq = (seqlist *)malloc(sizeof(seqlist));//给结构体开空间
	if(NULL == seq)
		return NULL;

	memset(seq->data,0,sizeof(seq->data));//内存清零函数 bzero
	seq->last = -1;//说明顺序表为空
	
	return seq;
}
//判空
int seqlist_is_empty(seqlist *seq)
{
	if(NULL != seq)
		return ((seq->last == -1)?1:0);
}

//判满
int seqlist_is_full(seqlist *seq)
{
	if(NULL != seq)
		return ((seq->last+1 == SIZE)?1:0);
}

//求顺序表中元素个数
int getLengthSeqlist(seqlist *seq)
{
	if(NULL != seq)//判断指针是否有效
		return (seq->last+1);
}

#if 1

//按位置添加元素到顺序表
/*******************************************************
Description:按位置添加元素到顺序表
	int insertSeqlistByPos(seqlist *seq, int pos, data_t data);
Argument:
	seq:顺序表的首地址
	pos:要插入的位置 pos从0开始
	data:要插入的元素值
Return:
	成功：0
	失败：-1
*******************************************************/
int insertSeqlistByPos(seqlist *seq, int pos, data_t data)
{
	if(NULL == seq)//判断指针是否有效
		return -1;
	int len = getLengthSeqlist(seq);//求顺序表中元素个数
	//判断位置是否合法
	if(pos < 0 || pos > len)
		return -1;
	//判断顺序表是否为满
	if(seqlist_is_full(seq) == 1)
		return -1;

	//腾出 pos 位置
	int i ;
	for(i=seq->last;i>=pos;i--)
		seq->data[i+1] = seq->data[i];
	//将data值放在pos位置
	seq->data[pos] = data;
	seq->last++;
	return 0;
}

//按位置删除顺序表中的元素
/*******************************************************
Description:按位置删除顺序表中的元素
	int deleteSeqlistByPos(seqlist *seq, int pos);
Argument:
	seq:顺序表的首地址
	pos:要删除的位置 pos从0开始
Return:
	成功：0
	失败：-1
*******************************************************/
int deleteSeqlistByPos(seqlist *seq, int pos)
{
	if(NULL == seq)//判断指针是否有效
		return -1;
	int len = getLengthSeqlist(seq);//求顺序表中的元素个数
	
	if(pos < 0 || pos > len-1)//判断位置是否有效
		return -1;
	//判断顺序表是否为空
	if(seqlist_is_empty(seq) == 1)
		return -1;
	//将pos后所有的有效元素依次向前移动一个位置
	int i ;
	for(i=pos;i<seq->last;i++)
		seq->data[i] = seq->data[i+1];

	seq->last--;//最后一个元素下标自减

	return 0;
}



//按位置查找顺序表中的元素
data_t findSeqlistByPos(seqlist *seq, int pos)
{
	if(NULL == seq)
		return -1;
	if(seqlist_is_empty(seq))
		return -1;
	if(pos < 0 || pos > seq->last)
		return -1;

	return seq->data[pos];
}

//按值查找顺序表中的元素，返回查找到的值为data的元素的下标
int findSeqlistByData(seqlist *seq, data_t data)
{
	if(NULL == seq)
		return -1;
	if(seqlist_is_empty(seq))
		return -1;
	int i = 0;
	for(i=0;i<=seq->last;i++)
	{
		if(seq->data[i] == data)
			return i;
	}
	return -1;
}

//按值删除顺序表中的元素
int deleteSeqlistByData(seqlist *seq, data_t data)
{
	int pos = findSeqlistByData(seq, data);
	deleteSeqlistByPos(seq,pos);
	return 0;
}

//按位置修改顺序表中的元素值
int changeSeqlistByPos(seqlist *seq, int pos, data_t new_data)
{
	if(NULL == seq)
		return -1;
	if(seqlist_is_empty(seq))
		return -1;
	if(pos < 0 || pos > seq->last)
		return -1;
	seq->data[pos] = new_data;
	return 0;
}

//按值修改顺序表中的元素值
int changeSeqlistByData(seqlist *seq, data_t old_data, data_t new_data)
{
	int pos = findSeqlistByData(seq, old_data);
	changeSeqlistByPos(seq,pos, new_data);

	return 0;
}

//清空顺序表
int clearSeqlist(seqlist *seq)
{
	if(NULL == seq)
		return -1;
	
	seq->last = -1;
	return 0;
}

//销毁顺序表
void destorySeqlist(seqlist **seq)
{
	free(*seq);
	*seq = NULL;
}


//打印顺序表中的各个元素值
void printSeqlist(seqlist *seq)
{
	if(NULL == seq)
		return ;
	int i = 0;
	for(i=0;i<seq->last+1;i++)
		printf("%d ",seq->data[i]);
	printf("\n");
}

#endif


