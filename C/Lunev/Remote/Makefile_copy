CC     = gcc #clang-3.5
FLAGS  = -Wall -g -Werror -MD -pthread
TARGET = remoted 
.PHONY: all clean

all: $(TARGET)

remoted: main.c client.o server.o iv_standard.o common.o
	$(CC) $(FLAGS) client.o server.o common.o iv_standard.o ../Determinant/ivmatrix.o main.c -o $@

client.o: client.c
	$(CC) $(FLAGS) -c $< -o $@

server.o: server.c
	$(CC) $(FLAGS) -c $< -o $@

common.o: common.c 
	$(CC) $(FLAGS) -c $< -o $@

iv_standard.o: iv_standard.c
	$(CC) $(FLAGS) -c $< -o $@ 

clean:
	rm -rf *.o $(TARGET) *.d
	clear && clear

-include $(wildcard *.d)
