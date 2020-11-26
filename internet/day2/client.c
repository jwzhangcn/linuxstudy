#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
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
	struct sockaddr_in srvaddr;
	memset(&srvaddr, 0 ,sizeof(srvaddr));
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_port = htons(8080);
	srvaddr.sin_addr = inet_addr("192.168.2.193");
	
	
	//recvfrom,sendto
	while(1)
	{
		memset(buf, 0 ,sizeof(buf));
		fgets(buf, sizeof(buf), stdin);
		sendto(sockfd, buf, sizeof(buf), 0,\
				(struct sockaddr*)&srvaddr, sizeof(srvaddr));
	}
	//close
	return 0;
}
