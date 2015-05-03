CC = clang-3.5
FLAGS = -Wall -Werror -std=c99 -MD

.PHONY: all clean

all: client-server.out

client-server.out: client-server.c
	$(CC) client-server.c -o client-server.out $(FLAGS)

clean:
	rm *.o *.out

-include $(wildcard *.d)