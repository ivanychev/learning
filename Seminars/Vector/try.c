#include "ivvector.h"
#include "stdio.h"

int main(int argc, char const *argv[])
{
	vector_init(first, int, NULL);
	__vector_dump(first);
	int a = 5;
	int b = 0;
	int cond = vector_insert(first, &a, 0);
	printf("Insert code %d\n", cond);
	__vector_dump(first);

	vector_get(first, 0, &b);
	printf("%d\n", b);
	vector_delete(first);
	return 0;
}