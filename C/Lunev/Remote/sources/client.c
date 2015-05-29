#include "../include/iv_remote.h"
#include "../include/iv_standard.h"

#define IP_ARR_STEP 10

void thread_sigusr1_handler(int sigid);

int thread_sigusr1_set();



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
        struct in_addr* arr     = NULL;
        struct in_addr* new_arr = NULL;
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
        sleep(2);

        
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
                fprintf(stderr, "Recvfrom invoked, cond = %d\n", cond);
                if (ips_got > 0 && ips_got % IP_ARR_STEP == 0) {
                        new_arr = realloc(arr, sizeof(struct in_addr)*
                                                 (ips_got + IP_ARR_STEP));
                        if (new_arr == NULL) {
                                print_error(CT_ALLOC_FAIL);
                                goto fail;
                        }
                        arr = new_arr;
                }
                fprintf(stderr, "got %s\n", inet_ntoa(rcv_addr.sin_addr));
                arr[ips_got] = rcv_addr.sin_addr;
                ips_got++;
        }

        if (errno != EAGAIN && errno != EWOULDBLOCK) {
                print_error(CT_RECV_FAIL);
                goto fail;
        }

        fprintf(stderr, "ips_got = %d\n", ips_got);
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
            fprintf(stderr, "%s\n", inet_ntoa(ips_array[i]));
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
    fprintf(stderr, "Network scan completed.\n");

    if (get_matrix(argv[2], &current) == -1) {
        print_error(CT_MATR_READ_FAIL);
        goto fail;
    }
    fprintf(stderr, "Matrix has been read");

    if (get_det(&current, &result, ips, ips_array) == -1) {
        print_error(CT_DET_CALC_FAIL);
        goto fail;
    }   

    fprintf(stderr, "Determinant is %lg\n", result); 

    free(ips_array);
    matrix_kill(&current);
    return 0;

fail:
    
    free(ips_array);
    matrix_kill(&current);
    return -1;
}


int get_ips_semaphore(int ips, uint32_t size) {
    union semun set;
    int sem = 0;

    if ((sem = semget(0, 3, IPC_PRIVATE | 0660)) == -1) {
        print_error(CT_SEM_FAIL); //~!!!!!!!!!!!!!!!!!!
        goto fail;
    }

    set.val = ips;
    semctl(sem, 0, SETVAL, set);
    set.val = size;
    semctl(sem, 1, SETVAL, set);
    set.val = 0;
    semctl(sem, 2, SETVAL, set);

    return sem;
fail:
    semctl(sem, 0, IPC_RMID);
    unlink(TEMP_FILE);
    return -1;
}


int get_ips_msgqueue(int ips) {
     int msgqueue = 0;
    if ((msgqueue = msgget(0, IPC_PRIVATE | 0660)) == -1) {
        print_error(CT_MSG_FAIL);
        return -1;
    }
    return msgqueue;
}


ssize_t udp_sender(int sk, struct sockaddr_in* addr, const void* ptr, size_t size)
{
    int attempt  = 0;
    ssize_t sent = 0;

    while (attempt < SND_ATTEMPTS) {
        sent = sendto(sk, ptr, size, 0, (struct sockaddr*)addr, sizeof(*addr));
        if (sent == -1)
            return -1;
        if (rcv_acc(sk) == 0)
            return sent;
        attempt += 1;
    }
    return -1;
}


int talker_send_matrix(int sk, const matrix* cur)
{
    int ret = 0;

    ret = tcp_ssend(sk, (char*)cur, sizeof(*cur));
    if (ret != 0) {
        print_error(CT_MATR_SEND_FAIL);
        return -1;
    }

    ret = tcp_ssend(sk, cur->data, sizeof(double) * cur->size * cur->size);
    if (ret != 0) {
        print_error(CT_MATR_SEND_FAIL);
        return -1;
    }
    DP(3);
    return 0;
}

int talker_get_socket() 
{
    int sk = 0, is_reuse = 1;

    sk = socket(PF_INET, SOCK_STREAM, 0);
    if (sk == -1) {
        print_error(CT_GETSOCK_FAIL);
        return -1;
    }

    if (setsockopt(sk, 
                   SOL_SOCKET, 
                   SO_REUSEADDR, 
                   &is_reuse, sizeof(is_reuse)) == -1) {
        print_error(CT_SETSOCK_FAIL);
        goto fail;
    }

    if (set_default_timeouts(sk) != 0) {
        print_error(CT_SETSOCK_FAIL);
        goto fail;        
    }

    return sk;
fail:
    close(sk);
    return -1;
}


