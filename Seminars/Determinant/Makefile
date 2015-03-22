CC 		=  gcc #clang-3.5
WARNINGS 	= -Wall -Werror
STANDARD 	= -std=c11
GCOV 	 	= -fprofile-arcs -ftest-coverage -pg
CFLAGS 		= -g $(STANDARD) $(GCOV) $(WARNINGS) -MD -pthread
TARGET 		= determ.out
VALGRIND_KEYS 	= 
.PHONY: all clean testing valgrind


all: determinant

determinant: ivmatrix.c
	$(CC) $(CFLAGS) $< -o $(TARGET)

clean:
	rm -rf *.o *.gcna *gcno *.gcda $(TARGET) 
testing: $(TARGET)
	./$(TARGET)

# можно ли вызвать правило с другой переменной (хочу использовать clang, gcc при valgrind)
valgrind: $(TARGET)
	valgrind $(VALGRIND_KEYS) ./$(TARGET)

-include $(wildcard *.d)