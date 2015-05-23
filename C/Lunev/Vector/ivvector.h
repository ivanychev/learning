#ifndef IV_VECTOR
#define IV_VECTOR

#include "stdint.h"
#include "assert.h"
#include "inttypes.h"


typedef uint32_t uint32;
typedef uint64_t uint64;
typedef  int32_t  int32;
typedef  int64_t  int64;


struct vector_s; 
typedef struct vector_s vector;

struct vector_iter_s;
typedef struct vector_iter_s vector_iter;



/**
 * Allocates memory and creates vector object
 *
 * @size 	Size of contained element
 * @destr 	Function pointer to object destructor, possible to be NULL
 * @maxsize 	Maximal size of vector
 */
vector* __vector_init(uint32 size, void (*destr)(void* obj));

#define   vector_init(name, type, destr)	\
	  vector* name = __vector_init(sizeof(type), destr);

void 		__vector_iter_dump	(const vector_iter* iter);


void 		__vector_dump 		(const vector* this);

/**
 * Deletes current vector
 * @param  this Deleting vector
 * @return      -1 if pointer is NULL, 0 if success
 */
int vector_delete(vector*);
/**
 * Deletes all objects and releases memory
 * @param  this current vector
 * @return      -1 if vector is invalid, 0 if success
 */
int vector_erase (vector*);
/**
 * Removes index'th element of vector
 * @param  this  current vector
 * @param  index index of removing object
 * @return       -1 if not in bounds, 0 if OK
 */
int vector_remove(vector*, uint32);
/**
 * Inserts current element to be index'th element in vector
 * @param  this  current vector
 * @param  elem  element to insert
 * @param  index future index
 * @return       -1  if not in bounds or reallocation failed
 *                0  if maximum size reached
 *                1  if OK
 */
int vector_insert(vector*, const void*, uint32 index_will_be);

/**
 * Sorts current vector
 * @param this	current vector
 * @param comp	comparison function
 * @return	-1 if vector is invalid, 0 if OK
 */
int vector_sort  (vector*, int (*comp)(const void*, const void*));
/**
 * Copies vector element to the pointer
 * @param  this         current vector
 * @param  index        index of copying element
 * @param  where_to_get pointer to save
 * @return              -1 if not in bounds, 0 if OK
 */
int vector_get(const vector*, uint32, void* where_to_get);

/**
 * Set index'th value of vector to the argumented object
 * @param  this         current vector
 * @param  index        changing member
 * @param  what_to_send new object
 * @return              -1 if out of bounds ot argumented pointer is NULL
 */
int vector_set(      vector*, uint32, void* what_to_send);

/**
 * @brief 	Checks if vector is empty
 * @details 
 * 
 * @param  current vector
 * @return 0 if not empty, otherwise not 0
 */
int    vector_empty   (const vector*);
/**
 * @brief Returns size of current vector
 * @details 
 * 
 * @param  current vector
 * @return size
 */
uint32 vector_size    (const vector*);
uint32 vector_esize   (const vector*);
uint32 vector_maxsize (const vector*);
uint32 vector_alloc   (const vector*);

/**
 * @brief Fits vector to its size
 * @details If allocated memory is bigger than needed, it will be cut to current size
 * of vector
 * 
 * @param  current vector
 * @return 1 if vector is invalid or failed to reallocate memory
 *         0 if OK
 */
int vector_fit	(vector*);


#ifndef DEBUG
#define CHECK_SIZE(vec_ptr, obj_ptr)
#else
#define CHECK_SIZE(vec_ptr, obj_ptr) 					\
	assert("Pointed object size don't match vector element size",	\
	vector_esize(vec_ptr) == sizeof(*(obj_ptr)));
#endif

int __vector_pushback (vector* this, const void* obj);
int __vector_pushfront(vector* this, const void* obj);
int __vector_popback  (vector* this, void* dest);
int __vector_popfront (vector* this, void* dest);


#define vector_pushback(vec_ptr, obj_ptr)	\
	CHECK_SIZE((vec_ptr), (obj_ptr))	\
	__vector_pushback((vec_ptr), (void*)obj_ptr)
#define vector_pushfront(vec_ptr, obj_ptr)	\
	CHECK_SIZE(vec_ptr, obj_ptr)		\
	__vector_pushfront((vec_ptr), (void*)obj_ptr)
#define vector_popback(vec_ptr, obj_ptr)	\
	CHECK_SIZE(vec_ptr, obj_ptr)		\
	__vector_popback((vec_ptr), (void*)obj_ptr)
#define vector_popfront(vec_ptr, obj_ptr)	\
	CHECK_SIZE(vec_ptr, obj_ptr)		\
	__vector_popfront((vec_ptr), (void*)obj_ptr)

/**
 * if dest is NULL, nothing is copied
 */

/**
 * Moves iterator to next element
 * @param  this current iterator
 * @param  dest if not NULL copies current object before moving iterator
 * @return      1 if moved, 0 if not, -1 if iterator is invalid
 */
int vector_iter_next	(vector_iter*, 	void* dest);

/**
 * Moves iterator to previous element
 * @param  this current iterator
 * @param  dest if not NULL copies current object before moving iterator
 * @return 1 if moved, 0 if not, -1 if iterator is invalid
 */
int vector_iter_prev	(vector_iter*, 	void* dest);

/**
 * Copies object, pointed by iterator
 * @param  this current iterator
 * @param  dest destination
 * @return      0 if success, -1 if failure
 */
int vector_iter_getelem (const vector_iter*, void* dest);

/**
 * Replaces object, pointed by iterator, with argumented
 * @param  this current iterator
 * @param  src  
 * @return      0 if success, -1 if failure
 */
int vector_iter_setelem (vector_iter*, const void* src);

/**
 * Sets iterator to begin of vector
 * @param  this current iterator
 * @return      0 if success, -1 if "this" is NULL or vector is invalid
 */
int vector_iter_begin   (vector_iter*);

/**
 * Sets iterator to end of vector
 * @param  this current iterator
 * @return      0 if success, -1 if "this" is NULL or vector is invalid
 */
int vector_iter_end     (vector_iter*);
vector_iter* vector_iter_get(vector*);

/**
 * Deletes iterator
 * @param  this pointer to iterator
 * @return      0 if success, -1 if "this" is NULL
 */
int vector_iter_del(vector_iter*);

/**
 * Is the pointed object first
 * @param  this current iterator
 * @return      1 if true, 0 if false, -1 if iterator is invalid
 */
int vector_iter_isbegin  (const vector_iter*);


/**
 * Is the pointed object last
 * @param  this current iterator
 * @return      1 if true, 0 if false, -1 if iterator is invalid
 */
int vector_iter_isend (const vector_iter*);
//uint32 vector_iter_get_index(const* vector_iter*);

void* vector_iter_do(vector_iter* iter, void* args, void* (*proceed)(void* obj,void* argv));


#endif
