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


int vector_iter_del(vector_iter* this)
{
	if (this == NULL)
		return -1;
	this -> ptr   =        NULL;
	this -> index =        IV_POISON;
	iv_free(this);
	this = NULL;

	return 0;
}

//==========================================================================================
//==========================================================================================

int vector_iter_next(vector_iter* this, void* dest)
{
	ITER_CHECK(this);

	if (this->ptr->size == 0)
		return 0;

	if (dest != NULL)
		__copy_elem(this->ptr, this->index, dest);

	if (this->index < this->ptr->size - 1)
	{
		this->index += 1;
		return 1;
	}
	return 0;
}


int vector_iter_prev(vector_iter* this, void* dest)
{
	ITER_CHECK(this);
	if (this->ptr->size == 0)
		return 0;
	if (dest != NULL)
		__copy_elem(this->ptr, this->index, dest);

	if (this->index > 0)
	{
		this->index -= 1;
		return 1;
	}
	return 0;
}
//==========================================================================================
//==========================================================================================

int vector_iter_getelem (const vector_iter* this, void* dest)
{
	ITER_CHECK(this);
	if (dest == NULL || this->ptr->size == 0)
		return -1;
	__copy_elem(this->ptr, this->index, dest);
	return 0;
}

//==========================================================================================
//==========================================================================================

int vector_iter_setelem(vector_iter* this, const void* src)
{
	ITER_CHECK(this);
	if (src == NULL || this->ptr->size == 0)
		return -1;
	__set_elem(this->ptr, this->index, src);
	return 0;
}

//==========================================================================================
//==========================================================================================

int vector_iter_begin(vector_iter* this)
{
	if (this == NULL)
		return -1;
	VECTOR_CHECK(this->ptr);
	this->index = 0;
	return 0;
}


int vector_iter_end(vector_iter* this)
{
	if (this == NULL)
		return -1;
	VECTOR_CHECK(this->ptr);
	this->index = this->ptr->size - 1;
	return 0;
}

//==========================================================================================
//==========================================================================================

int vector_iter_isbegin(const vector_iter* this)
{
	ITER_CHECK(this);
	if (this -> index == 0 && this->ptr->size != 0)
		return 1;
	return 0;
}

int vector_iter_isend(const vector_iter* this)
{
	ITER_CHECK(this);
	if (this -> index == this -> ptr -> size - (int64)1)
		return 1;
	return 0;
}

//==========================================================================================
//==========================================================================================

void* vector_iter_do(vector_iter* iter, void* args, void* (*proceed)(void* obj,void* argv))
{
//	fprintf(stderr, "Hello!");
	if (!__vector_iter_check(iter) || !__vector_check(iter->ptr) || !proceed)
		return NULL;
//	__vector_dump(iter->ptr);
	return proceed(__elem_ptr(iter->ptr, iter->index), args);
}

