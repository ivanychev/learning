CC = gcc
WARNINGS 	= -Wall -Werror
STANDARD 	= -std=c11
GCOV 	 	= -fprofile-arcs -ftest-coverage
CFLAGS 		= -g $(STANDARD) $(GCOV) $(WARNINGS) -MD 
TARGET 		= try_vector 
VALGRIND_KEYS 	= 
.PHONY: all clean testing valgrind

# Multiple commands ??

all: vector_test

vector_test: ivvector.o try.c
	$(CC) $(CFLAGS) ivvector.o try.c -o $(TARGET)

ivvector.o: ivvector.c
	$(CC) $(CFLAGS) $< -c -o $@ 

clean:
	rm -rf *.o $(TARGET)
testing: $(TARGET)
	./$(TARGET)

valgrind: $(TARGET)
	valgrind $(VALGRIND_KEYS) ./$(TARGET)

-include $(wildcard *.d)