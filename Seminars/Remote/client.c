#include "iv_remote.h"

#define IP_ARR_STEP 10


int getmyip(struct in_addr* to_save)
{
    int fd;
    struct ifreq ifr;
     
    char iface[] = "eth0";
     
    fd = socket(AF_INET, SOCK_DGRAM, 0);

    if (fd == -1)
        return -1;
    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name , iface , IFNAMSIZ - 1);
    ioctl(fd, SIOCGIFADDR, &ifr);
    close(fd);
 
    *to_save = ( (struct sockaddr_in *)&ifr.ifr_addr )->sin_addr;
    return 0;
}

int configure_broadcast() {
        int sk = socket(AF_INET, SOCK_DGRAM, 0);
        int broadcast_enable = 1;
        int is_reuse = 1;
        int cond = 0;

        if (sk == -1) {
                print_error(CT_GETSOCK_FAIL);
                return -1;
        }

        cond = setsockopt(sk, 
                          SOL_SOCKET, 
                          SO_BROADCAST, 
                          &broadcast_enable,
                          sizeof(broadcast_enable));
        if (cond == -1) {
                print_error(CT_SETSOCK_FAIL);
                return -1;
        }

        cond = setsockopt(sk,
                          SOL_SOCKET,
                          SO_REUSEADDR,
                          &is_reuse,
                          sizeof(is_reuse));
        if (cond == -1) {
                print_error(CT_SETSOCK_FAIL);
                return -1;
        }
        return sk;
}

int configure_accepting()
{
        int sk = socket(AF_INET, SOCK_DGRAM, 0);
        int is_reuse = 1;
        int cond = 0;

         if (sk == -1) {
                print_error(CT_GETSOCK_FAIL);
                return -1;
        }

        cond = setsockopt(sk,
                          SOL_SOCKET,
                          SO_REUSEADDR,
                          &is_reuse,
                          sizeof(is_reuse));
        if (cond == -1) {
                print_error(CT_SETSOCK_FAIL);
                return -1;
        }
        return sk;
}

int discover(struct in_addr** array_tosave, int* num_tosave)
{
        int cond = 0, ips_got = 0, sk = 0, sk_acc = 0;
        unsigned rcv_addr_len = 0; 
        char* request = NULL;
        struct in_addr* arr = NULL;
        struct in_addr  my_ip = {};
        struct sockaddr_in rcv_addr, addr;

        addr.sin_family = AF_INET;
        addr.sin_port   = htons(HANDSHAKE_PORT);
        inet_pton(AF_INET, "255.255.255.255", &addr.sin_addr);

        rcv_addr.sin_family       = AF_INET;
        rcv_addr.sin_addr.s_addr  = htonl(INADDR_ANY);
        rcv_addr.sin_port         = htons(HANDSHAKE_PORT);
        
        sk      = configure_broadcast();

        if (sk == -1) {
            print_error(CT_GETSOCK_FAIL);
            goto fail;
        }

        request = (char*) calloc(16, sizeof(char));
        if (request == NULL) {
            print_error(CT_ALLOC_FAIL);
            goto fail;
        }

        cond = getmyip(&my_ip);
        if (cond == -1) {
            print_error(CT_MYIP_FAIL);
            goto fail;
        }

        strncpy(request, inet_ntoa(my_ip), 16);

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

        close(sk);

        sk_acc  = configure_accepting();
        if (sk_acc == -1) {
            print_error(CT_GETSOCK_FAIL);
            goto fail;
        }

        cond = bind(sk_acc, (struct sockaddr*)&rcv_addr, sizeof(rcv_addr));
        if (cond == -1) {
            print_error(CT_BIND_FAIL);
            goto fail;
        }
        sleep(5);

        
        arr = (struct in_addr*) calloc(IP_ARR_STEP, sizeof(struct in_addr));
        if (cond == -1) {
                print_error(CT_ALLOC_FAIL);
                goto fail;
        }

        rcv_addr_len = sizeof(struct sockaddr_in);
        while ((cond = recvfrom(sk_acc, 
                        request, 
                        16, 
                        MSG_DONTWAIT,
                        (struct sockaddr*)&rcv_addr,
                        &rcv_addr_len)) != -1) 
        {
                printf("Recvfrom invoked, cond = %d\n", cond);
                if (ips_got > 0 && ips_got % IP_ARR_STEP == 0) {
                        arr = realloc(arr, sizeof(struct in_addr)*
                                                 (ips_got + IP_ARR_STEP));
                        if (arr == NULL) {
                                print_error(CT_ALLOC_FAIL);
                                goto fail;
                        }
                }
                printf("got %s\n", inet_ntoa(rcv_addr.sin_addr));
                arr[ips_got] = rcv_addr.sin_addr;
                ips_got++;
        }

        if (errno != EAGAIN && errno != EWOULDBLOCK) {
                print_error(CT_RECV_FAIL);
                goto fail;
        }

        printf("ips_got = %d\n", ips_got);
        *num_tosave = ips_got;
        *array_tosave = arr;

        close(sk);
        close(sk_acc);
        free(request);
        return 0;

fail:
        close(sk);
        close(sk_acc);
        free(arr);
        free(request);
        return -1;
}

int client(int argc, char const *argv[])
{
        int ips = 0, i = 0;
        struct in_addr* ips_array = NULL;
        int cond = 0;

        cond = discover(&ips_array, &ips);

        printf("ips = %d\ncond = %d\n", ips, cond);

        for (i = 0; i < ips; ++i)
                printf("%s\n", inet_ntoa(ips_array[i]));
        return 0;
}