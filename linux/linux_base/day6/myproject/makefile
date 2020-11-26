CFLAGS = -O -Wall -I ./include
LDFLAGS = -L ./lib/ -pthread

APP = app
SRCS = $(wildcard ./src/*.c)
OBJS = $(patsubst %c, %o, $(SRCS))

CC = gcc
all:$(APP)

$(APP):$(OBJS)
	$(CC) $^ -o $(APP)

.PHONY:clean
clean:
	rm -f $(APP) $(OBJS)

