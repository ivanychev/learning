#include "inttypes.h"
#include "stdint.h"
#include "stdio.h"
#include "unistd.h"
#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <sys/types.h>

#define PORT 4201
#define RCV_TMOUT_SEC 8
#define SND_TMOUT_SEC 8

typedef struct {
  uint32_t day;
  uint32_t hour;
  uint32_t min;
  uint32_t type;
  int32_t index;
} Case;

enum CASE_TYPES { TAKEOFF = 1, LANDING = 2 };

typedef struct {
  uint32_t type;
  Case task;
} task;

typedef struct {
  int32_t sk;
  int32_t msgid;
  int32_t index;

} configure_meta;
