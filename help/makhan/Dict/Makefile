CC 	= gcc
.PHONY: all clean


all: test.out

test.out: test.c dict.o
	$(CC) dict.o test.c -g -fprofile-arcs -ftest-coverage -o test.out

dict.o: dict.c
	$(CC) dict.c -c -g -fprofile-arcs -ftest-coverage -o dict.o

clean:
	rm *.out *.o *.gcno *.gcov