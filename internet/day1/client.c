
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
int main(int argc, const char *argv[]){
	
	//socket
	char buf[64] = "";
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == sockfd){
		perror("socket");
		return -1;
	}
	printf("socket......\n");

	//connect
	struct sockaddr_in myaddr;
	memset(&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(8888);
	myaddr.sin_addr.s_addr = inet_addr("192.168.2.193");

	if(-1 == connect(sockfd, (struct sockaddr*)&myaddr, sizeof(myaddr))){
		perror("connect");
		goto err;
	}
	printf("connected......\n");
	
	//read()/write()
	while(1)
	{
		memset(buf, 0 ,sizeof(buf));
		printf("send> ");
		gets(buf);
		if(0 != strcmp(buf, "quit"))
			write(sockfd, buf, sizeof(buf));
		else
			break;
	}
	//close
	close(sockfd);
	//err
err:
	close(sockfd);

	return 0;
}
