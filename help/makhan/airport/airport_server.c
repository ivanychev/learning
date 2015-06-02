#include "airport_header.h"

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
        // print_error(CT_SETSOCK_FAIL);
        return -1;    
    }
    if (snd >= 0 && setsockopt(sk, SOL_SOCKET, SO_SNDTIMEO, &snd_timeout,
                                                    sizeof(snd_timeout))== -1){
        // print_error(CT_SETSOCK_FAIL);
        return -1;   
    }

    return 0;
}

int set_default_timeouts(int sk) {
    return socket_snd_rcv_timeout(sk, RCV_TMOUT_SEC, SND_TMOUT_SEC);
}

int get_case(FILE* fd, Case* to_save)
{
        char type = 0, temp = 0;
        int ret = 0;
        uint32_t day  = 0;
        uint32_t hour = 0;
        uint32_t min  = 0;

        ret = fscanf(fd, "%c%c %"PRIu32" %02"PRIu32":%02"PRIu32"", 
                &temp, &type, &day, &hour, &min);
        if (ret != 5) {
                printf("Failed to read current case, scanf returned %d\n", ret);
                return -1;
        }

        switch (type) {
        case 't':
                to_save->type = TAKEOFF;
                break;
        case 'l':
                to_save->type = LANDING;
                break;
        default:
                printf("Got wrong character of type, expected \"t\" or \"l\"\n");
                return -1;
        }

        to_save->day = day;
        to_save->min = min;
        to_save->hour= hour;
        return 0;
}

Case* get_cases(FILE* fd, int* num_tosave) {
        uint32_t num = 0, i = 0;
        int ret = 0;
        Case* arr = 0;

        ret = fscanf(fd, "%"PRIu32"", &num);
        if (ret != 1) {
                printf("Failed to get number of cases\n");
                return NULL;
        }
        printf("Expecting %"PRIu32" cases\n", num);

        arr = (Case*)calloc(num, sizeof(Case));
        if (arr == NULL) {
                printf("Failed to allocate memory\n");
                return NULL;
        }

        for (i = 0; i < num; ++i) {
                ret = get_case(fd, &(arr[i]));
                arr[i].index = (uint32_t)i;
                if (ret == -1) {
                        printf("Failed to read %d'th case\n", i);
                        free(arr);
                        return NULL;
                }
        }

        *num_tosave = num;
        return arr;
}

Case* get_args(int argc, char const *argv[], int* num_tosave)
{
        const char* path = NULL;
        if (argc != 2) {
                printf("Wrong number of arguments\n"
                       "One argument is path to the file with cases\n");
                return NULL;
        }
        path = argv[1];
        FILE* fd = fopen(path, "r");
        if (fd == NULL) {
                printf("Failed to open file\n");
                return NULL;
        }

        Case* cases = get_cases(fd, num_tosave);
        return cases;
}

void print_case(Case* cur_case)
{
        printf("%s on day %"PRIu32", time %02"PRIu32":%02"PRIu32"\n", 
                        (cur_case->type == LANDING)? "Landing":"Takeoff", 
                         cur_case->day,
                         cur_case->hour,
                         cur_case->min);
}

void print_cases(Case* arr, int size)
{
        int i = 0;
        for (i = 0; i < size; ++i) 
                print_case(&(arr[i]));
}

int get_msgqueue(int ips) {
     int msgqueue = 0;
    if ((msgqueue = msgget(0, IPC_PRIVATE | 0660)) == -1) {
        printf("Failed to get message queue\n");
        return -1;
    }
    return msgqueue;
}



int fill_tasks(int msgid, Case* arr, int num) 
{
    int i = 0;
    int cond = 0;
    task temp = {.type = 1};
    for (i = 0; i < num; ++i) {
        temp.task = arr[i];
        cond = msgsnd(msgid, &temp, sizeof(temp.task), IPC_NOWAIT);
        if (cond == -1) {
                printf("Failed to send message\n");
            return -1;
        }
        // printf("Message sent\n");
    }
    return 0;
}

int case_compare(const void* arg1, const void* arg2)
{
        Case* case1 = (Case*)arg1;
        Case* case2 = (Case*)arg2;

        if (case1->day - case2->day != 0)
                return (case1->day - case2->day);
        if (case1->hour - case2->hour != 0)
                return (case1->day - case2->day);
        if (case1->min  - case2->min  != 0)
                return (case1->min - case2->min);
        return 0;
}

void sort_tasks(Case* arr, int num)
{
        qsort(arr, num, sizeof(Case), case_compare);
}




int get_listen_socket(int* sk_tosave)
{
    struct sockaddr_in addr = {};
    int sk = 0, cond = 0, is_reuse = 1;
    addr.sin_family         = AF_INET;
    addr.sin_port           = htons(PORT);
    addr.sin_addr.s_addr    = htonl(INADDR_ANY);

    sk = socket(PF_INET, SOCK_STREAM, 0);
    if (sk == -1)
            goto fail;
    if (setsockopt(sk,
                      SOL_SOCKET,
                      SO_REUSEADDR,
                      &is_reuse,
                      sizeof(is_reuse)) == -1)
        goto fail;
    cond = bind(sk, (struct sockaddr*)&addr, sizeof(addr));
    if (cond == -1)
            goto fail;
    if (cond == -1) {
                // print_error(SV_SETSOCK_FAIL);
                goto fail;
        }
    cond = listen(sk, SOMAXCONN);
    if (cond == -1) {
        // print_error(SV_SETSOCK_FAIL);
        goto fail;
    }
    *sk_tosave = sk;
    return 0;
fail:
    if (sk > 0)
        close(sk);
    return -1;
}

