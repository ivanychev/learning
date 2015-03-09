#include "ivvector.h"
#include "ivvector_internal.h"

// Iterators

/*
	PTR_ERR MODIFY AHEAD
 */
vector_iter* vector_iter_get(vector* this)
{
	if (this == NULL)
		return NULL;
	vector_iter* new = iv_calloc(1, sizeof(vector_iter));
	if (new == NULL)
		return NULL;
	new->ptr = this;

	return new;
}

/**
 * Deletes iterator
 * @param  this pointer to iterator
 * @return      0 if success, -1 if "this" is NULL
 */
int vector_iter_del(vector_iter* this)
{
	if (this == NULL)
		return -1;
	this -> ptr   =        NULL;
	this -> index =        IV_POISON;
	iv_free(this);
	return 0;
}

/**
 * Moves iterator to next element
 * @param  this current iterator
 * @param  dest if not NULL copies current object before moving iterator
 * @return      1 if moved, 0 if not, -1 if iterator is invalid
 */
int vector_iter_next(vector_iter* this, void* dest)
{
	ITER_CHECK(this);

	if (dest != NULL)
		__copy_elem(this->ptr, this->index, dest);

	if (this->index < this->ptr->size - 1)
	{
		this->index += 1;
		return 1;
	}
	return 0;
}

/**
 * Moves iterator to previous element
 * @param  this current iterator
 * @param  dest if not NULL copies current object before moving iterator
 * @return 1 if moved, 0 if not, -1 if iterator is invalid
 */
int vector_iter_prev(vector_iter* this, void* dest)
{
	ITER_CHECK(this);

	if (dest != NULL)
		__copy_elem(this->ptr, this->index, dest);

	if (this->index > 0)
	{
		this->index -= 1;
		return 1;
	}
	return 0;
}

/**
 * Copies object, pointed by iterator
 * @param  this current iterator
 * @param  dest destination
 * @return      0 if success, -1 if failure
 */
int vector_iter_getelem (const vector_iter* this, void* dest)
{
	ITER_CHECK(this);
	if (dest == NULL)
		return -1;
	__copy_elem(this->ptr, this->index, dest);
	return 0;
}

/**
 * Replaces object, pointed by iterator, with argumented
 * @param  this current iterator
 * @param  src  
 * @return      0 if success, -1 if failure
 */
int vector_iter_setelem(vector_iter* this, const void* src)
{
	ITER_CHECK(this);
	if (src == NULL)
		return -1;
	__set_elem(this->ptr, this->index, src);
	return 0;
}

/**
 * Sets iterator to begin of vector
 * @param  this current iterator
 * @return      0 if success, -1 if "this" is NULL or vector is invalid
 */
int vector_iter_begin(vector_iter* this)
{
	if (this == NULL)
		return -1;
	VECTOR_CHECK(this->ptr);
	this->index = 0;
	return 0;
}

/**
 * Sets iterator to end of vector
 * @param  this current iterator
 * @return      0 if success, -1 if "this" is NULL or vector is invalid
 */
int vector_iter_end(vector_iter* this)
{
	if (this == NULL)
		return -1;
	VECTOR_CHECK(this->ptr);
	this->index = this->ptr->size - 1;
	return 0;
}

/**
 * Is the pointed object first??
 * @param  this current iterator
 * @return      1 if true, 0 if false, -1 if iterator is invalid
 */
int vector_iter_isbegin(const vector_iter* this)
{
	ITER_CHECK(this);
	if (this -> index == 0)
		return 1;
	return 0;
}

/**
 * Is the pointed object last??
 * @param  this current iterator
 * @return      1 if true, 0 if false, -1 if iterator is invalid
 */
int vector_iter_isend(const vector_iter* this)
{
	ITER_CHECK(this);
	if (this -> index == this -> ptr -> size - 1)
		return 1;
	return 0;
}


void* vector_iter_do(vector_iter* iter, void* args, void* (*proceed)(void* obj,void* argv))
{
	if (!__vector_iter_check(iter))
		return NULL;
	return proceed(__elem_ptr(iter->ptr, iter->index), args);
}
