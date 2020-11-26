#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, const char *argv[])
{
	int fd = open("./open.c",O_RDONLY);
	if(-1 == fd)
	{
		perror("fdopen");
		return -1;
	
	}
	char buf[64] = {0};
	int ret = sizeof(buf);

	while(ret == sizeof(buf))
	{
		ret = read(fd, buf, sizeof(buf));

		write(STDOUT_FILENO, buf, ret);
	}

	ret = close(fd);
	if(-1 == ret)
	{
		perror("fdclose");
		return -1;
	}

	return 0;
}
