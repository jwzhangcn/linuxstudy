#ifndef __serial_op_h__
#define __serial_op_h__

#include<stdio.h>      /*标准输入输出定义*/ 
#include<stdlib.h>     /*标准函数库定义*/  
#include<unistd.h>     /*Unix 标准函数定义*/  
#include<sys/types.h>   
#include<sys/stat.h>     
#include<fcntl.h>      /*文件控制定义*/  
#include<termios.h>    /*PPSIX 终端控制定义*/  
#include<errno.h>      /*错误号定义*/  
#include<string.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern int errno;

#include <poll.h>
#include <sys/ioctl.h>

#define FALSE  -1  
#define TRUE   0 

#define ON 1
#define OFF 0

#define eprintf(x)  printf("%s   ===file:%s     ===line:%d   ===%s \n",x,__FILE__,__LINE__,strerror(errno))

/***************************************************
Description:打开串口设备
	int serial_open(char *devpath);
Input:
	dev_path:串口设备文件名的首地址 "/dev/ttyS0"
Output:
	None
Return:
	成功：串口文件描述符
	失败：-1 
***************************************************/
int serial_open(char *devpath);

/***************************************************
Description:串口设置
	int serial_set(int fd, int speed, int flow_ctrl, int databits, int stopbits, int parity);
Input:
	serial_fd：open_serial函数的返回值
	speed： 波特率 115200
	flow_ctrl:流控 0
	databits: 数据位 8
	stopbits:停止位 1
	parity: 奇偶校验位 'N'
Output:
	None
Return:
	成功：0
	失败：-1 
***************************************************/
int serial_set(int fd, int speed, int flow_ctrl, int databits, int stopbits, int parity);

//串口接收数据
int serial_recv(int fd, void *p,int data_len, int timeout);
//串口发送数据
int serial_send(int fd, void *p,int data_len, int timeout);

//串口关闭
void serial_close(int fd);


#endif
