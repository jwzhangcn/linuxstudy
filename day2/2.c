#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[])
{
	int s = 0,n = 1;
	while(n <= 100)
	{
		s += n;
		n++;
	}
	printf("s = %d\n",s);
	return 0;
}
