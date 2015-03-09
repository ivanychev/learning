#include "ivvector.h"
#include "ivvector_internal.h"

#include "ivvector_utils.c"
#include "ivvector_iter.c"


const uint32 MAXESIZE_RATIO = 100;
const uint32 MINALLOC_ELEMS = 5; 


//==========================================================================================
/**
 * Deletes all objects and releases memory
 * @param this current vector
 */

static void __vector_eliminate_all_and_free(vector* this)
{
	void*  cursor = NULL;
	uint32 index  = 0;
	FOR_EACH(cursor, this, index);
		if (this->destr != NULL)
			this->destr(cursor);
	if (this->begin != NULL)
		iv_free(this->begin);
}

/**
 * Optimizes allocated memory. If allocated more than size * 2, the
 * ammount of memory would be reduced
 * @param  this analysed vector
 * @return 0 if OK, -1 if failed to realloc memory
 */
static int __optimize_alloc(vector* this)
{
	uint32 alloc = this->alloc;
	uint32 size  = this->size;
	if (!
		((size  <= alloc / 2) &&
		(alloc / 2>= MINALLOC_ELEMS)) 
	    )
		return 0;
	void* new_begin = iv_realloc(this->begin, alloc / 2);
	this->begin = new_begin;
	this->alloc = alloc / 2;

	if (new_begin == NULL)
		return -1;
	return 0;
}

/**
 * Allocates more memory to vector
 * @param  	this current vector
 * @return      1 if success, 0 if maximum size reached, -1 if realloc failed
 */
static int __alloc_more(vector* this)
{
	assert(this);
	uint32      alloc   = this->alloc;
	uint32      maxsize = this->maxsize;
	if (alloc == maxsize)
		return 0;
	uint64 new_alloc = (alloc != 0)? alloc * 2: 
					 MINALLOC_ELEMS;
	if (new_alloc > maxsize)
		new_alloc = maxsize;
	void* new_begin = iv_realloc(this->begin, (size_t)new_alloc*this->esize);
	if (new_begin == NULL)
		return -1;

	this->begin = new_begin;
	this->alloc = new_alloc;
	return 1;
}


/**
 * Allocates memory and creates vector object
 *
 * @size 	Size of contained element
 * @destr 	Function pointer to object destructor, possible to be NULL
 * @maxsize 	Maximal size of vector
 */

vector* __vector_init(uint32 size, void (*destr)(void* obj))
{
	vector* new = iv_calloc(1, sizeof(vector));
	if (new == NULL)
		return NULL;

	       vector new_vector = {	
 		.alloc = 0, 		
 		.size = 0, 		
 		.maxsize = VEC_MAXSIZE, 	
 		.esize = size, 	
 		.emaxsize = VEC_MAXSIZE/MAXESIZE_RATIO, 	
 		.begin = NULL,
 		.destr = destr
 	};
 	*new = new_vector;
 	return new;
}

/**
 * Deletes current vector
 * @param  this Deleting vector
 * @return      -1 if pointer is NULL, 0 if success
 */
int vector_delete(vector* this)
{
	if (this == NULL)
		return -1;
	__vector_eliminate_all_and_free(this);

	this->alloc 	= IV_POISON;
	this->size  	= IV_POISON;
	this->maxsize 	= IV_POISON;
	this->esize   	= IV_POISON;
	this->emaxsize 	= IV_POISON;
	this->begin	= NULL;
	this->destr	= NULL;

	iv_free(this);
	return 0;
}

/**
 * Deletes all objects and releases memory
 * @param  this current vector
 * @return      -1 if vector is invalid, 0 if success
 */
int vector_erase(vector* this)
{
	VECTOR_CHECK(this);
	__vector_eliminate_all_and_free(this);

	this->alloc 	= 0;
	this->size  	= 0;
	this->begin	= NULL;
	return 0;
}

/**
 * Removes index'th element of vector
 * @param  this  current vector
 * @param  index index of removing object
 * @return       -1 if not in bounds, 0 if OK
 */
int vector_remove(vector* this, uint32 index)
{
	if (!(IN_BOUNDS(index, this)))
		return -1;
	void* ptr = __elem_ptr(this, index);
	this->destr(ptr);

	memmove(ptr, 
		NEXT_PTR(ptr, this), 
		(size_t)(this->size - index - 1)*(this->esize));
	this->size -= 1;
	__optimize_alloc(this);
	return 0;
}

/**
 * Inserts current element to be index'th element in vector
 * @param  this  current vector
 * @param  elem  element to insert
 * @param  index future index
 * @return       -1  if not in bounds or reallocation failed
 *                0  if maximum size reached
 *                1  if OK
 */
int vector_insert(vector* this, void* elem, uint32 index)
{
	if (!(IN_BOUNDS(index, this) || index == this->size))
		return -1;
	int cond = 0;

	if (this->size == this->alloc)
	{
		cond = __alloc_more(this);
		if (cond != 1)
			return cond;
	}
	void* current = __elem_ptr(this, index);
	memmove(NEXT_PTR(current, this), current, this->size - index);
	__set_elem(this, index, elem);

	this->size += 1;
	return 1;
}

/**
 * Sorts current vector
 * @param this	current vector
 * @param comp	comparison function
 * @return	-1 if vector is invalid, 0 if OK
 */

int vector_sort(vector* this, int (*comp)(const void*, const void*))
{
	VECTOR_CHECK(this);
	qsort(this->begin, this->esize, this->size, comp);
	return 0;
}

int vector_get(const vector* this, uint32 index, void* where_to_get)
{
	assert(this);
	assert(where_to_get);
	if (!IN_BOUNDS(index, this))
		return -1;
	__copy_elem(this, index, where_to_get);
	return 0;

}

int vector_set(vector* this, uint32 index, void* what_to_send)
{
	assert(this);
	assert(what_to_send);
	if (!IN_BOUNDS(index, this))
		return -1;
	__set_elem(this, index, what_to_send);
	return 0;
}

int vector_empty(const vector* this)
{
	return this->size == 0;
}

uint32 vector_size(const vector* this)
{
	return this->size;
}

uint32 vector_esize(const vector* this)
{
	return this->esize;
}

uint32 vector_maxsize(const vector* this)
{
	return this->maxsize;
}

uint32 vector_alloc(const vector* this)
{
	return this->alloc;
}

/**
 * Changes allocated memory capacity to its size
 * @param  this current vector
 * @return      -1 if vector is invalid or failed to reallocate memory
 *               0 if OK
 */
int vector_fit(vector* this)
{
	VECTOR_CHECK(this);
	void* new_begin = iv_realloc(this->begin, (size_t)this->size * this->esize);
	if (new_begin == NULL)
		return -1;
	this->begin = new_begin;
	this->alloc = this->size;
	return 1;
}
