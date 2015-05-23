#include "queue.h"

#ifdef QUEUE_EXISTS
#undef QUEUE_EXISTS
#endif


int main(int argc, char const *argv[])
{
	CHECK(argc == 2, "Wrong number of arguments");
	long proc_num = 0;
	CHECK(get_long(&proc_num, argc, argv[1]) == GET_OK, "Failed to interpret as number");
	
	int queue_file_id = creat(QUEUE_FILE, 0600);
	CHECK(queue_file_id != -1, "Failed to open file to stick queue to");

	int queue_key = ftok(QUEUE_FILE, 1);
	
	CHECK(queue_key != -1, "Failed to generate the key");

	int queue_id = 0;

#define QUEUE_EXISTS	

	CHECK((queue_id = msgget(queue_key, IPC_CREAT | 0600))!= -1, "Failed to create queue");
	
	OUT1("Queue id: %d\n", queue_id);

	int i = 0;
	pid_t proc = 0;

	for (i = 1; i <= proc_num; i++)
	{
		proc = fork();
		CHECK(proc != -1, "Failed to fork");

		if (proc == 0)
			break;
	}

	if (proc == 0)
	{
		OUT2("Child begin: index = %d, proc_num = %ld\n", i, proc_num);
		child_part (queue_id, proc_num, i);
	}
	else
	{
		OUT2("Parent begin: index = %d, proc_num = %ld\n", i, proc_num);
		parent_part(queue_id, proc_num);
	}
	return 0;
}

int parent_part(int queue_id, int proc_num)
{
	Long_msg to_send = {1, MSG_VAL};
	
	OUT2("queue_id = %d\nSend pointer = %08x\n", queue_id, &to_send);
	OUT2("Sizeof = %ld, msgflg = 0, Value = %ld\n\n", sizeof(Long_msg)- sizeof(long), MSG_VAL);

	CHECK(	msgsnd(	queue_id, 
			&to_send, 
			sizeof(to_send) - sizeof(long), 
			0
			) != -1, "Failed to send in parent");
	
	Long_msg received = {};
	int msg_size = 	msgrcv(	queue_id, 
				&received, 
				sizeof(Long_msg) - sizeof(long), 
				proc_num + 1, 
				0);
	
	OUT1("[Parent] ceived.type = %ld\n", received.type);
	OUT1("[Parent] ceived.val  = %ld\n", received.val);

	OUT1("[Parent] Msg size = %d\n",   msg_size);
	OUT1("[Parent] Received = %ld\n",  received.val);

	CHECK(msg_size == (int)(sizeof(Long_msg) - sizeof(long)), "Failed to read in child");
	CHECK(received.val == MSG_VAL, "Invalid received message");

	fprintf(stderr, "Print finished\n");

	msgctl(queue_id, IPC_RMID, NULL);
	return 0;
}


int child_part(int queue_id, int proc_num, int index)
{
	Long_msg received = {};
	OUT1("Child [%d] entered\n", index);

	int msg_size = msgrcv(  queue_id, 
				&received, 
				sizeof(Long_msg) - sizeof(long), 
				index, 
				0);
	
	OUT2("[%d] Index = %d\n", index, index);
	OUT2("[%d] received.type = %ld\n", index, received.type);
	OUT2("[%d] received.val  = %ld\n", index, received.val);

	OUT2("[%d] Msgg size = %d\n",   index, msg_size);
	OUT2("[%d] Received = %ld\n",  index, received.val);

	CHECK(msg_size == (int)(sizeof(Long_msg) - sizeof(long)), "Failed to read in child");
	CHECK(received.val == MSG_VAL, "Invalid received message");

	fprintf(stderr, "%d ", index);



	Long_msg to_send = {(long)index + 1, MSG_VAL};
	CHECK(msgsnd(	queue_id, 
			&to_send, 
			sizeof(to_send) - sizeof(long), 
			0) != -1, "Failed to send in child");
	OUT2("[%d] Message type = %ld sent\n", index, to_send.type)

	return 0;
}


int get_long(long* save, int argc, const char* str)
{
	assert(save);
	int base = 10;
	char* endptr = NULL;

	long val = strtol(str, &endptr, base);

	if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
	       || (errno != 0 && val == 0)) {
	   return GET_FAILED;
	}

	if (endptr == str) {
	   fprintf(stderr,  "No digits were found\n");
	   return GET_FAILED;
	}

	*save = val;
	return GET_OK; 
}