int do_task(int sk, uint32_t minor, double* res, int index)
{
    sv_answer temp = {.status = SV_ANSWER_WAIT};
    if (tcp_ssend(sk, (char*)&minor, sizeof(minor)) == -1){
        return -1;
    }
    fprintf(stderr, "{%d} Sent task to server\n", index);
    while (temp.status == SV_ANSWER_WAIT) {
        if (tcp_srecv(sk, (char*)&temp, sizeof(temp)) == -1) {
            print_error(NEUTRAL_ERROR);
            return -1;
        }
        fprintf(stderr, "{%d} Wait packet received\n", index);
        if (temp.status == SV_ANSWER_ERR) {
            print_error(NEUTRAL_ERROR);
            return -1;
        }
    }
    fprintf(stderr, "{%d} Result received\n", index);
    *res = temp.val;
    return 0;
}

int last_thread(ct_thread_meta* meta)
{
    short  ips = (short)meta->ips;
    struct sembuf op[2]   = {{2, -ips + 1, IPC_NOWAIT}, {2,  ips - 1, IPC_NOWAIT}};
    printf("Last thread see semaphore %d\n", iv_getsemval(meta->sem, 2));
    if (semop(meta->sem, op, 2) == -1 && errno == EAGAIN) {
        return 0;
    }
    return 1;
}

void* talker_tcp_routine(void* arg)
{
    struct sockaddr_in addr = {};
    int sk = 0,  cond = 0;
    double res   = 0;
    ssize_t ret  = 0;
    struct sembuf decr = {
        .sem_num =  0,
        .sem_op  = -1,
        .sem_flg =  0
    };
    struct sembuf success[] = {{0, 1, 0}, {1, -1, 0}};
    struct sembuf if_fail = {2, 1, 0};
    ct_task task            = {.mtype  = 1};
    ct_thread_meta* meta    = (ct_thread_meta*) arg;
    addr.sin_addr           = meta->server;
    addr.sin_family         = AF_INET;
    addr.sin_port           = htons(PORT);
    int msgid               = meta -> msgid;
    if (thread_sigusr1_set() == -1) {
        print_error(NEUTRAL_ERROR);
        goto fail;
    }

//    int msgid = meta->msgid;

    sk = talker_get_socket();
    if (sk == -1) {
        print_error(CT_GETSOCK_FAIL);
        goto fail;
    }
    fprintf(stderr, "{%d} Created socket\n", meta->num);

    cond = connect(sk ,(struct sockaddr*)&addr, sizeof(addr));
    if (cond == -1) {
        print_error(CT_CONNECT_FAIL);
        goto fail;
    }
    fprintf(stderr, "{%d} Connected to server\n", meta->num);
    meta->sk = sk;

    cond = talker_send_matrix(sk, meta->cur);
    if (cond == -1) {
        print_error(CT_THR_SEND_MATR_FAIL);
        goto fail;
    }
    fprintf(stderr, "{%d} Sent matrix to server\n", meta->num);
    while (1) {
        if (semop(meta->sem, &decr, 1) == -1) {
            print_error(NEUTRAL_ERROR);
            goto terrible_fail;
        };
        fprintf(stderr, "{%d} Starting new task\n", meta->num);
        ret = msgrcv(msgid, &task, sizeof(task.minor), 1, 0);
        if (ret != sizeof(task.minor)) {
            fprintf(stderr, 
                    "{%d}! ret = %zd, expected = %zd\n",meta->num, ret, 
                                                               sizeof(ct_task));
            print_error(NEUTRAL_ERROR);
            goto fail;
        }
        fprintf(stderr, "{%d} Received task %u\n", meta->num, task.minor);
        if (do_task(sk, task.minor, &res, meta->num) == -1) {
            print_error(NEUTRAL_ERROR);
            goto task_fail;
        }
        fprintf(stderr, "{%d} Completed task %u\n", meta->num, task.minor);
        meta->result += res;
        fprintf(stderr, "Before success semaphores: %d %d\n", iv_getsemval(meta->sem, 0),
                                                     iv_getsemval(meta->sem, 1));
        if (semop(meta->sem, success, 2) == -1) {
            // DP(1);
            print_error(NEUTRAL_ERROR);
            goto terrible_fail;
        }
        // DP(1);
    }

    return NULL;
fail:
    if (last_thread(meta)) {
        printf("LAST THREAD!");
        goto terrible_fail;
    }
    fprintf(stderr, 
           "{%d} Thread is terminating...\n"
           "{%d} Connection lost or not established\n"
           "{%d} Connected IP: %s\n"
           "{%d} No tasks lost\n", meta->num, meta->num, meta->num, 
                                            inet_ntoa(addr.sin_addr), meta->num);
    meta->finish_cond = -1;
    if (sk > 0) {
        close(sk);
        sk = 0;
    }
    semop(meta->sem, &if_fail, 1);
    DP(2);  
    return NULL;
task_fail:
    ret = msgsnd(msgid, &task, sizeof(uint32_t), 0);
    if (ret == 0)
        goto fail;
terrible_fail:
    fprintf(stderr, 
           "{%d} Program is terminating...\n"
           "{%d} Unsolvable issue occured\n"
           "{%d} Connected IP: %s\n"
           "{%d} Semaphores broken or tasks are lost\n", meta->num, meta->num, meta->num, 
                                            inet_ntoa(addr.sin_addr), meta->num);
    if (sk > 0)
        close(sk);
    for (cond = 0; cond < meta->ips; ++cond) 
        meta->meta_arr[cond].finish_cond = -1;
    semctl(meta->sem, 0, SETVAL, 0);
    semctl(meta->sem, 1, SETVAL, 0);
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
        cond = msgsnd(msgid, &task, sizeof(task.minor), IPC_NOWAIT);
        if (cond == -1)
            return -1;
    }
    return 0;
}

