#ifndef IV_VECTOR
#define IV_VECTOR


#include "stdint.h"

struct vector_s; 
typedef struct vector_s vector;

#define vector_init(name, type)	\
	__vector_init(name, sizeof(type));
// pointer too

int vector_delete(vector*);
int vector_erase (vector*);
int vector_remove(vector*, uint32);
int vector_insert(vector*, uint32);
int vector_sort  (vector*, int (*comp)(void*, void*));

int vector_get(vector*, uint32, void* where_to_get);
int vector_set(vector*, uint32, void* what_to_send);

int    vector_empty 	(vector*);
uint32 vector_size    (vector*);
uint32 vector_maxsize (vector*);
uint32 vector_capacity(vector*);
uint32 vector_alloc   (vector*);


int vector_fit	(vector*);
int vector_pushback (vector* this, void* elem);
int vector_pushfront(vector* this, void* elem);
int vector_popfront (vector* this, void* dest);
int vector_popback  (vector* this, void* dest);





// Если с итераторами

struct vector_iter_s;
typedef struct vector_iter_s vector_iter;


/**
 * if dest is NULL, nothing is copied
 */

// errptr

int vector_iter_next	(vector_iter*, 	void* dest);
int vector_iter_prev	(vector_iter*, 	void* dest);
int vector_iter_getelem (const vector_iter*, void* dest);
int vector_iter_setelem (vector_iter*, const void* dest);
int vector_iter_begin   (vector_iter*, 	void* dest);
int vector_iter_end     (vector_iter*, 	void* dest);
vector_iter* vector_iter_get_iter(const vector*);
int vector_iter_del_iter(vector_iter*);
int vector_iter_islast  (const vector_iter*);
int vector_iter_isfirst (const vector_iter*);

int vector_iter_do(Vector_iter* iter, void* args, void (do)(void* argv));


#endif