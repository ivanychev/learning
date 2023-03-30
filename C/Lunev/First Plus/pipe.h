#ifndef __PIPE_H
#define __PIPE_H

//===============================================================================================================
//			Headers
//===============================================================================================================
#define _GNU_SOURCE

#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "assert.h"
#include "errno.h"
#include "fcntl.h"
#include "limits.h"
#include "stdio.h"
#include "stdlib.h"
#include <fcntl.h>
#include <unistd.h>

//===============================================================================================================
//			Macroses
//===============================================================================================================

#define DEBUG

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

#define CHECK(cond, msg) F_CHECK(stdout, cond, msg)

//===============================================================================================================
//				Constants (Code dependant)
//===============================================================================================================

enum ERR_CONST { ERR_CONST_BEGIN = 1000, ERR_CONST_END };

enum FORCED_OPEN_FIFO_COND {
  FOFC_FILE_EXIST,
  FOFC_FILE_CREATED,
  FOFC_OPEN_ERROR
};

const char *SEND_NAME = "/tmp/IV_SEND";
const char *RECEIVE_NAME = "/tmp/IV_RECEIVE";
const char *FIFO_NAME = "IV_FIFO";
const char *SENDER_FLAG = "sender.flag";
const char *RECEIVE_FLAG = "receive.flag";

#define BUF_SIZE 1024 * 1024

//===============================================================================================================
//				Descriptions and prototypes (Code dependant)
//===============================================================================================================
int send(char const *filename);

int receive();

int is_sender(int *flag_save);

int is_receiver(int *flag_save);

int is_it(int *flag_save, const char *name);

int forced_open_fifo(const char *name, mode_t mode, int flags, int *to_save);
//===============================================================================================================
//===============================================================================================================

#endif