#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, const char *argv[])
{
	FILE *fp = fopen("1.txt","a+");
	time_t timer;
	int count = 0;
	char str[24] = "";

	while(1)
	{
		time(&timer);
		struct tm *t = localtime(&timer);
		
		count++;
		sprintf(str, "%d,  %4d-%2d-%2d %2d:%2d:%2d\n", count, t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);

		printf("已写入 %s",str);
		fgets(str, sizeof(str)/sizeof(*str), fp);
		sleep(1);
		
	}
	return 0;
}
