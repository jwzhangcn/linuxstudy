#include <stdio.h>
#include <stdlib.h>
#include <string.h>      
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>                
#include <sys/socket.h>
#include "camera.h"   
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>

#define SIZE 64
int server_init(unsigned char *ipaddr,unsigned short port,int backlog)
{
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0)
	{
		perror("socket");
		return -1;
	}
	printf("socket=%d",sockfd);

	int on = 1;
	setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));

	struct sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	saddr.sin_addr.s_addr = inet_addr(ipaddr);

	socklen_t slen = sizeof(saddr);
	int ret = bind(sockfd,(struct sockaddr *)&saddr,slen);
	if(ret < 0)
	{
		perror("bind");
		return -1;
	}
	printf("bind success!");

	ret = listen(sockfd,backlog);
	if(ret < 0)
	{
		perror("listen");
		return -1;
	}
	printf("listen success!");
	return sockfd;
}
int main(int argc, const char *argv[])
{
	unsigned int width = 640;
	unsigned int height = 480;
	unsigned int size = 0;
	unsigned int ismjpeg = 0;
	char scbuf[SIZE]={0};
	char headbuf[SIZE]={0};
	unsigned int index = 0;
	int piclen = 6479;
	char * picbuf = NULL;

	int camera_fd = camera_init("/dev/video0",&width,&height,&size,&ismjpeg);
	if(camera_fd < 0)
	{
		perror("init");
		return -1;
	}
	printf("camera init success!");

	int ret = camera_start(camera_fd);
	if(ret<0)
	{
		perror("start");
		return -1;
	}
	printf("camera start success!");

	int sockfd = server_init((unsigned char *)argv[1],8888,10);
	if(sockfd < 0)
	{
		perror("server_int");
		return -1;
	}
	printf("waiting for connect---------------------");

	int rws = accept(sockfd,NULL,NULL);
	if(rws < 0)
	{
		perror("accept");
		return -1;
	}
	printf("[%d] has accepted",rws);
	
	while(1)
	{
		
		ret = read(rws,scbuf,sizeof(scbuf));
		if(ret < 0)
		{
			perror("read");
			break;
		}
		if(ret == 0)
		{
			printf("client has closed");
			break;
		}
		if(strncmp(scbuf,"pic",3)==0)
		{
			ret = camera_dqbuf(camera_fd,(void**)&picbuf,&piclen,&index);
			if(ret < 0)
			{
				perror("camera_dqbuf");
				break;
			}
			sprintf(headbuf,"%d",piclen);
			ret = write(rws,headbuf,sizeof(headbuf));
			if(ret < 0)
			{
				perror("write piclen");
				break;
			}
			ret = write(rws,picbuf,piclen);
			if(ret < 0)
			{
				perror("write picbuf");
				break;
			}
			camera_eqbuf(camera_fd,index);
		}

	}
	camera_stop(camera_fd);
	camera_exit(camera_fd);
	close(rws);
	close(sockfd);
	return 0;
}
