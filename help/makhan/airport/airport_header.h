#include "stdio.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/msg.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/syscall.h>
#include "unistd.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/time.h>
#include <errno.h>
#include <stdlib.h>
#include "stdint.h"
#include "inttypes.h"
#include <string.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <assert.h>

#define PORT 4201
#define RCV_TMOUT_SEC   8
#define SND_TMOUT_SEC   8

typedef struct {
        uint32_t day;
        uint32_t hour;
        uint32_t min;
        uint32_t type;
        int32_t index;  
} Case;



enum CASE_TYPES {
        TAKEOFF = 1,
        LANDING = 2
};


typedef struct {
        uint32_t type;
        Case task;
} task;

typedef struct 
{
        int32_t sk;
        int32_t msgid;
        int32_t index;

} configure_meta;
