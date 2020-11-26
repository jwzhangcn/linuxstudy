#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{
	int fd1 = open("./1.txt",O_RDONLY);
	int fd2 = open("./2.txt",O_RDWR | O_CREAT , 0666);

	char buf[100] = "";

	read(fd1, buf, 100);
	puts(buf);
	write(fd2, buf, 100);

	return 0;
}
