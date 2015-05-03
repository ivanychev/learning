#include "iv_remote.h"

int iv_getlong(long* save, const char* str);

int get_args(int argc, char const *argv[])
{
        long res = 0;
        int cond = 0;
        if (argc != 2)
                return -1;
        
        cond = iv_getlong(&res, argv[2]);

        if (cond != 0) {
                if (strcmp(argv[2], "auto") == 0) 
                        return 0;
                return SV_ARGS_INVALARG;
        }

        if (res >= MAXPROC)
                return SV_ARGS_TOOBIG;
        else if (res <= 0)
                return SV_ARGS_TOOSMALL;
        return (int)res;
}

int get_nthread(int argc, char const *argv[])
{
        int nthread = 0;
        nthread = get_args(argc, argv);
        if (nthread < 0) {
                print_error(nthread);
                return -1;
        }

        if (nthread == 0)
                nthread = sysconf(_SC_NPROCESSORS_ONLN);  //! Getting online 
                                                          //! cores number
        return nthread;

}

int handshake_setsocket(int sk)
{
        const int is_reuse = 1;
        int cond = 0;
        struct timeval timeout = {
                .tv_sec  = HNDSK_TMOUT_SEC,
                .tv_usec = 0
        };
        cond = setsockopt(sk, 
                          SOL_SOCKET, 
                          SO_RCVTIMEO,
                          &timeout,
                          sizeof(timeout));
        if (cond == -1) {
                print_error(SV_SETSOCK_FAIL);
                goto fail;
        }
        cond = setsockopt(sk,
                          SOL_SOCKET,
                          SO_REUSEADDR,
                          &is_reuse,
                          sizeof(is_reuse));
        if (cond == -1) {
                print_error(SV_SETSOCK_FAIL);
                goto fail;
        }
        return 0;
fail:
        return -1;
}

void* handshake(void* arg)
{
        int sk = 0, cond = 0, got = 0;
        char buf[HND_BUFSIZE];
        struct sockaddr_in addr = {
                .sin_family = AF_INET
        };

        struct sockaddr_in clt_addr = {};
        unsigned  clt_add_len = 0;
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        addr.sin_port        = htons(HANDSHAKE_PORT);

        sk = socket(PF_INET, SOCK_DGRAM, 0);
        if (sk == -1) {
                print_error(SV_GETSOCK_FAIL);
                goto fail;
        }
        cond = bind(sk, (struct sockaddr*)&addr, sizeof(addr));
        if (cond == -1) {
                print_error(SV_BIND_FAIL);
                goto fail;
        }
        cond = handshake_setsocket(sk);
        if (cond == -1) {
                print_error(SV_HNDSK_FAIL);
                goto fail;
        }
        while (1) {
                got = recvfrom(sk, 
                                buf, 
                                sizeof(buf), 
                                0,
                                (struct sockaddr*)&clt_addr,
                                &clt_add_len);
                if (got == -1) {
                        print_error(SV_RECV_FAIL);
                        goto fail;
                }
                cond = sendto(sk,
                              buf,
                              got,
                              0,
                              (struct sockaddr*)&clt_addr,
                              clt_add_len);
        }
        fail:
        close(sk);

        return (void*)-1;
}

int handshaker_set()
{
        pthread_t handshaker;
        int cond = 0;

        cond = pthread_create(&handshaker, NULL, handshake, NULL);
        if (cond != 0) {
                print_error(SV_HND_CRTFAIL);
                return -1;
        }

        return 0;
}

int server(int argc, char const *argv[])
{
        int nthread = 0, cond = 0;
        nthread = get_nthread(argc, argv);
        if (nthread == -1)
                goto fail;
        cond = handshaker_set();
        if (cond == -1)
                goto fail;




        fail:
        fprintf(stderr, "Critical server error occured\n");
        return -1;
}