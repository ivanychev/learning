#ifndef __PIPE_H
#define __PIPE_H

//===============================================================================================================
//			Headers
//===============================================================================================================

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <fcntl.h>
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "assert.h"
#include "errno.h"
#include "limits.h"

//===============================================================================================================
//			Macroses
//===============================================================================================================

//#define DEBUG

#ifdef 	DEBUG
#define OUT(str) 		printf(str);
#define OUT1(str, arg1)		printf(str, arg1);
#define OUT2(str, arg1, arg2)	printf(str, arg1, arg2);

#else

#define OUT(str) 		if (0)	printf(str);
#define OUT1(str, arg1)		if (0)	printf(str, arg1);
#define OUT2(str, arg1, arg2)	if (0)	printf(str, arg1, arg2);

#endif

#ifdef QUEUE_EXISTS
#define CHECK(cond, msg)					\
	if (!(cond))						\
	{							\
		fprintf(stderr, "File:\t\t%s\n"			\
				"Line: \t\t%d\n"		\
					"Message:\t%s\n",	\
				__FILE__,			\
				__LINE__,			\
				msg);				\
		perror("ERRNO\t\t");				\
		putchar('\n');					\
		msgctl(queue_id, IPC_RMID, NULL);		\
								\
		exit(EXIT_FAILURE);				\
	}							\

#else
#define CHECK(cond, msg)					\
	if (!(cond))						\
	{							\
		fprintf(stderr, "File:\t\t%s\n"			\
				"Line: \t\t%d\n"		\
				"Message:\t%s\n",		\
				__FILE__,			\
				__LINE__,			\
				msg);				\
		perror("ERRNO\t\t");				\
		putchar('\n');					\
								\
		exit(EXIT_FAILURE);				\
	}	
#endif


//===============================================================================================================
//				Constants
//===============================================================================================================

enum ERR_CONST
{
	ERR_CONST_BEGIN = 1000,
	ERR_CONST_END
};

const char*	SEND_NAME 	= "/tmp/IV_SEND";
const char* 	RECEIVE_NAME	= "/tmp/IV_RECEIVE";
const char* 	FIFO_NAME	= "IV_FIFO";
#define		BUF_SIZE	  1024 * 1024

//===============================================================================================================
//				Descriptions and prototypes
//===============================================================================================================
int send(char const* filename);

int receive();

int is_sender();

int is_receiver();

//===============================================================================================================
//===============================================================================================================

#endif