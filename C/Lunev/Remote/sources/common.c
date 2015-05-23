#include "stdio.h"
#include "../include/iv_remote.h"

char const* errors_msgs[] = {
        "",
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

        ""
        
};

// int is_error(int errnum)
// {
//         if (FIRST_ERROR <= errnum && errnum <= LAST_ERROR){
//                 return 1;
//         }
//         return 0;
// }

void __print_error(int line, const char* filename, int errnum) 
{
       static char buf[1024];
       if (FIRST_ERROR <= errnum && errnum<= LAST_ERROR){
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
