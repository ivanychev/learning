#include "ivvector.h"
#include "ivvector_internal.h"
#include "stdio.h"

#define CONDITION (rand() % 3 != 0)



inline void* iv_calloc(size_t nmemb, size_t size)
{
	if (CONDITION) 
		return calloc(nmemb, size);
	return NULL;
}

inline void iv_free(void* ptr)
{
	free(ptr);
	ptr = NULL;
}

inline void* iv_realloc(void* ptr, size_t size)
{
	if (CONDITION)
		return realloc(ptr, size);
	free(ptr);
	ptr = NULL;

	return NULL;
}

int __vector_check(const vector* checked)
{
#ifndef DEBUG
	return (checked != NULL &&
		checked->size <= checked->alloc &&
		(	(checked->alloc == 0 && checked->begin == NULL)
			||
			(checked->alloc != 0 && checked->begin != NULL)) &&
		checked->size  <= checked->maxsize &&
		checked->esize <= checked->emaxsize);
#else	
	int cond =     (checked != NULL &&
			checked->size <= checked->alloc &&
			(	(checked->alloc == 0 && checked->begin == NULL)
			||
				(checked->alloc != 0 && checked->begin != NULL)) &&
			checked->size  <= checked->maxsize &&
			checked->esize <= checked->emaxsize);
	if (cond == 0)
	{
		fprintf(stderr, "Vector verification failed:\n");
		__vector_dump(checked);
	}
	return cond;
#endif
}

/**
 * Validates iterator
 * @param  checked validating iterator
 * @return         1 if OK, 0 if not
 */

inline int __vector_iter_check(const vector_iter* checked)
{
#ifndef DEBUG
	return 		(checked != NULL      &&
			 checked->ptr != NULL &&
			(checked->index < checked->ptr->size
			 	||
			 (checked->index == 0
			  		&&
			  checked->ptr->size == 0)));
#else
	int cond = 	(checked != NULL      &&
			 checked->ptr != NULL &&
			(checked->index < checked->ptr->size
			 	||
			(checked->index == 0
			  		&&
			 checked->ptr->size == 0)) &&
			 __vector_check(checked->ptr));
	if (cond == 0)
	{
		fprintf(stderr, "Vector iterator verification failed:\n");
		__vector_iter_dump(checked);
	}
	return cond;
#endif
}

/**
 * Prints detailed information about iterator copy
 * @param iter current iterator
 */
void __vector_iter_dump(const vector_iter* iter)
{
	if (iter == NULL)
		return;

	fprintf(stderr, "Vector iterator [%p] dump: Vector [%p], index[%"PRIu32"]\n",
			iter, iter->ptr, iter->index);
	
	if (iter->ptr != NULL)
	{
		fprintf(stderr, "Vector dump below\n");
		__vector_dump(iter->ptr);
	}
	else
		fputc('\n', stderr);
	fprintf(stderr, "Vector iterator dump end\n\n");	
}

/**
 * Prints detailed information about current vector object
 * @param this current object
 */
void __vector_dump(const vector* this)
{
	if (this == NULL)
		return;
	fprintf(stderr, "Vector [%p] dump:\n"
			"Allocated:     %"PRIu32 "\n"
			"Size:          %"PRIu32 "\n"
			"Max size:      %"PRIu32 "\n"
			"Elem size:     %"PRIu32 "\n"
			"Max elem size: %"PRIu32 "\n"
			"Array begin:   [%p]"   "\n"
			"Destructor ptr:[%p]"   "\n"
			"Vector dump end"	"\n",
			this,
			this->alloc,
			this->size,
			this->maxsize,
			this->esize,
			this->emaxsize,
			this->begin,
			this->destr);
// DELETE THIS (USED TO FIND BUGS)
		// if (this->begin != NULL)
		// 	for (uint32 i = 0; i < this -> size; ++i)
		// 		printf("%d ", ((int*)(this->begin))[i]);
		// 		
		//
		putchar('\n');
}


/**
 * Gets pointer of index'th element of vector
 * @param this  current vector
 * @param index 
 */
inline void* __elem_ptr(const vector* this, uint32 index)
{
	// fprintf(stderr, "this->begin = [%p], index = %"PRIu32", this->esize = %"PRIu32"\n", 
	// 	this->begin, index, this->esize);
	return (void*)( (unsigned long)(this->begin) + 
			BYTES_IN_ELEMS(this, index));
}

inline void __copy_elem(const vector* this, uint32 index, void* dest)
{
	 // fprintf(stderr, "this = [%lu], index = %"PRIu32", from = [%lu], dest = [%p]", 
	 // 	(unsigned long)this, index, (unsigned long)__elem_ptr(this, index), dest);
	
	memmove(dest, __elem_ptr(this, index), this->esize);
}

inline void __set_elem(vector* this, uint32 index, const void* src)
{
	memmove(__elem_ptr(this, index), src, this->esize);
}

