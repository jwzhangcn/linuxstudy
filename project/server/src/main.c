#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#include "camera.h"
#include "zgb.h"
#include "srv_qt.h"

pthread_t cam_tid;
pthread_t zgb_tid;
pthread_t srv_tid;

pthread_mutex_t cam_mutex;
pthread_mutex_t zgb_mutex;
pthread_mutex_t cmd_mutex;

extern struct jpg_buf_t jpg;
extern struct zgb_buf_t zgb;

int main(int argc, char *argv[])
{
	int ret;

	//填空，互斥锁初始化
	pthread_mutex_init(&cam_mutex, NULL);
	pthread_mutex_init(&zgb_mutex, NULL);
	pthread_mutex_init(&cmd_mutex, NULL);

	/* camera thread */
	//填空 ， 开一个摄像头线程
	ret = pthread_create(&cam_tid, NULL, thread_cam, NULL);
	if (ret) {
		errno = ret;
		perror("create camera thread");
		exit(EXIT_FAILURE);
	} else
		printf("create camera thread success\n");
	//填空， 回收摄像头线程资源
	ret = pthread_detach(cam_tid);
	if (ret) {
		errno = ret;
		perror("detach camera thread");
		exit(EXIT_FAILURE);
	} else
		printf("detach camera thread success\n");

	/* zigbee thread */
	//填空 ， 开一个zigbee线程
	ret = pthread_create(&zgb_tid, NULL, thread_zgb, NULL);
	if (ret) {
		errno = ret;
		perror("create zigbee thread");
		exit(EXIT_FAILURE);
	} else
		printf("create zigbee thread success\n");

	//填空， 回收zigbee线程资源
	ret = pthread_detach(zgb_tid);
	if (ret) {
		errno = ret;
		perror("detach zigbee thread");
		exit(EXIT_FAILURE);
	} else
		printf("detach zigbee thread success\n");

	sleep(3);
	
	/* qt server thread */
	//填空 ， 开一个服务器线程
	ret = pthread_create(&srv_tid, NULL, thread_srv, NULL);
	if (ret) {
		errno = ret;
		perror("create qt server thread\n");
		exit(EXIT_FAILURE);
	} else
		printf("create qt server thread success\n");

	//填空， 回收服务器线程资源
	ret = pthread_detach(srv_tid);
	if (ret) {
		errno = ret;
		perror("detach qt server thread\n");
		exit(EXIT_FAILURE);
	} else
		printf("detach qt server thread success\n");

	/* main thread, process environment data form m0 board or process short message */
	while (1) {
		sleep(1);
	}

	pthread_mutex_destroy(&cam_mutex);
	pthread_mutex_destroy(&zgb_mutex);

	exit(EXIT_SUCCESS);
}
