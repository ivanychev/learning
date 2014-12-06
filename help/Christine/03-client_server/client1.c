#define _XOPEN_SOURCE
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LAST_MESSAGE 255

int main(void)
{
    
    int msqid;
	long id;
    char pathname[]="09-1a.c";
    key_t  key;
    int i,len, maxlen;
    id = getpid();
    struct mymsgbuf
    {
       long mtype;
       struct {
		int pid;
		char mtext[81];
       }info;
    } mybuf;



    /* Create or attach message queue  */
    
    key = ftok(pathname, 0);
    
    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0){
       printf("Can\'t get msqid\n");
       exit(-1);
    }





    /* Send information */
    
       
       mybuf.mtype = 1;
       strcpy (mybuf.info.mtext, "From client1");
       mybuf.info.pid = id;
	len = sizeof (mybuf.info);
       
       if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0){
         printf("Can\'t send message to queue\n");
         msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
         exit(-1);
      }
       
    
//------------------------------------
//-------------------------
       
       maxlen = 100;
       
       if (( len = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, id, 0)) < 0){
         printf("Can\'t receive message from queue\n");
         exit(-1);
       }
       
       printf("Answer from server %s\n", mybuf.info.mtext);   
 
    return 0;    
}
