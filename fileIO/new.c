#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int fileCpy(char *src, char *dest)
{
	FILE *src_fp = fopen(src, "r");
	if(NULL == src_fp)
		return -1;
	FILE *dest_fp = fopen(dest, "w+"); 
	char c;
	while(EOF != (c = fgetc(src_fp)))
		fputc(c, dest_fp);
	
	fclose(src_fp);
	fclose(dest_fp);
	return 0;
}

int main(int argc, const char *argv[])
{
	fileCpy("date.c", "new.c");
	return 0;
}
