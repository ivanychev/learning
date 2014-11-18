#include "shared.h"
/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param argc [description]
 * @param argv [description]
 * 
 * @return [description]
 */

//===================================================================================
//===================================================================================
int main(int argc, char const *argv[])
{
	if (argc > 1)
		send(argv[1]);
	else
		receive();
}

void last_cleaner()
{
	unlink(FILE_NAME_SHMEM_ATTACH);
	unlink(SND_FLAG);
	unlink(RCV_FLAG);
}

//===================================================================================
//===================================================================================

#undef  F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE last_cleaner();
int receive()
{
	int master_receiver = is_receiver();
	if (!master_receiver)
		exit(EXIT_SUCCESS);

	int semid = get_sems(  FILE_NAME_SHMEM_ATTACH, 4);
	CHECK(semid != -1, "Failed to get semaphors id");

	int cond = rcv_protect_connection(semid);
	CHECK(cond == 0, "Failed to set up protected connection");

	int shmemid = 0;
	void* smbuf = get_memptr( FILE_NAME_SHMEM_ATTACH,
				  BUF_SIZE + sizeof(long),
				  &shmemid);
	assert(smbuf != (void*)-1);
	struct sembuf activate = {RCV_CONNECT, -1, 0};
	cond = semop(semid, &activate, 1);

	struct sembuf mutexes[3] = {
		{SND_MUTEX, -1, 0},
		{RCV_MUTEX,  1, 0},
		{RCV_MUTEX,  0, 0}
	};
	long* nbytes_to_save = smbuf + BUF_SIZE;

	cond = semop(semid, &mutexes[2], 1);
	CHECK(cond == 0, "Failed to set semaphors");

	while (*nbytes_to_save != -1)
	{
		cond = write(STDOUT_FILENO, smbuf, *nbytes_to_save);
		CHECK(cond == *nbytes_to_save, "Printed ammount of bytes isn't valid");
		cond = semop(semid, mutexes, 3);
		CHECK(cond == 0, "Failed to set semaphors");
	};

	semop(semid, mutexes, 1);
	unlink(RCV_FLAG);
	exit(EXIT_SUCCESS);
}

//===================================================================================
//===================================================================================

int send(const char* filename)
{
	int master_sender = is_sender();
	if (!master_sender)
		exit(EXIT_SUCCESS);

	int shmemid = 0;
	void* smbuf = get_memptr( FILE_NAME_SHMEM_ATTACH,
				  BUF_SIZE + sizeof(long),
				  &shmemid);
	assert(smbuf != (void*)-1);
	long* nbytes_to_save = smbuf + BUF_SIZE;

	CHECK(smbuf != (void*)-1, "Failed to get memory pointer");

	int semid = get_sems(  FILE_NAME_SHMEM_ATTACH, 4);
	CHECK(semid != -1, "Failed to get semaphors id");

	int cond = snd_protect_connection(semid);
	CHECK(cond == 0, "Failed to set up protected connection");

	int fileid = open(filename, O_RDONLY);
	CHECK(fileid != -1, "Failed to open file to send");

	struct sembuf mutexes[3] = {
		{SND_MUTEX,  1, 0},
		{RCV_MUTEX, -1, 0},
		{SND_MUTEX,  0, 0}
	};
	int nbytes = 0;
	while ((nbytes = read(fileid, smbuf, BUF_SIZE)) > 0)
	{
		*nbytes_to_save = nbytes;
		cond = semop(semid, mutexes, 3);
		CHECK(cond == 0, "Failed to set semaphors");
	}

	*nbytes_to_save = -1;
	cond = semop(semid, mutexes, 2);

	cond = snd_clean(semid, fileid, shmemid);
	exit(EXIT_SUCCESS);
}
#undef  F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE return -1;

//===================================================================================
//===================================================================================

int is_sender()
{
	int fileid = open(SND_FLAG, O_CREAT, 0600);
	CHECK(fileid != -1, "Failed to open sender flag");
	int key = ftok(SND_FLAG, 0);
	CHECK(key != -1, "Failed to get flag key");

	int semid = semget(key, 1, IPC_CREAT | IPC_EXCL);
	if (semid == -1 && errno == EEXIST)
		return 0;
	return 1;
}

int is_receiver()
{
	int fileid = open(RCV_FLAG, O_CREAT, 0600);
	CHECK(fileid != -1, "Failed to open receiver flag");
	int key = ftok(RCV_FLAG, 0);
	CHECK(key != -1, "Failed to get flag key");

	int semid = semget(key, 1, IPC_CREAT | IPC_EXCL);
	if (semid == -1 && errno == EEXIST)
		return 0;
	return 1;
}
//===================================================================================
//===================================================================================

