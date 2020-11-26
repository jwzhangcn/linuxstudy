#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float add(float a, float b)
{
	return a+b;
}

float minus(float a, float b)
{
	return a-b;
}

float mult(float a, float b)
{
	return a*b;
}

float divd(float a, float b)
{
	return a/b;
}

int main(int argc, const char *argv[])
{
	float a = 10;
	float b = 5;
	
	float (*p)(float, float) = {mult};
	printf("%.2f\n", p(a, b));


	return 0;
}
