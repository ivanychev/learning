#include "iv_remote.h"

#define IP_ARR_STEP 10


int configure_broadcast() {
        int broadcast_enable = 1;
        int is_reuse = 1;
        int cond = 0;
        int sk = socket(AF_INET, SOCK_DGRAM, 0);
        
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

        request = malloc(50);
        strcpy(request, "Hello, World!");

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
        
//===============================================================
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
                        strlen(request), 
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
        free(request);
        close(sk_acc);
        return 0;

fail:
        close(sk);
        close(sk_acc);
        if (arr)
            free(arr);
        if (request)
            free(request);
        return -1;
}

int scan(int* ips_tosave, struct in_addr** ips_array_tosave) {
    int ips = 0, i = 0;
    struct in_addr* ips_array = NULL;
    int cond = 0;

    cond = discover(&ips_array, &ips);

    if (cond == -1)
        return -1;

//==============================================================================
    printf( "Got %d responds\n"
            "Discover returned %d\n"
            "Printing connected IPs...\n\n", ips, cond);
    for (i = 0; i < ips; ++i)
            printf("%s\n", inet_ntoa(ips_array[i]));
//==============================================================================

    *ips_tosave = ips;
    *ips_array_tosave = ips_array;
    return 0;
}

int client(int argc, char const *argv[])
{
    int ips = 0;
    double result = 0;
    struct in_addr* ips_array = NULL;
    matrix current = {};
    
    if (scan(&ips, &ips_array) == -1) {
        print_error(CT_SCAN_FAIL);
        goto fail;
    }

    if (get_matrix(argv[2], &current) == -1) {
        print_error(CT_MATR_READ_FAIL);
        goto fail;
    }

    if (get_det(&current, &result, ips, ips_array) == -1) {
        print_error(CT_DET_CALC_FAIL);
        goto fail;
    }   

    printf("Determinant is %lg\n", result); 

    free(ips_array);
    matrix_kill(&current);
    return 0;

fail:
    
    free(ips_array);
    matrix_kill(&current);
    return -1;
}


int get_ips_semaphore(int ips) {
    union semun set;
    key_t key;
    int sem = 0, temp_fd = 0;
    if ((temp_fd = creat(TEMP_FILE, O_RDWR)) == -1) {
        print_error(CT_TEMP_CREAT_FAIL);
        return -1;
    }

    if ((key = ftok(TEMP_FILE, 3)) == -1) {
        print_error(CT_FTOK_FAIL);
        goto fail;
    }
    if ((sem = semget(key, ips, IPC_CREAT & 0660)) == -1) {
        print_error(CT_SEM_FAIL); //~!!!!!!!!!!!!!!!!!!
        goto fail;
    }

    set.val = 0;
    semctl(sem, ips, SETVAL, set);

    return sem;
fail:
    semctl(sem, 0, IPC_RMID);
    unlink(TEMP_FILE);
    return -1;
}


int get_ips_msgqueue(int ips) {
     key_t key;
     int msgqueue = 0;
     if ((key = ftok(TEMP_FILE, 1)) == -1) {
        print_error(CT_FTOK_FAIL);
        return -1;
    }
    if ((msgqueue = msgget(key, IPC_CREAT & 0660)) == -1) {
        print_error(CT_MSG_FAIL);
        return -1;
    }
    return msgqueue;
}


int talker_send_matrix(int sk, struct sockaddr_in* addr, const matrix* cur)
{
    ssize_t sent = 0;
    assert(cur);
    sent = sendto(sk, cur, sizeof(matrix), 0, (struct sockaddr*)addr, 
                                                            sizeof(*addr));
    if (sent == -1)
        return -1;
    if (rcv_acc(sk) == -1)
        return -1;
    sent = sendto(sk, cur->data, cur->size * 
                                 cur->size * 
                                 sizeof(double), 0, (struct sockaddr*)addr, 
                                                            sizeof(*addr));
    if (sent == -1)
        return -1;
    if (rcv_acc(sk) == -1)
        return -1;
    return 0;
}