int get_client_socket(int sk_listen, struct sockaddr_in* addr)
{
    int client = 0, cond = 0, is_reuse = 1;
    uint32_t size = sizeof(addr);

    client = accept(sk_listen, (struct sockaddr*)addr, &size);
    if (client <= 0) {
        // print_error(SV_ACCEPT_FAIL);
        goto fail;
    }

    cond = setsockopt(client,
                      SOL_SOCKET,
                      SO_REUSEADDR,
                      &is_reuse,
                      sizeof(is_reuse));
    if (cond == -1)
        goto fail;
    if (set_default_timeouts(client) != 0)
        goto fail;
        printf("Connected client!\n");
    return client;
fail:
    if (client > 0)
    close(client);
    return -1; 
}

void* configure_routine(void* arg)
{
        configure_meta* meta = (configure_meta*) arg;
        int sk    = meta->sk;
        int msgid = meta->msgid;
        int32_t index = meta->index;
        // printf("%d msgid, %"PRId32"'th configure started\n", meta->msgid, meta->index);
        task cur_task;
        uint32_t response = 0;

        while (msgrcv(msgid, &cur_task, sizeof(cur_task.task), 0, IPC_NOWAIT) != -1)
        {
                send(sk, &(cur_task.task), sizeof(cur_task.task), 0); //check
                recv(sk, &response, sizeof(response), 0);
        }
        perror("");
        cur_task.task.index = -1;
        send(sk, &(cur_task.task), sizeof(cur_task.task), 0);
        printf("%"PRId32"'th configure finished\n", index);
        return NULL;
}

int main(int argc, char const *argv[])
{
        Case* cases = NULL;
        int num = 0, listen_sk = 0, ret = 0, client1 = 0, client2 = 0, msgid = 0,
        computers = 0, i = 0;
        int* sks = NULL;
        struct sockaddr_in* addrs = NULL;
        // struct sockaddr_in first_addr  = {0};
        // struct sockaddr_in second_addr = {0};
        // configure_meta first_meta;
        // configure_meta second_meta;
        configure_meta* metas;
        // pthread_t first_configure;
        // pthread_t second_configure;
        pthread_t* threads = NULL;

        printf("Please, type number of computers\n");
        scanf("%d", &computers);
        sks = (int*)calloc(computers, sizeof(int));
        addrs = (struct sockaddr_in*)calloc(computers, sizeof(struct sockaddr_in));
        metas = (configure_meta*)calloc(computers, sizeof(configure_meta));
        threads = (pthread_t*)calloc(computers, sizeof(pthread_t));

        cases = get_args(argc, argv, &num);
        sort_tasks(cases, num);
        if (cases != NULL) 
                print_cases(cases, num);
        else {
                printf("Failed to get args, terminating...\n");
                return 0;
        }
        msgid = get_msgqueue(num);
        if (msgid == -1) {
                printf("Failed to get message queue\n");
                free(cases);
                return 0;
        }

        ret = fill_tasks(msgid, cases, num);
        if (ret == -1) {
                printf("Failed to fill message queue with tasks\n");
                msgctl(msgid, IPC_RMID, NULL);
                free(cases);
                return 0;
        }

        ret = get_listen_socket(&listen_sk);
        if (ret == -1) {
                printf("Failed to get listen socket\n");
                msgctl(msgid, IPC_RMID, NULL);
                free(cases);
                return 0;
        }

        for (i = 0; i < computers; ++i) {
                sks[i] = get_client_socket(listen_sk, &(addrs[i]));
                if (sks[i] == -1) {
                        printf("Failed to connect to the first runaway\n");
                        free(cases);
                        msgctl(msgid, IPC_RMID, NULL);
                        close(listen_sk);
                        return 0;
                }
                metas[i].sk = sks[i];
                metas[i].msgid = msgid;
                metas[i].index = i;
        }

        for (i = 0; i < computers; ++i)
                pthread_create(&(threads[i]), NULL, configure_routine, &(metas[i]));
        for (i = 0; i < computers; ++i) 
                pthread_join(threads[i], NULL);



        // first_meta.sk      = client1;
        // first_meta.msgid   = msgid;
        // first_meta.index   = 1;
        // second_meta.sk     = client2;
        // second_meta.msgid  = msgid;
        // second_meta.index  = 2;
        // pthread_create(&first_configure,  NULL, configure_routine, &first_meta);
        // pthread_create(&second_configure, NULL, configure_routine, &second_meta);
        // pthread_join(first_configure , NULL);
        // pthread_join(second_configure, NULL);
        return 0;
}




