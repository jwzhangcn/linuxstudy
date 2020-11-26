#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[])
{
	typedef union human{
		int age;
		char name[10];
		char gender;
	}man;

	int a = 12;
	int b = a*10++;

	printf("%d",b);
	
	return 0;
}
