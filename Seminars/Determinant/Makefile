CC 		=  gcc #clang-3.5
WARNINGS 	= -Wall -Werror
STANDARD 	= -std=c99
GCOV 	 	= -fprofile-arcs -ftest-coverage -pg
OPTIMIZE 	= -O0
CFLAGS 		= -g $(STANDARD) $(WARNINGS) $(OPTIMIZE) -MD -pthread
TARGET 		= determ.out
VALGRIND_KEYS 	= 
.PHONY: all clean testing valgrind


all: determinant

determinant: ivmatrix.c iv_standard.o
	$(CC) $(CFLAGS) iv_standard.o $< -o $(TARGET)

iv_standard.o: iv_standard.c
	$(CC) $(CFLAGS) $< -c -o $@

clean:
	rm -rf *.o *.gcna *gcno *.gcda $(TARGET) 
testing: $(TARGET)
	./$(TARGET)

# можно ли вызвать правило с другой переменной (хочу использовать clang, gcc при valgrind)
valgrind: $(TARGET)
	valgrind $(VALGRIND_KEYS) ./$(TARGET)

-include $(wildcard *.d)
