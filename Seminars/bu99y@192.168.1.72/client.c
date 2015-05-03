#include "iv_remote.h"

#define IP_ARR_STEP 10


int discover(struct in_addr** array_tosave, int* num_tosave)
{
        int cond = 0;
        unsigned rcv_addr_len = 0; 
        int sk = 0;
        int broadcast_enable = 1;
        int ips_got = 0;
        int is_reuse = 1;
        struct in_addr* arr = NULL;
        struct sockaddr_in rcv_addr, addr = {
                .sin_family = AF_INET
        };

        char* request = "hello";
        addr.sin_port        = htons(HANDSHAKE_PORT);
        
        inet_pton(AF_INET, "255.255.255.255", &addr.sin_addr);
        sk = socket(AF_INET, SOCK_DGRAM, 0);
        if (sk == -1) {
                print_error(CT_GETSOCK_FAIL);
                goto fail;
        }

        cond = setsockopt(sk, 
                          SOL_SOCKET, 
                          SO_BROADCAST, 
                          &broadcast_enable,
                          sizeof(broadcast_enable));
        if (cond == -1) {
                print_error(CT_SETSOCK_FAIL);
                goto fail;
        }

        cond = setsockopt(sk,
                          SOL_SOCKET,
                          SO_REUSEADDR,
                          &is_reuse,
                          sizeof(is_reuse));
        if (cond == -1) {
                print_error(CT_SETSOCK_FAIL);
                goto fail;
        }

        cond = sendto(sk, 
                      request, 
                      strlen(request), 
                      0, 
                      (struct sockaddr*)&addr,
                      sizeof(addr));
        if (cond == -1) {
                print_error(CT_SEND_FAIL);
                goto fail;
        }

        sleep(2);

        
        arr = (struct in_addr*) calloc(IP_ARR_STEP, sizeof(struct in_addr));
        if (cond == -1) {
                print_error(CT_ALLOC_FAIL);
                goto fail;
        }

        while (recvfrom(sk, 
                        request, 
                        strlen(request), 
                        MSG_DONTWAIT,
                        (struct sockaddr*)&rcv_addr,
                        &rcv_addr_len) != -1) 
        {
                if (ips_got > 0 && ips_got % IP_ARR_STEP == 0) {
                        arr = realloc(arr, sizeof(struct in_addr)*
                                                 (ips_got + IP_ARR_STEP));
                        if (arr == NULL) {
                                print_error(CT_ALLOC_FAIL);
                                goto fail;
                        }
                }
                arr[ips_got] = rcv_addr.sin_addr;
                ips_got++;
        }

        if (errno != EAGAIN && errno != EWOULDBLOCK) {
                print_error(CT_RECV_FAIL);
                goto fail;
        }

        *num_tosave = ips_got;
        *array_tosave = arr;

        close(sk);
        return 0;

fail:
        close(sk);
        free(arr);
        return -1;
}

int client(int argc, char const *argv[])
{
        int ips = 0, i = 0;
        struct in_addr* ips_array = NULL;
        int cond = 0;

        cond = discover(&ips_array, &ips);

        for (i = 0; i < ips; ++i)
                printf("%s\n", inet_ntoa(ips_array[i]));
        return 0;
}