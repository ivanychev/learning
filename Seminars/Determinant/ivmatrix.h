#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>
#include <float.h>
#include "stdio.h"
#include "stdlib.h"

struct matrix_s {
	uint32_t size;
	void* data;
};

#define ELEM_TYPE double

//!	This macros allowes to get access to element like matrix[i][j] = 5;
#define ELEM(matrix_ptr, string, column)	\
	*(((ELEM_TYPE*)((matrix_ptr)->data)) + (string)*((matrix_ptr)->size) + (column))

#define IS_ZERO(num)				\
	(fabs(num)<DBL_EPSILON)

typedef struct matrix_s matrix;