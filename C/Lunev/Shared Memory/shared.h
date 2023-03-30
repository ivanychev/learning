#ifndef __SHARED_H
#define __SHARED_H

//===============================================================================================================
//			Headers
//===============================================================================================================
#define _GNU_SOURCE

#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "assert.h"
#include "errno.h"
#include "fcntl.h"
#include "limits.h"
#include "stdio.h"
#include "stdlib.h"
#include <fcntl.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

//===============================================================================================================
//			Macroses
//===============================================================================================================

// #define DEBUG

#define F_LOCATION(stream)                                                     \
  fprintf(stream,                                                              \
          "File:     %s\n"                                                     \
          "Line:     %d\n"                                                     \
          "Function: %s\n",                                                    \
          __FILE__, __LINE__, __PRETTY_FUNCTION__);                            \
  fflush(stream);

#define LOCATION F_LOCATION(stdout)

#ifdef DEBUG

#define OUT(str)                                                               \
  printf(str);                                                                 \
  fflush(stdout);
#define OUT1(str, arg1)                                                        \
  printf(str, arg1);                                                           \
  fflush(stdout);
#define OUT2(str, arg1, arg2)                                                  \
  printf(str, arg1, arg2);                                                     \
  fflush(stdout);
#define OUT3(str, arg1, arg2, arg3)                                            \
  printf(str, arg1, arg2, arg3);                                               \
  fflush(stdout);
#define LOC_OUT(str)                                                           \
  LOCATION;                                                                    \
  printf(str);                                                                 \
  fflush(stdout);
#define LOC_OUT1(str, arg1)                                                    \
  LOCATION;                                                                    \
  printf(str, arg1);                                                           \
  fflush(stdout);
#define LOC_OUT2(str, arg1, arg2)                                              \
  LOCATION;                                                                    \
  printf(str, arg1, arg2);                                                     \
  fflush(stdout);

/*
CHECK(n != 1, "Error happened");

if (n != 1)
{
        printf("Error happened");
        perror("");
        return -1;
}
*/
* /

#else

#define OUT(str)                                                               \
  if (0)                                                                       \
    printf(str);
#define OUT1(str, arg1)                                                        \
  if (0)                                                                       \
    printf(str, arg1);
#define OUT2(str, arg1, arg2)                                                  \
  if (0)                                                                       \
    printf(str, arg1, arg2);
#define OUT3(str, arg1, arg2, arg3)                                            \
  if (0)                                                                       \
    printf(str, arg1, arg2, arg3);
#define LOC_OUT(str)                                                           \
  if (0)                                                                       \
    printf(str);
#define LOC_OUT1(str, arg1)                                                    \
  if (0)                                                                       \
    printf(str, arg1);
#define LOC_OUT2(str, arg1, arg2)                                              \
  if (0)                                                                       \
    printf(str, arg1, arg2);

#endif

#define F_CHECK_EXIT_CODE

#define F_CHECK(stream, cond, msg)                                             \
  if (!(cond)) {                                                               \
    F_LOCATION(stream);                                                        \
    fprintf(stream, "Message:  %s\n", msg);                                    \
    fflush(stream);                                                            \
    perror("ERRNO\t\t");                                                       \
    fputc('\n', stream);                                                       \
    F_CHECK_EXIT_CODE                                                          \
                                                                               \
    exit(EXIT_FAILURE);                                                        \
  }

#define CALL(func, var, cond, msg)                                             \
  var = func;                                                                  \
  CHECK(!((var)##cond), msg);

#define CHECK(cond, msg) F_CHECK(stdout, cond, msg)

#define F_WARN(stream, cond, msg)                                              \
  if (!(cond)) {                                                               \
    fprintf(stream, "WARNING>>>>\n");                                          \
    F_LOCATION(stream);                                                        \
    fprintf(stream, "Message:  %s\n", msg);                                    \
    fflush(stream);                                                            \
    perror("ERRNO\t\t");                                                       \
    fputc('\n', stream);                                                       \
    fprintf(stream, ">>>>>>>>>>>\n");                                          \
    fflush(stream);                                                            \
  }

#define WARN(cond, msg) F_WARN(stdout, cond, msg)

    //===============================================================================================================
    //				Constants (Code dependant)
    //===============================================================================================================

    const char *FILE_NAME_SHMEM_ATTACH = "SHARING.tmp";
const char *SND_FLAG = "SENDING.tmp";
const char *RCV_FLAG = "RECEIVING.tmp";
const long BUF_SIZE = 4 * 1024 * 1024;
const long BUF_SIZE_W_NBYTES = 4 * 1024 * 1024 + sizeof(long);

// #define		BUF_SIZE	  	(4 * 1024 * 1024)
// #define 	BUF_SIZE_WITH_NBYTES	(4 * 1024 * 1024 + sizeof())
#define PAGESIZE getpagesize()

enum SHARING_SEMAPHORS {
  SND_FINISHED = 0,
};

enum SENDING_SEMS {
  SND_MUTEX,
  RCV_MUTEX,
  SND_DIED,
  RCV_DIED,
  RCV_CONNECT,
};

//===============================================================================================================
//				Descriptions and prototypes (Code dependant)
//===============================================================================================================

#define PFS(semid, num)                                                        \
  OUT1("[Line = %d] Printing flags...\n", __LINE__);                           \
  for (int k = 0; k < num; ++k) {                                              \
    OUT2("[%d] - %d\n", k, semctl(semid, k, GETVAL));                          \
  }                                                                            \
  OUT("\n");

struct Wait_for {
  int semid;
  int num;
  char *msg;
};

int send(const char *filename);

int receive();

int is_sender(int *);

int is_receiver(int *);

void *kill_if_died(void *ptr);

int snd_protect_connection(int semid);

int rcv_protect_connection(int semid);

int snd_clean(int semid, int fileid, int shmemid, int flagid);

int get_sems(const char *filename, int num);

void *get_memptr(const char *filename, size_t size, int *id_to_save);

int set_memory(const char *filename, size_t size, int *need_to_init);

//===============================================================================================================
//===============================================================================================================

#endif