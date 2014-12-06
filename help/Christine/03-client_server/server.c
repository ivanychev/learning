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

//-------------------------
for (i=0; i<5; i++) {
       
       maxlen = 100;
       
       if (( len = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, 1, 0)) < 0){
         printf("Can\'t receive message from queue\n");
         //exit(-1);
       }
	id = mybuf.info.pid;
	printf("message from %ld, val = %s\n", id, mybuf.info.mtext);
	
       mybuf.mtype = id;
       strcpy (mybuf.info.mtext, "From server");
       mybuf.info.pid = 0;
	len = sizeof (mybuf.info);
       
       if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0){
         printf("Can\'t send message to queue\n");
         msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
         exit(-1);
       }
       
       
    }    

msgctl(msqid, IPC_RMID, (struct msqid_ds *)NULL);
       
    
//------------------------------------

 
    return 0;    
}
