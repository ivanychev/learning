#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <inttypes.h>
#include "stdio.h"
#include "stdlib.h"

struct matrix_s {
	uint32_t size,
	void* data
};

//!	This macros allowes to get access to element like matrix[i][j] = 5;
#define ELEM(matrix_ptr, string, column)	\
	*(((double*)((matrix_ptr)->data)) + (string)*((matrix_ptr)->size) + (column))

typedef matrix_s matrix;