#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[])
{
	int a[10] = {11,22,33,44,55};
	int *p = a;
	printf("%d\n",(*p)++);
	printf("%d\n",*p++);
	printf("%d\n",*++p);
	printf("%d\n",++*p);
	return 0;
}
