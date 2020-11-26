all:
	arm-none-linux-gnueabi-gcc ./src/*.c -L./lib -lcamera -ljpeg  -lpthread -I./include -I./curlarm/include/curl -I./iconvarm/include/ -L./iconvarm/lib  -liconv -static
	cp a.out /tftpboot
