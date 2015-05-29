#include "stdio.h"
#include "../include/iv_remote.h"


char const* errors_msgs[] = {
        "",
        "Error occured",
        "Server error:\n"
        "Too big number: argument must be \"auto\" or in [1..#MAXPROC]\n",
        "Server error:\n"
        "Too small number: argument must be \"auto\" or in [1..#MAXPROC]\n",
        "Server error:\n"
        "Invalid argument: argument must be \"auto\" or in [1..#MAXPROC]\n",
        "Server error:\n"
        "There must be 2 extra arguments",

        "Server error:\n"
        "Failed to set up handshaker",
        "Server error:\n"
        "Failed to set socket",
        "Server error:\n"
        "Failed to get socket",
        "Server error:\n"
        "Failed to bind",
        "Server error:\n"
        "Failed to establish handshake thread",
        "Server error:\n"
        "recvfrom() failed",
        "Server error:\n"
        "Got invalid matrix",
        "Server error:\n"
        "Failed to get matrix",
        "Server error:\n"
        "Failed to allocate memory",
        "Server error:\n"
        "Failed to accept()",

        "Client error:\n"
        "Failed to get socket",
        "Client error:\n"
        "Failed to set socket",
        "Client error:\n"
        "Failed to send package",
        "Client error:\n"
        "Failed to receive package",
        "Client error:\n"
        "Memory allocation failed",
        "Client error:\n"
        "Failed to get IP adress of the standard interface",
        "Client error:\n"
        "Failed to bind",
        "Client error:\n"
        "Network scan failed",
        "Client error:\n"
        "Matrix read failed",
        "Client error:\n"
        "Determinant calculation failed",
        "Client error:\n"
        "Invalid argument passed",
        "Client error:\n"
        "No servers in current network",
        "Client error:\n"
        "Failed to create empty file",
        "Client error:\n"
        "Failed to get System V key",
        "Client error:\n"
        "Semaphore creation failed",
        "Client error:\n"
        "Message queue creation failed",
        "Client error:\n"
        "All threads failed to execute",
        "Client thread error:\n"
        "Failed to create socket",
        "Client thread error:\n"
        "Bind() failed",
        "Client thread error:\n"
        "Failed to send matrix",
        "Client error:\n"
        "Failed to fill message queue with tasks",
        "Client error:\n"
        "Failed to create thread",
        "Client error:\n"
        "Failed to connect",
        "Client error:\n"
        "Failed to send matrix"
        ""
        
};


void __print_error(int line, const char* filename, int errnum) 
{
       static char buf[1024];
       if (FIRST_ERROR <= errnum && errnum< LAST_ERROR){
                sprintf(buf, 
                        "%s: %d: %s\n", 
                        filename,
                        line, 
                        errors_msgs[errnum - FIRST_ERROR]);
                perror(buf);
        } 
}

const uint64_t      ACC_PACK = 0xaccaccaccacc;
const unsigned      MAXTIMEO = 16;

int __snd_acc(int sk, struct sockaddr_in* dest, int line) {
    int cond = 0;
    assert(sk > 0);
    assert(dest);
    cond = sendto(sk, &ACC_PACK, sizeof(ACC_PACK), 0, (struct sockaddr*)dest, 
                                                                sizeof(*dest));
    if (cond == -1){
        printf("%d: NOT sent ACC\n", line);
        return -1;
    }
    printf("%d: Sent ACC\n", line);
    return 0;
}

int __rcv_acc(int sk, int line) {
    int cond = 0;
    unsigned timeout = 1;
    uint64_t buf = 0;
    assert(sk > 0);
    printf("%d: Waiting for ACC\n", line);

    while ((cond = recv(sk, &buf, sizeof(buf), MSG_DONTWAIT)) == -1 && 
            (errno == EAGAIN || errno == EWOULDBLOCK) &&
            timeout < MAXTIMEO) {
        sleep(timeout);
        timeout *= 2;
    }

    if (cond == sizeof(buf) && buf == ACC_PACK) {
        printf("%d: Received ACC\n", line);
        return 0;
    }
    printf("%d: NOT received ACC\n", line);
    return -1;
}


// TCP 
//
//
//
//