int send_fin(int sk)
{
    uint32_t fin = FIN;
    return tcp_ssend(sk, (char*)&fin, sizeof(fin));
}

int get_det(const matrix* current, double* res_tosave, int ips, struct in_addr* ips_array)
{
    int cond    = 0,
        failed  = 0,
        i       = 0,
        sem     = 0,
        msgid   = 0;
    ct_thread_meta* meta_arr = NULL;
    struct sembuf zero_wait[] = {{0, 0, 0}, {1, 0, 0}};
    if (current == NULL || res_tosave == NULL || ips_array == NULL) {
        print_error(CT_INVL_ARG);
        return -1;
    }

    if (ips == 0) {
        print_error(CT_EMPTY_NET);
        return -1;
    }

    if ((sem = get_ips_semaphore(ips, current->size)) == -1) 
        return -1;              //! Error message printed
    fprintf(stderr, "Received ips semaphores\n");
    if ((msgid = get_ips_msgqueue(ips)) == -1)
        goto fail;              //! Error message printed
    fprintf(stderr, "Received thread shared message queue\n");
    meta_arr = (ct_thread_meta*)calloc(ips, sizeof(ct_thread_meta));
    if (meta_arr == NULL) {
        print_error(CT_ALLOC_FAIL);
        goto fail;
    }

    if ((fill_tasks(msgid, current)) == -1) {
        print_error(CT_FILL_FAIL);
        goto fail;
    }
    fprintf(stderr, "Tasks are loaded to the queue\n");

    for (i = 0; i < ips; ++i) {
        meta_arr[i].msgid  = msgid;
        meta_arr[i].ips    = ips;
        meta_arr[i].sem    = sem;
        meta_arr[i].cur    = current;
        meta_arr[i].server = ips_array[i];
        meta_arr[i].num    = i;
        meta_arr[i].meta_arr = meta_arr;
        cond = pthread_create(&meta_arr[i].id, NULL, talker_tcp_routine, 
                                                                &meta_arr[i]);
        pthread_detach(meta_arr[i].id);
        fprintf(stderr, "Created %d'th thread\n", i);
        if (cond == -1) {
            print_error(CT_THREAD_CREAT_FAIL);
            goto fail;
        }
    }
    semop(sem, zero_wait, 2);
    fprintf(stderr, "All threads finished their work\n");
    cond = 1;
    for (i = 0; i < ips; ++i) {
        if (meta_arr[i].sk > 0) {
            send_fin(meta_arr[i].sk);
            close(meta_arr[i].sk);
            fprintf(stderr, "%d'th thread has active socket. Closed now\n", i);
        }
        failed += (meta_arr[i].finish_cond == -1)? 1: 0;
        if (meta_arr[i].finish_cond == -1)
            fprintf(stderr, "%d'th thread finished by error\n", i);
        else {
            pthread_cancel(meta_arr[i].id);
            fprintf(stderr, "%d'th thread finished normally\n", i);
        }
    }
    if (ips == failed) {
        print_error(CT_ALL_THREADS_FAILED);
        goto fail;
    }
    fprintf(stderr, "%d threads succeeded\n", ips - failed);
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
    if (sem > 0)
        semctl(sem, 0, IPC_RMID);
    if (msgid > 0)
        msgctl(msgid, IPC_RMID, NULL);
    return -1;
}
