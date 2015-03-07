#include "stdint.h"

/**
 *
 * 
 */

#ifdef VECTOR_COMPILE_MAXSIZE
const uint32_t MAXSIZE = VECTOR_COMPILE_MAXSIZE;
#else
const uint32_t MAXSIZE = 4 * 1024 * 1024;
#endif

const uint32_t POISON = 0xDEADBEEF;


struct vector_s
{
	uint32_t alloc;
	uint32_t size;
	uint32_t maxsize;
	uint32_t esize;
	uint32_t emaxsize;
	char* begin;
}

/**
 * VECTOR_INIT 		- initializing vector of argumented type macro
 * @name 		- name of new vector
 * @type 		- type of contained elements
 */

#define vector_init(name, type)	 	\
 	struct vector_s name = {	\
 		.alloc = 0, 		\
 		.size = 0, 		\
 		.maxsize = MAXSIZE, 	\
 		.esize = sizeof(type), 	\
 		.emaxsize = MAXSIZE, 	\
 		.begin = NULL		\
 	}

/**
 * vector_for_each 	- iterate over vector
 * @name 		- name of iterated vector
 * @pos 		- char* cursor pointer to iterated copies
 */

#define vector_for_each(name, pos) 	\
 	for (pos = (name).begin; pos < ((name).begin + size); pos += (name).esize)

 /**
  * vector_for_each_prev- iterate backwards
  * @name 		- name of iterated vector
  * @pos 		- char* cursor pointer to iterated copies
  */
 
 #define vector_for_each_prev(name, pos)				\
  	if ((name).size > 0) for 	(pos = (name).begin + size; 	\
  					 pos >= (name).begin; 		\
  					 pos -= (name).esize)


// *
//  * vector_at
//  * @param  	name  vector name
//  * @param  	index index of requested object
//  * @return      void* pointer
 

// #define vector_at(name, index) 		\
//   	...