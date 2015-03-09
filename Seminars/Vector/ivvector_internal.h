#ifndef __IVVECTOR_INTERNAL
#define __IVVECTOR_INTERNAL

#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "assert.h"

#ifdef VECTOR_COMPILE_MAXSIZE
const uint32_t VEC_MAXSIZE = VECTOR_COMPILE_MAXSIZE;
#else
const uint32_t VEC_MAXSIZE = 4 * 1024 * 1024;
#endif

const uint32_t IV_POISON = 0xDEADBEEF;

int 		__vector_check 		(const vector* checked);
int 		__vector_iter_check	(const vector_iter* checked);


void* 	__elem_ptr 		(const vector* this, uint32 index);
void 	__copy_elem 		(const vector* this, uint32 index, void* dest);
void 	__set_elem 		(vector* this, uint32 index, const void* src);

void* iv_calloc(size_t nmemb, size_t size);
void  iv_free(void* ptr);
void* iv_realloc(void* ptr, size_t size);

int __vector_iter_check(const vector_iter* checked);
int __vector_check(const vector* checked);

#define FOR_EACH(cursor, vecptr, index)							 \
for (index = 0, cursor = vecptr->begin;							 \
	index< vecptr->size;								 \
	index += 1, cursor = (void*)((unsigned long)cursor + (unsigned long)(vecptr -> esize)))


#define ITER_CHECK(iter_ptr)			\
do{						\
	if (!__vector_iter_check(iter_ptr))	\
		return -1;			\
} while (0);	

#define VECTOR_CHECK(vec_ptr)			\
do{						\
	if (!__vector_check(vec_ptr))		\
		return -1;			\
} while(0);		

#define OFFSET_PTR(ptr, vector, number)		\
((void*)((long)(ptr) + (long)((vector)->esize) * (number)))
#define NEXT_PTR(ptr, vector)	OFFSET_PTR(ptr, vector,  1)
#define PREV_PTR(ptr, vector)	OFFSET_PTR(ptr, vector, -1)

#define IN_BOUNDS(index, vector) (((index) >= 0) && ((index) < (vector)->size))

#define BYTES_IN_ELEMS(vecptr, amount) (size_t)((amount)*(size_t)((vecptr)->esize))

/**
 *
 * 
 */


struct vector_s
{
	uint32_t alloc;
	uint32_t size;
	uint32_t maxsize;
	uint32_t esize;
	uint32_t emaxsize;
	char* begin;
	void (*destr)(void* obj);
};

struct vector_iter_s
{
	vector* ptr;
	uint32 index;
};


#endif
