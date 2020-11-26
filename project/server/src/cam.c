#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <jpeglib.h>
#include <pthread.h>

#include <sys/mman.h>
#include <sys/ioctl.h>

#include <linux/videodev2.h>
#include "camera.h"
#include "convert.h"

//填空， 摄像头的文件路径
#define CAM_DEV_PATH	"/dev/video0"

struct jpg_buf_t jpg;
extern pthread_mutex_t cam_mutex;

//填空， 摄像头线程函数
void *thread_cam(void *arg)
{
	int i;
	int fd;
	int ret;
	unsigned int width;
	unsigned int height;
	unsigned int size;
	unsigned int index;
	char yuv[1024*1024];
	char rgb[1024*1024];
	unsigned int j;

	width = 640;
	height = 480;

	//填空， 摄像头初始化函数
	fd = camera_init("/dev/video0",&width,&height,&size)	;
	printf("cam: width-%d, height-%d\n", width, height);
//	rgb = malloc(width * height * 3);

	//填空， 开启采集函数
	ret = camera_start(fd)	;
	if (ret == -1)
		pthread_exit(NULL);

	//填空， 格式转换初始化函数
	convert_rgb_to_jpg_init()	;

	//测试代码
	for (i = 0; i < 2 * REQBUFS_COUNT; i++) {
		ret = camera_dqbuf(fd, yuv, &size, &index);
		if (ret == -1)
			pthread_exit(NULL);

		ret = camera_eqbuf(fd, index);
		if (ret == -1)
			pthread_exit(NULL);
	}


	while(1) {
		//填空， 出队函数
		ret = camera_dqbuf(fd,yuv,&size,&index)	;
		if (ret == -1)
			pthread_exit(NULL);

		//填空， 格式转换yuv --> rgb
		convert_yuv_to_rgb(yuv,rgb,width,height,24)	;
		
		pthread_mutex_lock(&cam_mutex);
		//填空， 格式转换 rgb --> jpg
		jpg.jpg_size = convert_rgb_to_jpg_work(rgb,jpg.jpg_buf,width,height,24,80)	;
		pthread_mutex_unlock(&cam_mutex);

		int fd1 = open("2.jpg", O_WRONLY|O_CREAT, 0777);
		write(fd1, jpg.jpg_buf, jpg.jpg_size);

		//填空， 入队函数
		ret = camera_eqbuf(fd, index);
		if (ret == -1)
			pthread_exit(NULL);
	};
	
	//填空，格式转换结束函数
	convert_rgb_to_jpg_exit()	;
	free(rgb);

	//填空，停止采集函数
	ret = camera_stop(fd)	;
	if (ret == -1)
		pthread_exit(NULL);

	//填空，退出摄像头函数
	ret = camera_exit(fd)	;
	if (ret == -1)
		pthread_exit(NULL);
	
//	uninit_lcd();

	printf("camera thread exited\n");
	pthread_exit(NULL);
}
