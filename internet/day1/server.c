#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
int main(int argc, const char *argv[])
{
	//socket()
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == sockfd)
	{
		perror("socket");
		return -1;
	}
	printf("socket...................\n");
	//bind()
	struct sockaddr_in myaddr;
	memset(&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(8888);
	myaddr.sin_addr.s_addr = inet_addr("192.168.2.193");
//端口复用
	int opt = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&opt,
	sizeof(opt));
	if(-1 == bind(sockfd, (struct sockaddr*)&myaddr, sizeof(myaddr)))
	{
		perror("bind");
		goto err;
	}
	printf("bind..................\n");

	//listen()
	if(-1 == listen(sockfd, 8)){
		perror ("listen");
		goto err;
	}
	printf("listen...................\n");

	//accept()
	int connfd = accept(sockfd, NULL, NULL);
	if(-1 == connfd)
	{
		perror("accept");
		goto err;
	}
	printf("listen.....................\n");
	//read()/write()
	char buf[64] = "";
	int ret;
	while(1)
	{
		memset(buf, 0 ,sizeof(buf));
		ret = read(connfd, buf, sizeof(buf));
		if(-1 == ret)
		{
			perror("read");
			goto err;
		}
		else if(0 == ret){
			printf("connect closed!\n");
			break;
		}
		else{
			printf("recv> %s\n",buf);
			fflush(NULL);
		}
	}
	//close()
	close(sockfd);
	close(connfd);
err:
	close(sockfd);
	return 0;
}
