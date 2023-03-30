#ifndef __QUEUE_H
#define __QUEUE_H

//===============================================================================================================
//			Headers
//===============================================================================================================

#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "assert.h"
#include "errno.h"
#include "limits.h"
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include <fcntl.h>

//===============================================================================================================
//			Macroses
//===============================================================================================================

// #define DEBUG

#ifdef DEBUG
#define OUT(str) printf(str);
#define OUT1(str, arg1) printf(str, arg1);
#define OUT2(str, arg1, arg2) printf(str, arg1, arg2);

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

#endif

#ifdef QUEUE_EXISTS
#define CHECK(cond, msg)                                                       \
  if (!(cond)) {                                                               \
    fprintf(stderr,                                                            \
            "File:\t\t%s\n"                                                    \
            "Line: \t\t%d\n"                                                   \
            "Message:\t%s\n",                                                  \
            __FILE__, __LINE__, msg);                                          \
    perror("ERRNO\t\t");                                                       \
    putchar('\n');                                                             \
    msgctl(queue_id, IPC_RMID, NULL);                                          \
                                                                               \
    exit(EXIT_FAILURE);                                                        \
  }

#else
#define CHECK(cond, msg)                                                       \
  if (!(cond)) {                                                               \
    fprintf(stderr,                                                            \
            "File:\t\t%s\n"                                                    \
            "Line: \t\t%d\n"                                                   \
            "Message:\t%s\n",                                                  \
            __FILE__, __LINE__, msg);                                          \
    perror("ERRNO\t\t");                                                       \
    putchar('\n');                                                             \
                                                                               \
    exit(EXIT_FAILURE);                                                        \
  }
#endif

//===============================================================================================================
//				Constants
//===============================================================================================================

enum ERR_CONST { ERR_CONST_BEGIN = 1000, GET_OK, GET_FAILED, ERR_CONST_END };

long MSG_VAL = 42;

//===============================================================================================================
//				Descriptions and prototypes
//===============================================================================================================

const char *QUEUE_FILE = "queue.file";

typedef struct Long_msg_t {
  long type;
  long val;
} Long_msg;

int get_long(long *save, int argc, const char *str);

int child_part(int queue_id, int proc_num, int proc_index);

int parent_part(int queue_id, int proc_num);

//===============================================================================================================
//===============================================================================================================

#endif