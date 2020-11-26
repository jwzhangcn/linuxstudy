#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comp(const void*, const void*);

int main(int argc, const char *argv[])
{
	char a[] = "fedcba";
	qsort(a, strlen(a), sizeof(char), comp);
	puts(a);
	return 0;
}

int comp(const void*a,const void*b)
{
	return *(char*)a-*(char*)b;
}
