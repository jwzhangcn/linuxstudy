#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{

	int fd = open("1.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if(fd < 0)
		perror("open");

	while(1)
	{
		char str[100] = "";
		printf("输入要写入的内容，输入quit退出：");
		gets(str);

		if(strcmp(str,"quit") != 0)
		{
			int n = write(fd, str, strlen(str));
			printf("写入成功，写入 %d 字节\n",n);
		}
		else
		{
			printf("退出\n");
			return;
		}
	}

	return 0;
}