ssize_t tcp_sender(int sk, char* buf, size_t size)
{
    ssize_t ret = 0, try = 0;
    if (buf == NULL) {
        return -1;
    }
    ret = send(sk, buf, size, 0);
    if (ret != size && ret != -1) {
        try = tcp_sender(sk, buf + ret, size - ret);
        if (try == -1 || try + ret != size) {
            return -1;
        }
    }

    return 0;
}


int tcp_receiver(int sk, char* buf, size_t size)
{
    ssize_t recd = 0, ret = 0;
    do {
        ret = recv(sk, buf + recd, size - recd, 0);
        // fprintf(stderr, "RECEIVER: got %zd on return\n", ret);
        if (ret <= 0) {
            // perror("RECEIVER: strange return value");
            break;
        }
        recd += ret;
    } while (recd != size);

    if (recd == size){
        // fprintf(stderr, "RECEIVER: got whole package\n");
        return 0;
    }
    // fprintf(stderr, "RECEIVER: got %zd, needed %zu\n", recd, size);
    return -1;
}

int __tcp_ssender(int sk, char* buf, size_t size, int line)
{
    int ret = 0;
    ssize_t sret = 0;
    if ((sret = tcp_sender(sk, buf, size)) != 0) {
        printf("[%d]SMART SENDER: got %zd return value, expected %zu\n", line, sret, size);
        return -1;
    }
    ret = tcp_racc(sk);
    if (ret != 0) {
        printf("[%d]SMART SENDER: didn't get ACC\n", line);
        return -1;
    }
    fprintf(stderr, "[%d]Sent %zu bytes\n", line, size);
    return 0;
}


int __tcp_sreceiver(int sk, char* buf, size_t size, int line)
{
    int ret = 0;
//    fprintf(stderr, "[%d]SMART RECEIVER: expecting %zu bytes\n", line, size);
    if (tcp_receiver(sk, buf, size) != 0) {
        fprintf(stderr, "[%d]SMART RECEIVER: failed to receive\n", line);
        return -1;
    }
    ret = tcp_sacc(sk);
    if (ret != 0) {
        fprintf(stderr, "[%d]SMART RECEIVER: didn't get ACC\n", line);
        return -1;
    }
    fprintf(stderr, "[%d]Received %zu bytes\n", line, size);
    return 0;
}


int socket_snd_rcv_timeout(int sk, int rcv, int snd)
{
    struct timeval rcv_timeout = {
                .tv_sec  = rcv,
                .tv_usec = 0
    };
    struct timeval snd_timeout = {
                .tv_sec  = snd,
                .tv_usec = 0
    };

    if (rcv >= 0 && setsockopt(sk, SOL_SOCKET, SO_RCVTIMEO, &rcv_timeout,
                                                    sizeof(rcv_timeout))== -1){
        print_error(CT_SETSOCK_FAIL);
        return -1;    
    }
    if (snd >= 0 && setsockopt(sk, SOL_SOCKET, SO_SNDTIMEO, &snd_timeout,
                                                    sizeof(snd_timeout))== -1){
        print_error(CT_SETSOCK_FAIL);
        return -1;   
    }

    return 0;
}

int set_default_timeouts(int sk) {
    return socket_snd_rcv_timeout(sk, RCV_TMOUT_SEC, SND_TMOUT_SEC);
}


int tcp_sacc(int sk)
{
    ssize_t  ret = 0;
    ret = tcp_sender(sk, (char*)&ACC_PACK, sizeof(ACC_PACK));
    if (ret != 0)
        return -1;
 //   fprintf(stderr, "Sent acc\n");
    return 0;
}

int tcp_racc(int sk)
{
    uint64_t acc_buf = 0;
    if (tcp_receiver(sk,   (char*)&acc_buf, sizeof(acc_buf)) != 0 
        ||
        acc_buf != ACC_PACK)
        return -1;
//    fprintf(stderr, "Received acc\n");
    return 0;
}

void thread_sigusr1_handler(int sigid)
{
    pthread_exit(NULL);
}

int thread_sigusr1_set()
{
    struct sigaction term_act;
    int cond = 0;
    sigset_t mask;
    sigemptyset(&mask);
    memset(&term_act, 0, sizeof(term_act));
    term_act.sa_handler = thread_sigusr1_handler;
    term_act.sa_mask    = mask;
    cond = sigaction(SIGUSR1, &term_act, NULL);
    return cond;
}
