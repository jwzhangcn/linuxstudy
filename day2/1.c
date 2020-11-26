#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[])
{
	int score = 0;
	scanf("%d",&score);

	switch(score/10)
	{
		case 10:
	
		case 9:
			printf("A\n");
			break;
		case 8:
			printf("b\n");
			break;
		case 7:
			printf("c\n");
			break;
		case 6:
			printf("d\n");
			break;
		default:
			printf("f\n");
	}
	return 0;
}
