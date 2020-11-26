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
	//1. 创建套接字, IPV4的地址族, 套接字类型, 0
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		perror("socket");
		return -1;
	}

	//2. 结构体: 保存服务器的IP地址和端口号
	struct sockaddr_in serveraddr = {0};
	serveraddr.sin_family = AF_INET;
	//主机字节序转化成网络字节序
	serveraddr.sin_port = htons(8888);
	//serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_addr.s_addr = inet_addr("0.0.0.0");

	int len = sizeof(serveraddr);
	//3. 绑定IP地址和端口号
	int ret = bind(sockfd, (struct sockaddr *)&serveraddr, len);
	if( ret < 0)
	{
		perror("bind");
		return -1;
	}
	printf("bind success!\n");

	//4. 设置监听套接字
	ret = listen(sockfd, 10);
	if(ret < 0)
	{
		perror("listen");
		return -1;
	}
	printf("listen success!\n");

xxx:
	printf("wait for a client............\n");

	//5. 等待客户端连接
	int rws = accept(sockfd, NULL, NULL);
	if(rws < 0)
	{
		perror("accept");
		return -1;
	}
	printf("accept success!\n");


	char buf[100] ={0};
	while(1)
	{
		int n = read(rws, buf, sizeof(buf));
		if(n <= 0)
		{
			goto xxx;		
		}

		printf("buf = %s\n", buf);
	}

	return 0;
}
