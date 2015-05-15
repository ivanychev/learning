CC 	= gcc
.PHONY: all clean


 # Checking code coverage
 # 1. Compiling with "make clean" AND "make all"
 # 2. Executing program
 # 3. launch gcov like:
 # 	#> gcov <filename>
 #    for example
 #    	#> gcov test.c

all: test.out

test.out: test.c dict.o
	$(CC) dict.o test.c -g -fprofile-arcs -ftest-coverage -o test.out

dict.o: dict.c
	$(CC) dict.c -c -g -fprofile-arcs -ftest-coverage -o dict.o

clean:
	rm *.out *.o *.gcno *.gcov
