#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[])
{
	float c,f;
	printf("输入一个华式温度：");
	scanf("%f",&f);
	printf("摄氏度为：%.2f\n",c=5.0/9*(f-32));
	return 0;
}
