#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *getUsrName(char *str)
{
	char *p = str;
	static char uName[10] = "";
	while(*p != '#')
	{
		strcat(uName,p);
		p++;
	}
	return uName;
}
int main(int argc, const char *argv[])
{
	char str[] = "Ujack#ps123";
	//puts(str);
	char *usrName = getUsrName(str);
	puts(usrName);
	return 0;
}
