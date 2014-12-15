#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

int sort(int* shmptr, int size, int cons);


int comp(const void* ptr1, const void* ptr2)
{
	return *(int*)ptr1 - *(int*)ptr2;
}

const char tempname[] = "TEMP";

int main(int argc, char const *argv[])
{
	
	int size = atoi(argv[1]);
	printf("Size = %d\n", size);
	int* array = (int*) calloc(size, sizeof(int));
	int* copy  = (int*) calloc(size, sizeof(int));
	assert(array);
	assert(copy);

	int i = 0;

	for (i = 0; i < size; ++i)
		array[i] = rand() % 40; // возвращает от 0 до RAND_MAX

	printf("generated:\n");
	for (i = 0; i < size; ++i)
		printf("%d ", array[i]);
	fflush(stdout);

	int cond  = creat(tempname, 0660);
	printf("cond = %d\n", cond);
	key_t key   = ftok(tempname, 1);
	if (key == -1)
		perror("");
	printf("key = %d\n", key);
	int shmid = shmget(key, sizeof(int) * size, 0600 | IPC_CREAT);
	if (shmid == -1)
		perror("");
	int* shmptr= shmat(shmid, 0, 0);

	memcpy(shmptr, array, size * sizeof(int));
	memcpy(copy,   array, size * sizeof(int));

	qsort(copy, size, sizeof(int), comp);

	int cld1_id = fork();
	if (cld1_id == 0)
		sort(shmptr, size, 1);
	int cld2_id = fork();
	if (cld2_id == 0)
		sort(shmptr, size, 2);
	wait(0);
	wait(0);

	printf("qsorted:\n");
	for (int i = 0; i < size; ++i)
		printf("%d ", copy[i]);
	putchar('\n');
	
	int index_1 = 0;
	int index_2 = size / 2;
	int index = 0;

	printf("parallely qsorted:\n");
	for (int i = 0; i < size; ++i)
	{
		if (index_1 < size / 2 && index_2 < size){
			index = (shmptr[index_1] < shmptr[index_2])? index_1++: index_2++;
			printf("%d ", shmptr[index]);
			continue;
		}
		if (index_1 >= size / 2 && index_2 <  size)
		{
			printf("%d ", shmptr[index_2++]);
			continue;
		}
		if (index_1 <  size / 2 && index_2 >= size)
		{
			printf("%d ", shmptr[index_1++]);
			continue;
		}
		break;
	}


	free(copy);
	free(array);
	shmctl(shmid, IPC_RMID, NULL);
	putchar('\n');
	return 0;
}

int sort(int* shmptr, int size, int cons)
{
	int half = size / 2;
	if (cons == 1)
		qsort(shmptr, half, sizeof(int), comp);
	else
		qsort(&shmptr[half], size - half, sizeof(int), comp);
	exit(EXIT_SUCCESS);
}