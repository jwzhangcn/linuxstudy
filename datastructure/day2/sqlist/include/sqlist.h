#ifndef _SQLIST_H_
#define _SQLIST_H_
#define SIZE 100
typedef int data_t;

//构造顺序表
typedef struct list{
	data_t data[SIZE];
	int last;//记录当前顺序表中最后一个元素的下标
}seqlist;//给 struct list 取别名为 seqlist

seqlist * createSeqlist();
int seqlist_is_empty(seqlist *seq);
int seqlist_is_full(seqlist *seq);
int getLengthSeqlist(seqlist *seq);
int insertSeqlistByPos(seqlist *seq, int pos, data_t data);
int deleteSeqlistByPos(seqlist *seq, int pos);
data_t findSeqlistByPos(seqlist *seq, int pos);
int findSeqlistByData(seqlist *seq, data_t data);
int deleteSeqlistByData(seqlist *seq, data_t data);
int changeSeqlistByPos(seqlist *seq, int pos, data_t new_data);
int changeSeqlistByData(seqlist *seq, data_t old_data, data_t new_data);
int clearSeqlist(seqlist *seq);
void destorySeqlist(seqlist **seq);
void printSeqlist(seqlist *seq);
#endif
