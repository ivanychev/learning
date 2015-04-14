/**
 * 	@brief 		Common function implementation routines here
 * 	@detailes 	Function implementations:
 * 	
 * 			iv_getfilesize
 * 			iv_allocbuffer_copy
 * 			iv_getlong
 * 			
 * 	@version 	0.1
 * 	
 * 	@author 	Sergey Ivanychev
 * 	@par 		sergeyivanychev@gmail.com 
 */

#include "string.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "errno.h"
#include "stdint.h"
#include "inttypes.h"
#include "limits.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "stdlib.h"
#include "iv_standard.h"
#include "stdio.h"

#define BUFSIZE 4096
#define ONEXIT
#define RETURN(val) do {ONEXIT return val;} while (0);

char const* iv_msgs[] = {
	"Argumented pointer is null",
	"Failed to open the file",
	"Invalid pid",
	"Size is below zero",
	"Invalid number of arguments",
	"Memory allocation failed"
};





//=========================================================================================

int iv_getfilesize(const char* path, size_t* to_save)
{
	if (path == NULL || to_save == NULL)
		RETURN(IV_INVALARGS);

	struct stat st;
	int cond = stat(path, &st);	
	if  (cond != 0)
		RETURN(IV_STATFAIL);
	*to_save = (size_t)st.st_size;
	return 0;
}

//=========================================================================================

int iv_allocbuffer_copy(const char* path, char** copy, size_t* file_size)
{
	if (path == NULL || copy == NULL)
		RETURN(IV_INVALARGS);

	int fd = open(path, O_RDONLY);
	if (fd == -1)
		RETURN(IV_OPENFAIL);

#undef  ONEXIT
#define ONEXIT close(fd);

	size_t size = 0;
	int cond = iv_getfilesize(path, &size);
	if (cond != 0)
		RETURN(cond);

	char* my_copy =  malloc(size);
	if (  my_copy == NULL)
		RETURN(IV_ALLOCFAIL);
#undef  ONEXIT
#define ONEXIT close(fd); free(my_copy);

// 	char* buf = malloc(BUFSIZE);
// 	if (buf == NULL)
// 		RETURN(IV_BUFALLOCFAIL);
// #undef  ONEXIT
// #define ONEXIT close(fd); free(my_copy); free(buf);

	size_t copied = 0;
	size_t iteration = 0;

	while (copied < size)
	{
		iteration = read(fd, my_copy + copied, BUFSIZE);
		if (iteration == -1)
			RETURN(IV_READFAIL);
		copied += iteration;
	}

	if (copied != size)
		RETURN(IV_COPYSIZEFAIL);

	*copy = my_copy;
	*file_size = size;
	
	close(fd);

	return 0;
}
#undef  ONEXIT
#define ONEXIT

//=========================================================================================

int iv_getlong(long* save, const char* str)
{
	if (save == NULL || str == NULL)
		RETURN(IV_INVALARGS);

	int base = 10;
	char* endptr = NULL;

	long val = strtol(str, &endptr, base);

	if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
	       || (errno != 0 && val == 0)
	       || (void*)endptr == (void*)str) {
	   	RETURN(IV_NONUMBER);
	}

	*save = val;
	return 0; 
}


//=========================================================================================