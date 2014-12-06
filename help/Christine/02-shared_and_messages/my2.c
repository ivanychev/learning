#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <errno.h>
#include <sys/msg.h>
#include <string.h>

int main()
{

char * mas ;
    int shmid;
    int new =1, i=0;
    char pathname[] = "prog1.c";
    key_t key, key1;
    if ((key = ftok (pathname, 0)) < 0){
        printf ("Can\'t generate key\n");
        exit(-1);
    }
    int msqid;
	long id;
    int len, maxlen;
    struct mymsgbuf
    {
       long mtype;
       char mes[2];
    } mybuf;

    //создание эксклюзивной разделяемой памяти

    if ((shmid = shmget (key, 10000, 0666|IPC_CREAT|IPC_EXCL))<0){
        if (errno != EEXIST){
            printf ("Cant created shared memory\n");
            exit(-1);
        }else{
            //память есть, получаем ее дескриптор
            if ((shmid = shmget (key, 10000, 0))<0){
                printf ("Can\'t find shared memory\n");
                exit (-1);
            }
            new = 0;
        }
    }
    //printf ("Lol2\n");

    if ((mas = (char *)shmat(shmid, NULL, 0)) == (char *)(-1)){
        printf ("Can't attach shared mempry\n");
        exit (-1);
    }
    int c;
//------------------------------------semah
/* Create or attach message queue  */
    
    key = ftok(pathname, 0);
    
    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0){
       printf("Can\'t get msqid\n");
       exit(-1);
    }
   
//-------------------------proga
    //priem
    maxlen = 100;
       
       if (( len = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, 0, 0)) < 0){
         printf("Can\'t receive message from queue\n");
         exit(-1);
       }
//------------------------
    char mas1[] = "Hello2";
    
 if (mybuf.mtype==1){
    i=0;
    while (mas[i]!='\0'){
        printf("%c", mas[i]);
        i++;
    }
printf ("\n");
}


    for (i=0; i<7; i++){
        mas[i]=mas1[i];
    }
    
//send dignal
	mybuf.mtype = 2;
		len = 2;
       
       if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0){
         printf("Can\'t send message to queue\n");
         msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
         exit(-1);
      }
//---------------

/////////////////////deleted memory
    if (shmdt(mas) < 0){
        printf ("Can't detach shared memory\n");
        exit (-1);
    }
    //shmctl (shmid, IPC_RMID, NULL);
    return 0;
}
