#ifndef __IVVECTOR_INTERNAL
#define __IVVECTOR_INTERNAL

#include "assert.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#ifdef VECTOR_COMPILE_MAXSIZE
const uint32_t VEC_MAXSIZE = VECTOR_COMPILE_MAXSIZE;
#else
const uint32_t VEC_MAXSIZE = 4 * 1024 * 1024;
#endif

const uint32_t IV_POISON = 0xDEADBEEF;

/**
 * @brief Gets pointer of index'th element of vector
 * @param this  current vector
 * @param index
 */
void *__elem_ptr(const vector *this, uint32 index);

void __copy_elem(const vector *this, uint32 index, void *dest);
void __set_elem(vector *this, uint32 index, const void *src);

/**
 * @brief Debug memory allocator
 * @details Can cause errors during memory allocation
 *
 * @param nmemb number of members
 * @param size size of element
 * @return NULL if failed, otherwise desired pointer
 */
void *iv_calloc(size_t nmemb, size_t size);

/**
 * @brief Debug freer
 * @details Can cause errors during deallocation
 *
 * @param ptr pointer to free
 */
void iv_free(void *ptr);

/**
 * @brief Debug reallocator
 * @details Can cause errors
 *
 * @param ptr poiner to reallocate
 * @param size requested size
 * @return new pointer or NULL if terrible happened
 */
void *iv_realloc(void *ptr, size_t size, size_t oldsize);

/**
 * @brief	Validates iterator
 * @detailes	See __vector_check about modes. In DEBUG mode also checks
 * 		vector
 *
 * @param  	checked validating iterator
 * @return      1 if OK, 0 if not
 */
int __vector_iter_check(const vector_iter *checked);

/**
 * @brief Vector verification
 * @details Verifies vector consistency and has two modes.
 * In DEBUG mode if error happened debug information is printed to STDERR
 *
 * @param checked checking vector
 * @return 0 if failed, otherwise 1
 */
int __vector_check(const vector *checked);

#define FOR_EACH(cursor, vecptr, index)                                        \
  for (index = 0, cursor = vecptr->begin; index < vecptr->size;                \
       index += 1, cursor = (void *)((unsigned long)cursor +                   \
                                     (unsigned long)(vecptr->esize)))

#define ITER_CHECK(iter_ptr)                                                   \
  do {                                                                         \
    if (!__vector_iter_check(iter_ptr))                                        \
      return -1;                                                               \
    VECTOR_CHECK(iter_ptr->ptr);                                               \
  } while (0);

#define VECTOR_CHECK(vec_ptr)                                                  \
  do {                                                                         \
    if (!__vector_check(vec_ptr))                                              \
      return -1;                                                               \
  } while (0);

#define OFFSET_PTR(ptr, vector, number)                                        \
  ((void *)((long)(ptr) + (long)((vector)->esize) * (number)))
#define NEXT_PTR(ptr, vector) OFFSET_PTR(ptr, vector, 1)
#define PREV_PTR(ptr, vector) OFFSET_PTR(ptr, vector, -1)

#define IN_BOUNDS(index, vector) (((index) >= 0) && ((index) < (vector)->size))

#define BYTES_IN_ELEMS(vecptr, amount)                                         \
  (size_t)((amount) * (size_t)((vecptr)->esize))

struct vector_s {
  uint32_t alloc;
  uint32_t size;
  uint32_t maxsize;
  uint32_t esize;
  uint32_t emaxsize;
  char *begin;
  void (*destr)(void *obj);
};

struct vector_iter_s {
  vector *ptr;
  uint32 index;
};

#endif
