#include <stdio.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <string.h>

#define N 128
struct msg
{
	long mtype;
	char mdata[N];
};

int main(int argc, const char *argv[])
{
	key_t key = ftok("./", 'a');
	if(-1 == key)
	{
		perror("ftok");
		return -1;
	}

	int msgid = msgget(key, IPC_CREAT|0666);
	if(-1 == msgid)
	{
		perror("msgget");
	}

	struct msg msg1;
	msg1.mtype = 100;
	strcpy(msg1.mdata, "hello, world!");

	msgsnd(msgid,(void*)&msg1, N, 0);
	return 0;
}
