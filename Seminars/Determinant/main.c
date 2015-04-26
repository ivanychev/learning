#include "stdio.h"

int main(int argc, char const *argv[])
{
	long first = 0;
	long second = 0;

	scanf("%ld %ld", &first, second);
	long result = first + second;
	printf("%ld", result);
	return 0;
}