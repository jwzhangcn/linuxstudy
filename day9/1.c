#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fun(int *a, int *b)
{
	*a ^= *b;
	*b ^= *a;
 	*a ^= *b;
}

int main(int argc, const char *argv[])
{
	int a = 2;
	int b = 4;
	fun(&a, &b);
	printf("a = %d b = %d", a, b);
	return 0;
}
