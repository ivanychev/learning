#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>

int main(int argc, char const *argv[])
{
	FILE* f = fopen("test3.txt", "w");
	for (int i = 0; i < 100000; ++i)
		fprintf(f, "%d\n", i);
	fclose(f);
}