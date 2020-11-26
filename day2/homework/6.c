#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *delstr(char *p,char str)
{	
	static char a[100] = "";
	int start, count, i, j, k= 0;           

	for (i = 0; p[i] != '\0'; i++)
	{
		start = i;      
		j = 0;          
						   

		while ((p[i] != '\0') && (str[j] != '\0') && (p[i] == str[j]))
		{
			i++;
			j++;
		}

		if (str[j] != '\0')                
		{
			a[k++] = p[start];   i = start;   
		}
		else                       
		{
			count++;
			i--;         
		}
	}
	return a;
}

int main(int argc, const char *argv[])
{

	char a[]="abbcdef";
	char str;
	scanf("%c",&str);
	delstr(a,str);
	puts(a);
	return 0;
}
