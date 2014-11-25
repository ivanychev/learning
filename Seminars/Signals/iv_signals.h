#ifndef __IVSIGNAL_H
#define __IVSIGNAL_H

//===============================================================================================================
//			Headers
//===============================================================================================================
#define _GNU_SOURCE

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/shm.h>

#include <fcntl.h>
#include "stdio.h"
#include "stdlib.h"
#include <unistd.h>
#include "fcntl.h"
#include "assert.h"
#include "errno.h"
#include "limits.h"
#include <pthread.h>
#include <string.h>
#include <signal.h>
#include <sys/prctl.h>

//===============================================================================================================
//			Macroses
//===============================================================================================================

#define DEBUG

#define F_LOCATION(stream)			\
	fprintf(stream, "File:     %s\n"	\
			"Line:     %d\n"	\
			"Function: %s\n",	\
			__FILE__,		\
			__LINE__,		\
			__PRETTY_FUNCTION__);	\
	fflush(stream);			

#define LOCATION F_LOCATION(stdout)

							
#ifdef 	DEBUG

#define OUT(str) 					printf(str);			fflush(stdout);		
#define OUT1(str, arg1)					printf(str, arg1);		fflush(stdout);
#define OUT2(str, arg1, arg2)				printf(str, arg1, arg2);	fflush(stdout);
#define OUT3(str, arg1, arg2, arg3)			printf(str, arg1, arg2, arg3);	fflush(stdout);
#define LOC_OUT(str) 			LOCATION;	printf(str);			fflush(stdout);		
#define LOC_OUT1(str, arg1)		LOCATION;	printf(str, arg1);		fflush(stdout);
#define LOC_OUT2(str, arg1, arg2)	LOCATION;	printf(str, arg1, arg2);	fflush(stdout);


#else

#define OUT(str)			if (0)		printf(str);
#define OUT1(str, arg1)			if (0)		printf(str, arg1);
#define OUT2(str, arg1, arg2)		if (0)		printf(str, arg1, arg2);
#define OUT3(str, arg1, arg2, arg3)	if (0)		printf(str, arg1, arg2, arg3);
#define LOC_OUT(str) 			if (0)		printf(str);				
#define LOC_OUT1(str, arg1)		if (0)		printf(str, arg1);	
#define LOC_OUT2(str, arg1, arg2)	if (0)		printf(str, arg1, arg2);


#endif

#define F_CHECK_EXIT_CODE

#define F_CHECK(stream, cond, msg)				\
	if (!(cond))						\
	{							\
		F_LOCATION(stream);				\
		fprintf(stream, "Message:  %s\n", msg);		\
		fflush(stream);					\
		perror("ERRNO\t\t");				\
		fputc('\n', stream);				\
		F_CHECK_EXIT_CODE				\
								\
		exit(EXIT_FAILURE);				\
	}							\

#define CALL(func, var, cond, msg)				\
	var = func;						\
	CHECK(!((var)##cond), msg);				\


#define CHECK(cond, msg) F_CHECK(stdout, cond, msg)

#define F_WARN(stream, cond, msg)			\
if (!(cond))						\
{							\
	fprintf(stream, "WARNING>>>>\n");		\
	F_LOCATION(stream);				\
	fprintf(stream, "Message:  %s\n", msg);		\
	fflush(stream);					\
	perror("ERRNO\t\t");				\
	fputc('\n', stream);				\
	fprintf(stream, ">>>>>>>>>>>\n");		\
	fflush(stream);					\
}							\

#define WARN(cond, msg) F_WARN(stdout, cond, msg)

enum ERROR_MESSAGES
{
	IVPTRNULL,
	IVFOPENFAIL,
	IVINVALPID,
	IVNEGSIZE,
};

char const* iv_msgs[] = {
	"Argumented pointer is null",
	"Failed to open the file",
	"Invalid pid",
	"Size is below zero"
};

//===============================================================================================================
//				Constants (Code dependant)
//===============================================================================================================

const unsigned long BUFSIZE 	= 4 * 1024 * 1024;
const unsigned      BITSPERBYTE = 8;


//===============================================================================================================
//				Descriptions and prototypes (Code dependant)
//===============================================================================================================

void go_child(char const* filename);

void go_parent(pid_t child);

int getbit(void* ptr, unsigned offset, unsigned bit_index);

int send(pid_t dad, void* buf, long len);

int child_sigterm_set();

void clear_child();

int parent_set_handlers(sigset_t blocked);

int print_buf(char* buf, unsigned long nbits);


//===============================================================================================================
//				Globals
//===============================================================================================================



//===============================================================================================================
//===============================================================================================================


#endif