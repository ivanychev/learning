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




vector* __vector_init(uint32 size, void (*destr)(void* obj));
#define   vector_init(name, type, destr)	\
	  vector* name = __vector_init(sizeof(type), destr);

void 		__vector_iter_dump	(const vector_iter* iter);
void 		__vector_dump 		(const vector* this);


int vector_delete(vector*);
int vector_erase (vector*);
int vector_remove(vector*, uint32);
int vector_insert(vector*, const void*, uint32 index_will_be);
int vector_sort  (vector*, int (*comp)(const void*, const void*));

int vector_get(const vector*, uint32, void* where_to_get);
int vector_set(      vector*, uint32, void* what_to_send);

int    vector_empty   (const vector*);
uint32 vector_size    (const vector*);
uint32 vector_esize   (const vector*);
uint32 vector_maxsize (const vector*);
uint32 vector_alloc   (const vector*);
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

int vector_iter_next	(vector_iter*, 	void* dest);
int vector_iter_prev	(vector_iter*, 	void* dest);
int vector_iter_getelem (const vector_iter*, void* dest);
int vector_iter_setelem (vector_iter*, const void* src);
int vector_iter_begin   (vector_iter*);
int vector_iter_end     (vector_iter*);
vector_iter* vector_iter_get(vector*);
int vector_iter_del(vector_iter*);
int vector_iter_isbegin  (const vector_iter*);
int vector_iter_isend (const vector_iter*);
//uint32 vector_iter_get_index(const* vector_iter*);

void* vector_iter_do(vector_iter* iter, void* args, void* (*proceed)(void* obj,void* argv));


#endif
