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
#include <string.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <assert.h>
#include "../../Determinant/ivmatrix.h"

enum errors {
        FIRST_ERROR      = -1000,
        NEUTRAL_ERROR,

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
        SV_MATRIX_GET_FAIL,
        SV_ALLOC_FAIL,
        SV_ACCEPT_FAIL,

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
        CT_CONNECT_FAIL,
        CT_MATR_SEND_FAIL,

        LAST_ERROR
};

typedef struct ct_thread_meta_s {
        int             sem;
        int             ips;
        int             num;
        int             msgid;
        struct in_addr  server;
        const matrix*   cur;
        double          result;
        pthread_t       id;
        int             sk;
        int             finish_cond;    // 0 if OK, -1 if failed
        struct ct_thread_meta_s* meta_arr;
} ct_thread_meta;

typedef struct {
        long            mtype;
        uint32_t        minor;
} ct_task;

typedef struct 
{
        int sk;
        int sem;
} beater_meta;

typedef struct {
        int             status;         // 0 - answer, 1 - wait, -1 - error
        double          val;
} sv_answer;
#define SV_ANSWER_VAL   0
#define SV_ANSWER_WAIT  1
#define SV_ANSWER_ERR  -1

void __print_error(int line, const char* filename, int errnum);

#define print_error(num) __print_error(__LINE__, __FILE__, num)
#define DP(n) fprintf(stderr, "[%d]POINT "#n"\n", __LINE__);






#define BUFSIZE         1024
#define MAXPROC         128
#define MAXNODE         128
#define RECV_TIMEOUT    30
#define PORT            4201
#define HANDSHAKE_PORT  4202
#define HNDSK_TMOUT_SEC 600
#define RCV_TMOUT_SEC   8
#define SND_TMOUT_SEC   8
#define SND_ATTEMPTS    4

#define BEAT_TIMEOUT    4               // should be less than RCV_TMOUT
#define MTU             (63*1024)
#define HND_BUFSIZE     (4*1024)

#define WAIT  ((uint64_t)0x010101010101)
#define NOW   ((uint64_t)0x010101010111)
#define FIN   ((uint32_t)0x111111111110)

#define LABEL           fprintf(stderr, "[%s: %d]\n", __FILE__, __LINE__)


int get_det(const matrix* current, double* res_tosave, int ips, struct in_addr* ips_array);

#define rcv_acc(sk)             __rcv_acc(sk, __LINE__)
#define snd_acc(sk, dest)       __snd_acc(sk, dest, __LINE__)

int __rcv_acc(int sk, int line);

int __snd_acc(int sk, struct sockaddr_in* dest, int line);

int __tcp_sreceiver(int sk, char* buf, size_t size, int line);

int __tcp_ssender(  int sk, char* buf, size_t size, int line);

#define tcp_ssend(sk, buf, size) __tcp_ssender  (sk, buf, size, __LINE__)
#define tcp_srecv(sk, buf, size) __tcp_sreceiver(sk, buf, size, __LINE__)


int tcp_sacc(int sk);

int tcp_racc(int sk);

int set_default_timeouts(int sk);

