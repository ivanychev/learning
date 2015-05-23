#ifndef __IV_OCTOPUS
#define __IV_OCTOPUS



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
//				Constants (Code dependant)
//===============================================================================================================

const unsigned 	BUFBLOCK    	= 1111;
const unsigned  WRITEBUFSIZE	= 64 * 1024;
const unsigned  READBUFSIZE	= 64 * 1024;
const unsigned  BUFSIZE 	= 64 * 1024;
const unsigned  BITSPERBYTE 	= 8;

const int READ  = 0;
const int WRITE = 1;


//===============================================================================================================
//				Descriptions and prototypes (Code dependant)
//===============================================================================================================

typedef struct
{
	pid_t 	procid;
	int 	to_read;
	int 	to_write;
	char*	buf;
	long 	contain;
	long    size;
	int     index;
	long long read;
	long long written;
} tentacle;

/*
typedef struct
{
	pid_t 	procid;
	int 	to_read;
	int 	to_write;
	char*	buf;
	long 	begin;
	long 	end;
	long 	contain;
	long    size;
	int     index;
} tentacle;
 */	

typedef struct 
{
	int 	to_read;
	int 	to_write;
	int 	index;
} tentacle_in;

typedef struct
{
	int rw[2];
} pipe_io;


int nonblock_ids(int kids_num, tentacle* kids_info);

int proceed(int kids_num, tentacle* kids_info);

int transfer_operations(tentacle* kids_info, int kids_num, fd_set sndset, fd_set rcvset);

int read_from_tentacle(tentacle* reading);

int write_to_tentacle(tentacle* from, int writeid);

int getsnd(	int kids_num, 
		tentacle* kids_info, 
		fd_set* sndset,
		int* maxsndid);

int getrcv(	int kids_num, 
		tentacle* kids_info, 
		fd_set* rcvset,
		int* maxrcvid);

int activate_kids(int num, tentacle* kids_info, const char* filename);

int close_pipes(int index, tentacle* kids_info);

int create_bufs(int num, tentacle* kids);

int first_kid_deal(tentacle* info, const char* filename);

void tentacle_proceed(tentacle_in info);

int get_long(long* save, const char* str);




#endif