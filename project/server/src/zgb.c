#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pthread.h>

#include "serial.h"
#include "zgb.h"
#include "turing.h"

extern pthread_mutex_t zgb_mutex;
extern pthread_mutex_t cmd_mutex;
struct zgb_buf_t zgb; //环境参数存放位置
char cmd[1024];   //存放M0的控制命令
int zgbfd, voifd;
pthread_t thread1, thread2;
unsigned char buf[36];
unsigned char buf1[36];

void buf_to_zgb()
{
	//填空， 加锁函数
	pthread_mutex_lock(&zgb_mutex);   
	zgb.tmp = buf[5] + buf[4] / 10;
	zgb.hum = buf[7] + buf[6] / 10;
	zgb.ill = (buf[23] << 24) + (buf[22] << 16) + (buf[21] << 8) + buf[20];
	printf("%d, %d, %d\n", zgb.tmp, zgb.hum, zgb.ill);
	//填空， 解锁函数
	pthread_mutex_unlock(&zgb_mutex);  
}

void send_cmd(char *order)
{
	write(1, order, 1024);

	//填空， 控制命令格式，5字节初始化
	unsigned char buf1[36] = {0xDD, 0x03, 0x24, 0x00, 0x00};
	char out[1024];
	int ret; 
	int flag = 0;
	int on = 0;
	//填空， 字符串比较函数
	if (strcmp(order, "开灯") == 0)
	{
		//ret = turing("开灯", out);
		transcode("开灯", out);
		on = 0;
	}//填空， 字符串比较函数
	else if (strcmp(order, "关灯") == 0)
	{
		//ret = turing("关灯",out);
		transcode("关灯", out);
		on = 1;
	}//填空， 字符串比较函数
	else if (strcmp(order, "开风扇") == 0)
	{
		//ret = turing("开风扇",out);
		transcode("开风扇", out);
		on = 4;
	}//填空， 字符串比较函数
	else if (strcmp(order, "关风扇") == 0)
	{
		//ret = turing("关风扇",out);
		transcode("关风扇", out);
		on = 8;
	}//填空， 字符串比较函数
	else if (strcmp(order, "报警") == 0)
	{
		//ret = turing("报警",out);
		transcode("报警", out);
		on = 2;
	}//填空， 字符串比较函数
	else if (strcmp(order, "解除警报") == 0)
	{
		//ret = turing("解除警报",out);
		transcode("解除警报", out);
		on = 3;
	}
	else
	{
		ret = turing(order, out);
		//transcode(order, out);
		flag = 1;
	}
	if (0 > write(voifd, out, 1024))
	{
		perror("write voice");
		return;
	}

	if (1 == flag)
		return;
	buf1[1] = buf[1];
	buf1[4] = on;
	int i;
	for (i = 0; i < 5; i++)
	{
		printf("    %x ", buf1[i]);	
	}
	printf("\n");
	printf("**************%s\n", buf1);

	//填空， 串口通信，发送控制命令
	serial_send_exact_nbytes(zgbfd, buf1, 36);
}

void *recv_env(void *arg)
{
	int ret;
	while (1) {
		//填空， 串口通信，接收环境信息
		ret = serial_recv_exact_nbytes(zgbfd, buf, 36);
		if (buf[0] != 0xBB) {
			continue;
		}
		buf_to_zgb(buf);
		sleep(1);
	}
}

void *recv_cmd(void *arg)
{
	char order[1024];
	while (1)
	{
		pthread_mutex_lock(&cmd_mutex);
		if (cmd[0] == 0x0) {
			pthread_mutex_unlock(&cmd_mutex);
			continue;
		}
		memcpy(order, cmd, sizeof(order));
		cmd[0] = 0x0;
		pthread_mutex_unlock(&cmd_mutex);
		//send_cmd(order);
	}
}

void *thread_zgb(void *arg)
{
	//填空， 串口初始化函数  
	zgbfd = serial_init("/dev/ttyUSB0", 115200); //M0
	if (zgbfd < 0) {
		perror("serial_init M0");
		pthread_exit(NULL);
	}
	//填空， 串口初始化函数 
	voifd = serial_init("/dev/ttyUSB1", 9600); //语音
	if (voifd < 0) {
		perror("serial_init voice");
		pthread_exit(NULL);
	}
	sleep(2);
	transcodeInit();
	//填空， 创建线程函数
	if (0 != pthread_create(&thread1, NULL, recv_env, NULL)){
		perror("pthread_create");
		pthread_exit(NULL);
	}
	pthread_detach(thread1);

	//填空， 创建线程函数
	if (0 != pthread_create(&thread2, NULL, recv_cmd, NULL)){
		perror("pthread_create");
		pthread_exit(NULL);

	}
	pthread_detach(thread2);

	while (1);	

	//填空，串口退出函数
	if (0 > serial_exit(zgbfd)) {
		perror("serial_exit");
		pthread_exit(NULL);
	}
	//填空，串口退出函数
	if (0 > serial_exit(voifd)) {
		perror("serial_exit");
		pthread_exit(NULL);
	}
	
	printf("zigbee task exited\n");
	pthread_exit(NULL);
}
