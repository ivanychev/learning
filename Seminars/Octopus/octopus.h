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

#define BUFSIZE 	(4 * 1024 * 1024)
const unsigned      BITSPERBYTE = 8;


//===============================================================================================================
//				Descriptions and prototypes (Code dependant)
//===============================================================================================================

void go_child(char const* filename);

void go_parent(pid_t child);

int getbit(void* ptr, unsigned offset, unsigned bit_index);

int writebit(char* buf, unsigned long index);

int sendbit(pid_t dad, int bit, const sigset_t* now);

int send(pid_t dad, void* buf, long len, const sigset_t* ignored);

int child_sigterm_set();

int child_sigusr1_set();

void child_sigusr1_handler(int sigid);

void child_sigterm_handler(int sigid);

void clear_child();

int parent_set_handlers(sigset_t blocked);

int print_buf(char* buf, unsigned long nbits);

int set_block_mask(sigset_t* blocked);

int set_wait_mask(sigset_t* wait);




#endif