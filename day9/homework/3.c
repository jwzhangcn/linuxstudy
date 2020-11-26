#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void del(char *p,char *p1)
{
	char *p2,*p3;
	p2 = p3 = p1;
	int flag;
	while(*p)
	{
		flag = 1;
		while(*p2)
		{
			if(*p == *p2)
			{
				flag = 0;
			}
			p2++;				
		}
		if(flag)
			*p1++ = *p;	
		p2 = p3;
		p++;
	}
}

int main(int argc, const char *argv[])
{
	char old[] = "aaaabbaddffef";
	char new[20] = "";
	del(old,new);
	puts(old);
	puts(new);
	return 0;
}
