#include "stdio.h"
#include <asm/pgtable.h>
int main(int argc, char const *argv[])
{
	printf("%ld", VMALLOC_START);
	return 0;
}