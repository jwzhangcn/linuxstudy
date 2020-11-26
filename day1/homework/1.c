#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, const char *argv[])
{
	float a,b,c,s,area;
	scanf("%f%f%f",&a,&b,&c);

	if(a+b<c && a+c<b && b+c<a)
	{
		printf("error\n");
	} 
	else
	{
		s = (a + b + c) / 2;
		area = sqrt(s*(s - a)*(s - b)*(s -c));
		printf("area = %.2f\n",area);
	}
	return 0;
}
