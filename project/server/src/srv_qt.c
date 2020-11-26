/*===============================================================
*   Copyright (C) 2017 All rights reserved.
*   
*   文件名称：server.c
*   创 建 者：liujing
*   创建日期：2017年02月09日
*   描    述：
*
*   更新日志：
*
================================================================*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include "camera.h"
#include "zgb.h"

extern pthread_mutex_t cam_mutex;
extern pthread_mutex_t zgb_mutex;
extern pthread_mutex_t cmd_mutex;
extern struct jpg_buf_t jpg;
extern struct zgb_buf_t zgb;
extern char cmd[1024];

int myread(int fd, char *buf, int size)
{
	int count = 0;
	int ret;
	while (count < size) {
		ret = read(fd, buf+count, size-count);
		count += ret;
	}
	return count;
}

int mywrite(int fd, char *buf, int size)
{
	int count = 0;
	int ret;
	while (count < size) {
		ret = write(fd, buf+count, size-count);
		count += ret;
	}
	return count;
}

void process_qt(int connfd)
{
	char order[1024];
	char buf[20];
	int ret = 0;
	
	while (1) {
		memset(order, 0, sizeof(order));
		//填空， 自己写的接收数据函数
		ret = myread(connfd, order, sizeof(order));
		if (ret != sizeof(order)) {
			perror("read order");
			break;
		}
		//填空， 字符串中找子字符串函数， 图片的格式头
		if (strstr(order, "pic")) {
			memset(buf, 0, sizeof(buf));
			
			pthread_mutex_lock(&cam_mutex);
			
			sprintf(buf, "%d", jpg.jpg_size);
//			puts(buf);

			//填空， 自己写的发送数据函数
			ret = mywrite(connfd, buf, sizeof(buf));
			if (ret != sizeof(buf)) {
				perror("write len");
				break;
			}
			//填空， 自己写的发送数据函数
			ret = mywrite(connfd, jpg.jpg_buf, jpg.jpg_size);
			if (ret != jpg.jpg_size) {
				perror("write pic");
				break;
			}
			pthread_mutex_unlock(&cam_mutex);
		}//填空， 字符串中找子字符串函数， 环境信息的格式头
		else if (strstr(order, "env")) {
			memset(buf, 0, sizeof(buf));
		
			pthread_mutex_lock(&zgb_mutex);
			sprintf(buf, "%d&%d&%d", zgb.tmp, zgb.hum, zgb.ill);
# if 1
			printf("%d, %d, %d\n", zgb.tmp, zgb.hum, zgb.ill);
#endif	
			pthread_mutex_unlock(&zgb_mutex);
			
			//填空， 自己写的发送数据函数
			ret = mywrite(connfd, buf, sizeof(buf));
			if (ret != sizeof(buf)) {
				perror("mywrite");
				break;
			}
		}
		else {
			pthread_mutex_lock(&cmd_mutex);
			memcpy(cmd, order, sizeof(order));	
			printf("speech cmd:%s\n", cmd);
			send_cmd(cmd);
			pthread_mutex_unlock(&cmd_mutex);
		}
	}
}

void *thread_srv(void *arg)
{
	/*1. 创建套接字*/
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	//填空， 创建套接字
	if (0 > sockfd) {
		perror("socket");
		pthread_exit(NULL);
	}
	printf("socket success!\n");

	int on = 1;
	//填空， 端口复用
	if (0 > setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) ) {
		perror("setsocket");
		pthread_exit(NULL);
	}
	
	/*2. 绑定本机地址和端口*/
	struct sockaddr_in myaddr;
	memset(&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	//填空， 端口号：主机字节序转网络字节序
	myaddr.sin_port = htons(8080);
	//myaddr.sin_addr.s_addr = inet_addr("182.148.27.195");
	//填空， IP地址：主机字节序转网络字节序
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	//填空， 绑定本机地址和端口号
	if (0 > bind(sockfd, (struct sockaddr*)&myaddr, sizeof(myaddr))){
		perror("bind");
		pthread_exit(NULL);
	}
	printf("bind success!\n");

	/*3. 设置监听套接字*/
	//填空， 设置监听套接字
	if (0 >	listen(sockfd, 1024)) {
		perror("listen");
		pthread_exit(NULL);
	}
	printf("listen.................\n");

	/*4. 接收客户端发来的连接请求*/
	int connfd;
	//填空， 等待客户端连接
	if (0 > (connfd = accept(sockfd, NULL, NULL))) {
		perror("accpet");
		pthread_exit(NULL);
	}
	printf("accept success!\n");

	//填空， 框架已经搭好了，可以进行收发数据了
	process_qt(connfd);

	close(connfd);
	close(sockfd);

	return 0;
}
