#define _SVID_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <fcntl.h>

struct thread_box
{
    pthread_t id;
    int index;
    int msgid;
};

struct message
{
    long type;
};



void* epic_func (void* number_ptr)
{
    struct thread_box thread_info = *(struct thread_box*)number_ptr;
    struct message received = {0};
    struct message sending = {thread_info.index + 2};


    int cond = msgrcv(  thread_info.msgid, 
                        &received,
                        sizeof(struct message) - sizeof(long),
                        thread_info.index + 1,
                        0);
    if (cond == -1)
    {
        perror("Failed to receive message in thread");
        exit(errno);
    }
    printf ("number of thread = %d\n", thread_info.index);
    cond = msgsnd(  thread_info.msgid,
                    &sending,
                    sizeof(struct message) - sizeof(long),
                    0
                    );
    return number_ptr;
}




int main (int argc, const char* argv[])
{

//==================================== Getting the number ============================================
	
    int nThreads = 0;
    printf("Type the number of threads\n");
    scanf("%d", &nThreads);

    if (nThreads < 1)
    {
        printf( "Invalid number of threads received.\n"
                "Should be positive\n"
                "Got %d\n",
                nThreads);
        exit(-1);
    }

//======================================== Using threads ==============================================
    struct thread_box* threads = (struct thread_box*) calloc(nThreads, sizeof(struct thread_box));
    if (threads == NULL)
    {
        perror("Calloc didn't allocated memory\n");
        exit(errno);
    }

    int cond = creat("queue_base", 0600);
    if (cond == -1)
    {
        perror("Failed to create base file");
        exit(errno);
    }
    int key = ftok("queue_base", 1);
    if (key == -1)
    {
        perror("Failed to get key from file");
        exit(errno);
    }

    int msgid = msgget(key, IPC_CREAT | 0600);
    if (msgid == -1)
    {
        perror("Failed to create message queue");
        exit(errno);
    }

    int i = 0;
    int err = 0;
    for (i = 0; i < nThreads; i++)
    {
        threads[i].index = i;
        threads[i].msgid = msgid;
        err = pthread_create (&(threads[i].id), NULL, epic_func, (void*)(&threads[i]));
        if (err)
        {
            perror ("pthread_create failed\n");
            exit(errno);
        }
    }

    struct message sending  = {1};
    struct message received = {0};

    cond = msgsnd(  msgid, 
                    &sending, 
                    sizeof(struct message) - sizeof(long),
                    0
                    );
    if (cond == -1)
    {
        perror("Failed to send first message");
        exit(errno);
    }

    cond = msgrcv(  msgid,
                    &received,
                    sizeof(struct message) - sizeof(long),
                    nThreads + 1,
                    0);


    free(threads);
    msgctl(msgid, IPC_RMID, NULL);

	return 0;
}