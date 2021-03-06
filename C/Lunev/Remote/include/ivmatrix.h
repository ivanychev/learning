#ifndef __IV_MATRIX
#define __IV_MATRIX

#define _XOPEN_SOURCE
#define _GNU_SOURCE

#include <sched.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include "errno.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "limits.h"
#include <sys/time.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
       #include <sys/ipc.h>
       #include <sys/sem.h>



struct matrix_s {
	uint32_t size;
	void* data;
};

typedef struct matrix_s matrix;

struct thread_meta {
	const matrix*  	ptr;
//	int      	semid;
	long 	 	threads_num;
	uint32_t 	minor_index;
	double*  	to_save;
	int 		semid;
};

typedef struct {
        int struct_size;
        int data_size;
} matrix_size;

#define PAGESIZE (4096)
#define MB (1024*1024)
#define MAX_FILENAME 100
#define TEMP_FILE ".temp"

union semun {
    int val;                         // value  for SETVAL
    struct semid_ds *buf;            // buffer for IPC_STAT, IPC_SET
    unsigned short int *array;       // array  for GETALL, SETALL
    struct seminfo *__buf;           // buffer for IPC_INFO
};


/**
 * @brief Reads matrix from argumented file
 * @details File structure: SIZE and SIZE*SIZE double numbers
 * 
 * @param filename 	reading file
 * @param this 		matrix to save results in
 * 
 * @return -1 if error occured, 0 if OK
 */
int    	get_matrix(const char* filename, matrix* this);

/**
 * @brief Calculates determinant of input matrix
 * @details using Gauss method
 * 
 * @param this current matrix
 * @return calculated determinant
 */
int get_matrix_determinant(const matrix* this, long nthreads, double* ret);

/**
 * @brief Prints current matrix to stdout
 * 
 * @param this current matrix
 */
void   	print_matrix(const matrix* this);

/**
 * @brief 	serches and swaps i-th string with found one
 * @details 	if [i, i] element is zero during Gauss method we need to find
 * 		non-zero element below it and swap strings to continue annulating 
 * 		column below [i, i] 
 * 
 * @param this 	current matrix
 * @param i 	current diagonal element index
 */
void  	search_below_nzero_swap(matrix* this, uint32_t i);

/**
 * @brief Annihilates numbers below [i, i] to zero (current is 1)
 * @details 	1  2  3			1  2  3
 * 		0 [3] 7 	-> 	0 [3] 7
 * 		0  4  5 		0  0 (5 - 4*7/3)
 * 
 * @param this current matrix
 * @param i position (1 in description)
 */

void  	annihilate_below 	    (matrix* this, uint32_t i);

/**
 * @brief Swaps string of the matrix
 * 
 * @param this 	 current matrix
 * @param first  1-st string
 * @param second 2-nd string
 */
void  	swap_strings 	    (matrix* this, uint32_t first, uint32_t second);

/**
 * @brief Adds string, multiplied by factor, to current 
 * 
 * @param this 	 current matrix
 * @param added  added string
 * @param to 	 changing string
 * @param factor 
 */
void  	add_string 	    (matrix* this, uint32_t added, uint32_t to, double factor);


int gauss(matrix* this, double* result);

/**
 * @brief Safely deletes matrix
 * 
 * @param this current matrix
 */
void 	matrix_kill 	    (matrix* this);

int get_long(long* save, const char* str);

matrix* get_minor(const matrix* this, uint32_t string, uint32_t column);

void* thread_routine(void* info_ptr);

void* thread_routine_debug(void* info_ptr);





#define ELEM_TYPE double

//!	This macros allowes to get access to element like matrix[i][j] = 5;
#define ELEM(matrix_ptr, string, column)	\
	*(((ELEM_TYPE*)((matrix_ptr)->data)) + (string)*((matrix_ptr)->size) + (column))

#define IS_ZERO(num)				\
	(fabs(num)<DBL_EPSILON)

#endif
