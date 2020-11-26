#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{
	//创建套接字, IPV4的地址族, 套接字类型, 0
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		perror("socket");
		return -1;
	}

	//结构体: 保存服务器的IP地址和端口号
	struct sockaddr_in serveraddr = {0};
	serveraddr.sin_family = AF_INET;
	//主机字节序转化成网络字节序
	serveraddr.sin_port = htons(8888);
	//serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_addr.s_addr = inet_addr("0.0.0.0");

	int len = sizeof(serveraddr);

	int ret = connect(sockfd, (struct sockaddr *)&serveraddr, len);
	if( ret < 0)
	{
		perror("connect");
		return -1;
	}

	printf("connect success!\n");

	char buf[100] = {0};

	while(1)
	{
		printf("input> ");
		fflush(stdout);
		gets(buf);

		write(sockfd, buf, 100);
	
	}

	return 0;
}
