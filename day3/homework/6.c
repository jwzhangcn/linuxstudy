#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[])
{
	char str[100] = "aabbbbcccdd";
	char c;
	int i,j,k;
	int len = strlen(str);

	for(i = 0;i <= len - 1;i ++)
	{
		for(j = i + 1;j <= len - 1;j ++)
		{
			if(str[i] == str[j])
			{

				for(k = j;k <= len - 1;k ++)
				{
					str[k]=str[k + 1];
				}
				len --;
				j --;
			}
		}
	}

	str[len] = '\0';

	puts(str);
	return 0;
}
