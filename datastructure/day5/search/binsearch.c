#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int binsearch(int *s, int len, int key)
{
	int front = 0;
	int rear = len -1;
	int mid;
	while(front <= rear)
	{
		mid = (front + rear)/2;
		if(key == s[mid])
			return mid;
		if(key > s[mid])
			front = mid + 1;
		else if(key < s[mid])
			rear = mid - 1;
	}
	return -1;
}

int main(int argc, const char *argv[])
{

	int a[] = {1,5,10,23,40,58,65,78,83,94,102};
	int ret = binsearch(a, 11, 78);
	printf("%d\n",ret);
	return 0;
}
