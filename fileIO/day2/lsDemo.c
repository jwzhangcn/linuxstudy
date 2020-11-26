#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/*
 *
 *
 *
 *
 *
 */

int lsDemo(char *path)
{
	DIR* dp = opendir(path);
	if(!dp)
	{
		perror("opendir");
		return -1;
	}

	struct dirent *d;
	static char str[64] = "";
	while(d = readdir(dp))
	{
		if(getFileMod(d->d_name, str))
		{
			printf("getFileMod");	
			return -1;
		}

		sprintf(str, "%s %s\n", str, d->d_name);
		puts(str);
	}
	return 0;
}

int getFileMod(char *fileName, char *str)
{
	struct stat s;
	int ret = stat(fileName, &s);
	if(ret == -1)
	{
		perror("stat");
		return -1;
	}

	int i = 8;
	for(i = 8; i >= 0; i -= 3)
	{
		sprintf(str, "%s%c%c%c", str, s.st_mode & (1 << i)? 'r': '-',\
				s.st_mode & (1 << (i - 1)) ? 'w' : 'x',\
				s.st_mode & (1 << (i -2)) ?'x' : '-');
	}
	
	return 0;
}

int main(int argc, const char *argv[])
{
	lsDemo("./");
	return 0;
}
