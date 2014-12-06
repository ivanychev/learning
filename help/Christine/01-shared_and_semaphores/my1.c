#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <errno.h>

int main()
{
    char * mas ;
    int shmid;
    int new =1, i=0;
    char pathname[] = "prog1.c";
    key_t key;
    if ((key = ftok (pathname, 0)) < 0){
        printf ("Can\'t generate key\n");
        exit(-1);
    }

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

    if ((mas = (char *)shmat(shmid, NULL, 0)) == (char *)(-1)){
        printf ("Can't attach shared mempry\n");
        exit (-1);
    }
    int c;
//----------------semah
int   semid;
    struct sembuf mybuf;
    
    key = ftok(pathname, 0);
    
    if((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0){
      printf("Can\'t create semaphore set\n");
      exit(-1);
    }
    
 
//--------------------proga
char mas1[] = "Hello1";
 
for (i=0; i<7; i++){
        mas[i]=mas1[i];
    }
    mybuf.sem_num = 0;
    mybuf.sem_op  = 1;
    mybuf.sem_flg = 0;
    
    if(semop(semid, &mybuf, 1) < 0){
      printf("Can\'t add 1 to semaphore\n");
      exit(-1);
    }  
    mybuf.sem_num = 0;
    mybuf.sem_op  = -2;
    mybuf.sem_flg = 0;
    
    if(semop(semid, &mybuf, 1) < 0){
      printf("Can\'t add 1 to semaphore\n");
      exit(-1);
    }  
    i=0;
    while (mas[i]!='\0'){
        printf("%c", mas[i]);
        i++;
    }
    printf("\n");
  
//----------------------deleted memory
    if (shmdt(mas) < 0){
        printf ("Can't detach shared memory\n");
        exit (-1);
    }

    return 0;
}
