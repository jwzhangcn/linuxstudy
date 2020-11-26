#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myhead.h"

char retbuf[32] = "";

int do_list(){
	DIR *dir = opendir("./");
	struct dirent *tftpfile;
	memset(retbuf, 0, sizeof(retbuf));
	while (NULL != (tftpfile = readdir(dir))) 
		sprintf(retbuf, "%s  %s", retbuf, tftpfile->d_name);
	while(1){
		if(0 > send(connfd, retbuf, sizeof(retbuf), 0)){
			perror("send failed!\n");
			return -1;
		}
	}
}

int main(int argc, char *argv[]){
//socket
	static int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == sockfd){
		perror("socket");
		return -1;
	}
	printf("socket......\n");

//端口复用	
	int opt = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&opt, sizeof(opt));
//bind()
	struct sockaddr_in myaddr;
	memset(&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(8080);
	myaddr.sin_addr.s_addr = inet_addr("192.168.2.193");
	
	if(-1 == bind(sockfd, (struct sockaddr*)&myaddr, sizeof(myaddr))){
		perror("bind");
		return -1;
	}
	printf("bind......\n");

//listen()
	if(-1 == listen(sockfd, 8)){
		perror("listen\n");
		return -1;
	}

	printf("listen......\n");

//accept()
	//客户端信息
	struct sockaddr_in cliaddr;
	memset(&cliaddr, 0, sizeof(cliaddr));
	int cliaddr_len = sizeof(cliaddr);

	int connfd = accept(sockfd, (struct sockaddr*)&cliaddr, &cliaddr_len); 
	if(-1 == connfd){
		perror("connect");
		return -1;
	}

	printf("accept......\n");

	char buf[64] = "";
	int ret;
	while(1){
		memset(buf, 0, sizeof(buf));
		ret = recv(connfd, buf, sizeof(buf), 0);
		if(0 == ret){
			printf("connect lost!\n");
			return -1;
		}
		if(0 == strcmp(buf,"list"))
			do_list();
	}
	
	return 0;
}