void* kill_if_died(void* ptr)
{
	struct Wait_for* waiting_sem = (struct Wait_for*)ptr;
	assert(waiting_sem);
	int semid =  waiting_sem -> semid;

	struct sembuf s = {	waiting_sem -> num,
				0,
				0};
	printf("%s\n", waiting_sem -> msg);
	last_cleaner();
	exit(EXIT_FAILURE);
}


//===================================================================================
//===================================================================================
#undef  F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE return -1;
int snd_protect_connection(int semid)
{
	struct sembuf snd_ifdie     = {	SND_DIED,
					1,
					SEM_UNDO};
	struct sembuf rcv_ifdie     = {	RCV_DIED,
					1,
					0};
	struct sembuf rcv_connect   = {	RCV_CONNECT,
					1,
					0};
	int cond = semop(semid, &snd_ifdie, 1);
	CHECK(cond == 0, "Failed to set SND_IFDIE semaphor");
	    cond = semop(semid, &rcv_ifdie, 1);
	CHECK(cond == 0, "Failed to set RCV_IFDIE semaphor");

	pthread_t wait_for_rcv_death;
	static struct Wait_for rcv = {/*semid, RCV_DIED*/};
	rcv.semid = semid;
	rcv.num   = RCV_DIED;
	rcv.msg	  = "Receiver died";

	cond = pthread_create(  &wait_for_rcv_death, 
				NULL, 
				kill_if_died, 
				(void*)(&rcv));
	CHECK(cond == 0, "Failed to create waiting thread");

	cond = semop(semid, &rcv_connect, 1);
	CHECK(cond == 0, "Failed to set connection semaphor");

	return 0;
}

int rcv_protect_connection(int semid)
{
	struct sembuf sem_undo_zero[2] = {	
		{RCV_DIED, -1, 0},
		{RCV_DIED,  1, SEM_UNDO}};
	int cond = semop(semid, sem_undo_zero, 2);
	CHECK(cond == 0, "Failed to set RCV_DIED to undo mode");

	pthread_t wait_for_snd_death;
	static struct Wait_for snd = {/*semid, SND_DIED*/};
	snd.semid = semid;
	snd.num   = SND_DIED;
	snd.msg	  = "Sender died";

	cond = pthread_create(  &wait_for_snd_death, 
				NULL, 
				kill_if_died, 
				(void*)(&snd));
	CHECK(cond == 0, "Failed to create waiting thread");

	return 0;
}

#undef F_CHECK_EXIT_CODE


//===================================================================================
//===================================================================================

int snd_clean(int semid, int fileid, int shmemid)
{
	if (semid >= 0)
		semctl(semid, 0, IPC_RMID);
	if (fileid >= 0)
		close(fileid);
	if (shmemid >= 0)
		shmctl(shmemid, IPC_RMID, NULL);
	unlink(SND_FLAG);

	return 0;
}


//===================================================================================
//===================================================================================

#define F_CHECK_EXIT_CODE return -1;

int get_sems(const char* filename, int num)
{
	CHECK(filename, "Argumented filename pointer is NULL");
	int fileid = creat(filename, 600);
	key_t file_key = ftok(filename, 1);
	CHECK(file_key != -1, "Failed to get System V key");
	int sem_id = semget(file_key, num, IPC_CREAT | 0600);	
	CHECK(sem_id != -1, "Failed to get semaphor id from System V key");
	return sem_id;
}


//===================================================================================
//===================================================================================
#undef  F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE return (void*)-1;
void* get_memptr(const char* filename, size_t size, int* id_to_save)
{
	CHECK(filename,  "Argumented filename pointer is NULL");
	CHECK(id_to_save,"Argumented pointer is NULL" );
	WARN(size < PAGESIZE, "Requested size of shared memory will be rounded up to PAGESIZE");

	int shared_id = set_memory(FILE_NAME_SHMEM_ATTACH, 
		    		   BUF_SIZE);
	CHECK(shared_id != -1, "Failed to get shared memory");
	void* shm_ptr = shmat(shared_id, NULL, 0);
	CHECK(shm_ptr == (void*) -1, "Failed to get pointer from share memory id");
	memset(shm_ptr, size, 0);

	*id_to_save = shared_id;
	return shm_ptr;
}


//===================================================================================
//===================================================================================
#undef  F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE return -1;
int set_memory(const char* filename, size_t size)
{
	assert(filename);
	assert(size);

	key_t file_key = ftok(filename, 1);
	CHECK(file_key != -1, "Failed to get System V key");

	int memid = shmget(file_key, size, IPC_CREAT | 0600);
	CHECK(memid != -1, "Failed to get memory id from System V key");

	return memid;
}	

#undef F_CHECK_EXIT_CODE
