#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[])
{
	int a,b,c,n;
	printf("输入一个百位数：");
	scanf("%d",&n);
	a=n%10;
	b=n/10%10;
	c=n/100;
	printf("个位：%d 十位：%d 百位：%d",a,b,c);
	return 0;
}
