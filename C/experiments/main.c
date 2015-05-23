//#define _POSIX_C_SOURCE
#include <unistd.h>
#include "stdio.h"
#include "assert.h"
#include "stdlib.h"
#include <time.h>


int main()
{
	struct timespec temp;
	clock_gettime(CLOCK_REALTIME, &temp);
	return 0;
}