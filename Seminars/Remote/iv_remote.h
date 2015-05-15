#include "stdio.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/msg.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "unistd.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/time.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <assert.h>
#include "../Determinant/ivmatrix.h"

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
        SV_INVAL_MATRIX,

        CT_GETSOCK_FAIL,
        CT_SETSOCK_FAIL,
        CT_SEND_FAIL,
        CT_RECV_FAIL,
        CT_ALLOC_FAIL,
        CT_MYIP_FAIL,
        CT_BIND_FAIL,
        CT_SCAN_FAIL,
        CT_MATR_READ_FAIL,
        CT_DET_CALC_FAIL,
        CT_INVL_ARG,
        CT_EMPTY_NET,
        CT_TEMP_CREAT_FAIL,
        CT_FTOK_FAIL,
        CT_SEM_FAIL,
        CT_MSG_FAIL,
        CT_ALL_THREADS_FAILED,
        CT_THR_SOCK_CREATE_FAIL,
        CT_THR_BIND_FAIL,
        CT_THR_SEND_MATR_FAIL,
        CT_FILL_FAIL,
        CT_THREAD_CREAT_FAIL,

        LAST_ERROR
};

typedef struct {
        int             sem;
        int             msgid;
        struct in_addr  server;
        const matrix*   cur;
        double          result;
        pthread_t       id;
        int             finish_cond;    // 0 if OK, -1 if failed
} ct_thread_meta;

typedef struct {
        long            mtype;
        uint32_t        minor;
} ct_task;

void __print_error(int line, const char* filename, int errnum);

#define print_error(num) __print_error(__LINE__, __FILE__, num);





#define BUFSIZE         1024
#define MAXPROC         128
#define MAXNODE         128
#define RECV_TIMEOUT    30
#define PORT            4201
#define HANDSHAKE_PORT  4202
#define HNDSK_TMOUT_SEC 600
#define HND_BUFSIZE     (4*1024)


int get_det(const matrix* current, double* res_tosave, int ips, struct in_addr* ips_array);

int rcv_acc(int sk);

int snd_acc(int sk, struct sockaddr_in* dest);

