#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define N
#ifdef N
	#define PRINT(i,n) printf("%d %d",i,n);
#else
	#define PRINT(i,n)
#endif
	


int main(int argc, const char *argv[])
{
	PRINT(1,2);	
	return 0;
}
