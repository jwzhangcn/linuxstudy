#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myhead.h"

int recvbuf[32] = "";

int connect_to_server(char *ipaddr, char *port)
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == sockfd){
		return -1;
	}
	printf("socket......\n");
//绑定服务器地址和端口
	struct sockaddr_in srvaddr;
	memset(&srvaddr, 0, sizeof(srvaddr));
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_addr.s_addr = inet_addr(ipaddr);
	srvaddr.sin_port = htons(atoi(port));

	if(-1 == connect(sockfd, (struct sockaddr*)&srvaddr, sizeof(srvaddr))){
		perror("connect");
		return -1;
	}

	return sockfd;
}

void do_list(){
	
	int sockfd = connect_to_server("192.168.2.193", "8080");
	if(-1 == sockfd){
		printf("connect_to_server failed!\n");
	}
	char buf[] = "list";
	send(sockfd, buf, sizeof(buf), 0);
	int ret = 0;
	while(1){
		memset(&recvbuf, 0, sizeof(recvbuf));
		ret = recv(sockfd, recvbuf, sizeof(recvbuf), 0);
		if(ret == 0){
			break;
		}
		printf("tftpfile: %s\n", recvbuf);
	}
}

int main(int argc, const char *argv[])
{
	char order[16] = "";
	while(1){
		printf("send> ");
		fgets(order, sizeof(order), stdin);
		if(0 == strncmp(order, "list", 4))
			do_list();
		if(0 == strncmp(order, "quit", 4))
			break;
	}
	
	return 0;
}
