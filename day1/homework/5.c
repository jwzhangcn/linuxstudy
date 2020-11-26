#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define N 6

int main(int argc, const char *argv[])
{
	char str[N] = {2,2,3,4,5,6};
	printf("%d\n",charTrans(str));
	return 0;
}

int charTrans(char str [])
{
	int l,n = 0;
	l = strlen(str);
	while(*str != '\0')
	{
		n +=  (int)str[N-l] * pow(10,l-1);
		str++;
		l--;
	}
	return n;
}
