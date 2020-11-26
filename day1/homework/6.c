#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, const char *argv[])
{
	int n,i = 0,j;
	scanf("%d",&n);
	while(n != 0)
	{
		n = n / 10;
		i++;
	}
	char str[i];
	for(j = 0;j <= i;j++)
	{
		str[j] = n / pow(10,i);
	}
	for(j = 0;j < i;j++)
		printf("%i\t",str[j]);
	return 0;

}
