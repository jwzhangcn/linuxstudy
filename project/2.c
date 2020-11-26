 #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>
#include <stdio.h>
int main()
{
        int fd = open("/dev/ttyUSB0",O_RDWR | O_NOCTTY | O_NDELAY);
        printf("%d",fd);
}
