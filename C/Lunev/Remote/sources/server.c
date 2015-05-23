#include "../include/iv_remote.h"

int iv_getlong(long* save, const char* str);

int get_args(int argc, char const *argv[])
{
        long res = 0;
        int cond = 0;
        if (argc != 3)
                return SV_ARGS_INVALNUM;
        
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
                printf("%d\n", nthread);
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
        struct sockaddr_in addr = {}, clt_addr = {};
        addr.sin_family         = AF_INET;
        addr.sin_addr.s_addr    = htonl(INADDR_ANY);
        addr.sin_port           = htons(HANDSHAKE_PORT);

        unsigned  clt_add_len = sizeof(struct sockaddr_in);

        sk = socket(PF_INET, SOCK_DGRAM, 0);
        if (sk == -1) {
                print_error(SV_GETSOCK_FAIL);
                goto fail;
        }
        cond = handshake_setsocket(sk);
        if (cond == -1) {
                print_error(SV_HNDSK_FAIL);
                goto fail;
        }
        cond = bind(sk, (struct sockaddr*)&addr, sizeof(addr));
        if (cond == -1) {
                print_error(SV_BIND_FAIL);
                goto fail;
        }
        while (1) {
            printf("Handshaker acting...\n");
            got = recvfrom (sk, 
                            buf, 
                            sizeof(buf), 
                            0,
                            (struct sockaddr*)&clt_addr,
                            &clt_add_len);
            if (got == -1) {
                    print_error(SV_RECV_FAIL);
                    goto fail;
            }

            printf("port = %d, addr = %s\n", ntohs(clt_addr.sin_port),
                                        inet_ntoa(clt_addr.sin_addr));
            // inet_aton(buf, &(clt_addr.sin_addr));
            clt_addr.sin_port = htons(HANDSHAKE_PORT);
            

            cond = sendto(sk,
                          buf,
                          got,
                          0,
                          (struct sockaddr*)&clt_addr,
                          clt_add_len);
            printf("Sent %d bytes\n", cond);
            perror("");
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

int get_socket(int* sk_tosave) 
{
    struct sockaddr_in addr = {};
    int sk = 0, cond = 0, is_reuse = 1;
    addr.sin_port        = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_family      = AF_INET;
    struct timeval timeout = {
                .tv_sec  = RCV_TMOUT_SEC,
                .tv_usec = 0
        };
    sk = socket(AF_INET, SOCK_DGRAM, 0);
    if (sk == -1)
        return -1;
    cond = bind(sk, (struct sockaddr*)&addr, sizeof(addr));
    if (cond == -1) 
        return -1;

    cond = setsockopt(sk,
                          SOL_SOCKET,
                          SO_REUSEADDR,
                          &is_reuse,
                          sizeof(is_reuse));
    if (cond == -1) {
            return -1;
    }

    if (setsockopt(sk, SOL_SOCKET, SO_RCVTIMEO, &timeout,sizeof(timeout))== -1){
        print_error(CT_SETSOCK_FAIL);
        return -1;   
    }



    *sk_tosave = sk;
    return 0;
}


int matrix_get(int sk, matrix* cur)             // add verifications
{
    matrix temp = {};
    struct sockaddr_in temp_addr = {};
    unsigned size_addr = sizeof(temp_addr);
    ssize_t cond = 0, data_size = 0, got = 0;
    char* data = NULL;
    char* ptr  = NULL;

    cond = recvfrom(sk, &temp, sizeof(matrix), 0, (struct sockaddr*)&temp_addr, 
                                                                    &size_addr);
    printf("Received matrix struct of size %zd, dimention = %"PRIu32"\n", 
                                                               cond, temp.size);
    if (cond != sizeof(matrix)) {
        print_error(SV_INVAL_MATRIX);
        return -1;
    }

    data_size = temp.size * temp.size * sizeof(double);
    printf("Waiting for %zd data size\n", data_size);
    data = malloc(data_size);
    if (data == NULL) {
        return -1;
    }
    ptr = data;

    if (snd_acc(sk, &temp_addr) == -1)
            return -1;

    while (got != data_size) {
        cond = recvfrom(sk, ptr, MTU, 0, (struct sockaddr*)&temp_addr, 
                                                   &size_addr);
        printf("Received %zd bytes\n", cond);
        if (cond == -1)
            return -1;
        if (snd_acc(sk, &temp_addr) == -1)
            return -1;
        got += cond;
        ptr += cond;
        printf("got = %zd, left %zd\n", got, data_size - got);
    }

    if (rcv_acc(sk) != 0)
        return -1;
    if (snd_acc(sk, &temp_addr) == -1)
            return -1;


    snd_acc(sk, &temp_addr);
    temp.data = data;
    *cur = temp;
    return 0;
}

int server(int argc, char const *argv[])
{
        int nthread = 0, cond = 0, sk = 0;
        matrix cur;
        nthread = get_nthread(argc, argv);
        if (nthread == -1) {
            goto fail;
        }
        printf("%d cores\n", nthread);
        cond = handshaker_set();
        if (cond == -1)
                goto fail;
        cond = get_socket(&sk);
        cond = matrix_get(sk, &cur);
        if (cond == -1) {
            print_error(SV_MATRIX_GET_FAIL);
            return -1;
        }

        print_matrix(&cur);
        return 0;
fail:
        fprintf(stderr, "Critical server error occured\n");
        return -1;
}
