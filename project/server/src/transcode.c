#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "iconv.h"
static iconv_t cd;

/*********************************************************************************  
* Description：  字符转换模块初始化
* Input:         无
* Output:        无
* Return:       无
* Others:       无
**********************************************************************************/
int transcodeInit(void)
{
	/*开启iconv*/
	cd = iconv_open("GBK", "UTF-8");   //把UTF-8转换为GBK
	if (cd == (iconv_t)-1) 
	{
		perror("iconv_open");
		return -1;
	}
	return 0;
}

/*********************************************************************************  
* Description：  字符转换模块退出
* Input:         无
* Output:        无
* Return:       无
* Others:       无
**********************************************************************************/
void transcodeExit(void)
{
	iconv_close(cd);
}

/*********************************************************************************  
* Description：  字符转换模块转换
* Input:         无
* Output:        无
* Return:       无
* Others:       无
**********************************************************************************/
int transcode(const char *inbuf, char *outbuf) 
{
	int ret=0;
	int inlen;
	char tmpbuf[1024]={0};
	char* p = tmpbuf;
	char* in = (char*)inbuf;
	int outlen;

	inlen = strlen(inbuf)+1;
	outlen = 1024;	
	/*把UTF-8转换为GBK*/
	ret = iconv(cd, &in, (size_t*)&inlen, &p, (size_t*)&outlen);
	if (ret < 0) 
	{
		iconv_close(cd);
		cd = iconv_open("GBK", "UTF-8");
		usleep(1000);
		ret = iconv(cd, &in, (size_t*)&inlen, &p, (size_t*)&outlen);
		if (ret == -1) 
		{
			printf("ivonv error .\n");
			return -1;
		}
	}
	outlen =strlen(tmpbuf); 			//需要发送文本的长度
	
	/*合成语音的固定格式*/           
	outbuf[0] = 0xFD ; 			//构造帧头FD
	outbuf[1] = ((outlen+2)>>8)&0xff; 	//构造数据区长度的高字节
	outbuf[2] = (outlen+2)&0xff; 		//构造数据区长度的低字节
	outbuf[3] = 0x01 ; 			//构造命令字：合成播放命令		 		 
	outbuf[4] = 0x01;       //文本编码格式：GBK 
	memcpy(&outbuf[5], tmpbuf, outlen+5);
	return 0;
}

#if 0
#include <fcntl.h>
#include <assert.h>
#include <termios.h>
int serial_init(const char *devpath, int baudrate)
{
	int fd;
	struct termios oldtio, newtio;

	assert(devpath != NULL);

	fd = open(devpath, O_RDWR | O_NOCTTY); 
	if (fd == -1) {
		perror("serial->open");
		return -1;
	}

	tcgetattr(fd, &oldtio);		/* save current port settings */

	memset(&newtio, 0, sizeof(newtio));
	newtio.c_cflag = baudrate | CS8 | CLOCAL | CREAD;
	newtio.c_iflag = IGNPAR;
	newtio.c_oflag = 0;

	newtio.c_lflag = 0;		/* set input mode (non-canonical, no echo,...) */

	newtio.c_cc[VTIME] = 40;	/* set timeout value, n * 0.1 S */
	newtio.c_cc[VMIN] = 0;

	tcflush(fd, TCIFLUSH);
	tcsetattr(fd, TCSANOW, &newtio);

	return fd;
}

void main(void)
{
	char buf[1024]={0};
	int i = 0;
	int j = 0;
	transcodeInit();
	//for(j=0;j<100;j++)
	{
		transcode("　　长颈鹿渴了，走到池塘边喝水。他叉开前腿，低下身子，弯下脖子，伸出尖尖的舌头，一下又一下，舔到清水，脖子一昂，咽进肚子里。　　青蛙见了，感概地说：“你这样喝水，真累!”　　天旱的时候，池水干了。长颈鹿昂起长长的脖子，嘴巴伸到树梢上，牙齿啃一啃，嫩绿的树叶就成了他的饮料。嫩叶中藏着许多水分，味道甜甜的，又解渴，又提神。　　青蛙见了，感慨地说：“你这样喝水，真好!”",buf);
		printf("buf is : ");
		for(i=0;i<256;i++)
			printf("%x ",buf[i]);
		printf("\n");
	}
	
	char cmd[] = {0xFD, 0x00, 0x01, 0x21}; /*vic 开始命令*/

	int fd = serial_init("/dev/ttyUSB0", B9600);
	write(fd, cmd, sizeof(cmd));
	memset(cmd, 0, sizeof(cmd));
	read(fd, cmd, sizeof(cmd));
	if(cmd[0] == 0x4f) {
		
	} else {
		fd = serial_init("/dev/ttyUSB1", B9600);
	}
	
	write(fd,buf,1024);

	transcodeExit();

}
#endif
