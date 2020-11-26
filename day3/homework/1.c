#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[])
{
	int i,n;
	
	for(n = 300; n <= 400 ; n++)
	{
		for(i = 2; i <= n - 1 ; i++)
		{
			if(n % i == 0)
				break;	
			if(i == n-1)
				printf("%d\t",n);
		}
	}
	return 0;
}
