#include "stdio.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "unistd.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/time.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>


enum errors {
        FIRST_ERROR      = -1000,
        SV_ARGS_TOOBIG,
        SV_ARGS_TOOSMALL,
        SV_ARGS_INVALARG,
        SV_ARGS_INVALNUM,
        SV_HND_CRTFAIL,
        SV_SETSOCK_FAIL,
        SV_GETSOCK_FAIL,
        SV_BIND_FAIL,
        SV_HNDSK_FAIL,
        SV_RECV_FAIL,

        CT_GETSOCK_FAIL,
        CT_SETSOCK_FAIL,
        CT_SEND_FAIL,
        CT_RECV_FAIL,
        CT_ALLOC_FAIL,

        LAST_ERROR
};

void __print_error(int line, int errnum);

#define print_error(num) __print_error(__LINE__, num);





#define BUFSIZE         1024
#define MAXPROC         128
#define MAXNODE         128
#define PORT            4201
#define HANDSHAKE_PORT  4202
#define HNDSK_TMOUT_SEC 600
#define HND_BUFSIZE     (4*1024)

