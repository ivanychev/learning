#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>

void* epic_func(void* ptr)
{
	exit(EXIT_SUCCESS);
}

int main(int argc, char const *argv[])
{
	pthread_t thread;

	int err = pthread_create (&thread, NULL, epic_func, NULL);

	while (1)
		printf("Working...\n");
	return 0;
}