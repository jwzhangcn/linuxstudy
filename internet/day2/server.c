
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[])
{
	//socket
	char buf[64] = "";
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(-1 == sockfd){
		perror("socket");
		return -1
	}
	
	//bind
	struct sockaddr_in myaddr;
	memset(&myaddr, 0 ,sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(8080);
	myaddr.sin_addr = inet_addr("192.168.2.193");
	
	if(-1 == bind(sockfd, (struct sockaddr*)&myaddr, sizeof(myaddr))){
		perror("bind");
		return -1
	}
	//recvfrom,sendto
	struct sockaddr_in cliaddr;
	int cliaddrlen = sizeof(cliaddr);
	while(1){
		memset(buf, 0 ,sizeof(buf));
		int ret = recvfrom(sockfd, buf, sizeof(buf), 0,\
				(struct sockaddr*)&cliaddr, &cliaddrlen);
		if(-1 == ret){
			perror("recvfrom");
			return -1;
		}
		else{
			printf("recv> %s\n",buf);
		}
	}
	//close
	return 0;
}