void* talker_routine(void* arg) 
{
    struct sockaddr_in addr= {};
    int sk = 0, is_reuse = 1;
    struct sembuf decr = {
        .sem_num = 0,
        .sem_op  = -1,
        .sem_flg = 0
    };
    ct_thread_meta* meta   = (ct_thread_meta*) arg;
    addr.sin_port          = 0;
    addr.sin_addr          = meta->server;
    addr.sin_family        = SOCK_DGRAM;

    if ((sk = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        print_error(CT_THR_SOCK_CREATE_FAIL);
        goto fail;
    };
    if (setsockopt(sk, 
                   SOL_SOCKET, 
                   SO_REUSEADDR, 
                   &is_reuse, sizeof(is_reuse)) == -1) {
        print_error(CT_SETSOCK_FAIL);
        goto fail;
    }
    if (bind(sk, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        print_error(CT_THR_BIND_FAIL);
        goto fail;
    }



    if (talker_send_matrix(sk, &addr, meta->cur) == -1) {
        print_error(CT_THR_SEND_MATR_FAIL);
        goto fail;
    }


    semop(meta->sem, &decr, 1);
    meta->finish_cond = 0;
    return NULL;
fail:
    semop(meta->sem, &decr, 1);
    meta->finish_cond = -1;
    return NULL;
}

int fill_tasks(int msgid, const matrix* current) 
{
    uint32_t i = 0;
    int cond = 0;
    assert(current);
    ct_task task = {.mtype = 1};
    for (i = 0; i < current ->size; ++i) {
        task.minor = i;
        cond = msgsnd(msgid, &task, sizeof(task), IPC_NOWAIT);
        if (cond == -1)
            return -1;
    }
    return 0;
}

int get_det(const matrix* current, double* res_tosave, int ips, struct in_addr* ips_array)
{
    int cond    = 0,
        failed  = 0,
        i       = 0,
        sem     = 0,
        msgid   = 0;
    ct_thread_meta* meta_arr = NULL;
    struct sembuf zero_wait = {0, 0, 0};
    if (current == NULL || res_tosave == NULL || ips_array == NULL) {
        print_error(CT_INVL_ARG);
        return -1;
    }

    if (ips == 0) {
        print_error(CT_EMPTY_NET);
        return -1;
    }

    if ((sem = get_ips_semaphore(ips)) == -1) 
        return -1;              //! Error message printed
    if ((msgid = get_ips_msgqueue(ips)) == -1)
        goto fail;              //! Error message printed

    meta_arr = (ct_thread_meta*)calloc(ips, sizeof(ct_thread_meta));
    if (meta_arr == NULL) {
        print_error(CT_ALLOC_FAIL);
        goto fail;
    }

    if ((fill_tasks(msgid, current)) == -1) {
        print_error(CT_FILL_FAIL);
        goto fail;
    }

    for (i = 0; i < ips; ++i) {
        meta_arr[i].msgid  = msgid;
        meta_arr[i].sem    = sem;
        meta_arr[i].cur    = current;
        meta_arr[i].server = ips_array[i];
        cond = pthread_create(&meta_arr[i].id, NULL, talker_routine, 
                                                                &meta_arr[i]);
        if (cond == -1) {
            print_error(CT_THREAD_CREAT_FAIL);
            goto fail;
        }
    }
    semop(sem, &zero_wait, 1);
    cond = 1;
    for (i = 0; i < ips; ++i) {
        pthread_join(meta_arr[i].id, NULL);
        failed += (meta_arr[i].finish_cond == -1)? 1: 0;
    }
    if (ips == failed) {
        print_error(CT_ALL_THREADS_FAILED);
        goto fail;
    }
    printf("%d threads succeeded\n", ips - failed);
    for (i = 0; i < ips; ++i)
        *res_tosave += meta_arr[i].result;

    unlink(TEMP_FILE);
    free(meta_arr);
    semctl(sem, 0, IPC_RMID);
    msgctl(msgid, IPC_RMID, NULL);
    return 0;

fail:
    unlink(TEMP_FILE);
    free(meta_arr);
    semctl(sem, 0, IPC_RMID);
    msgctl(msgid, IPC_RMID, NULL);
    return -1;
}
