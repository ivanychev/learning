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


int main(int argc, char const *argv[])
{
	if (argc > 1)
		return send(argv[1]);
	else
		return receive();
}

void* kill_if_died(void* ptr)
{
	struct Wait_for* waiting_sem = (Wait_for*)ptr;
	assert(waiting_sem);
	int semid =  waiting_sem -> semid;

	struct sembuf s = {	waiting_sem -> num,
				0,
				0};
	printf("%s\n", waiting_sem -> msg);
	exit(EXIT_FAILURE);
}

#define F_CHECK_EXIT_CODE return -1;
int snd_protect_connection(int semid)
{
	struct snd_ifdie = {	SND_DIED,
				1,
				SEM_UNDO};
	struct rcv_ifdie = {	RCV_DIED,
				1,
				SEM_UNDO};
	int cond = semop(semid, &snd_ifdie, 1);
	CHECK(cond == 0, "Failed to set SND_IFDIE semaphor");
	int cond = semop(semid, &rcv_ifdie, 1);
	CHECK(cond == 0, "Failed to set RCV_IFDIE semaphor");

	pthread_t wait_for_rcv_death;
	static struct Wait_for rcv = {semid, RCV_DIED};

	cond = pthread_create(  &wait_for_rcv_death, 
				NULL, 
				kill_if_died, 
				(void*)rcv);
	CHECK(cond == 0, "Failed to create waiting thread");

	return 0;
}

#undef F_CHECK_EXIT_CODE

int send(const char* filename)
{
	int master_sender = is_sender();
	if (!master_sender)
		exit(EXIT_SUCCESS);

	void* smbuf = get_memptr( FILE_NAME_SHMEM_ATTACH,
				BUF_SIZE + sizeof(long));
	long* nbytes_to_save = smbuf + BUF_SIZE;

	CHECK(smbuf != (void*)-1, "Failed to get memory pointer");

	int semid = get_sems(  FILE_NAME_SHMEM_ATTACH, 4);
	CHECK(semid != -1, "Failed to get semaphors id");

	int cond = snd_protect_connection(semid);
	CHECK(cond == 0, "Failed to set up protected connection");

	int fileid = open(filename, O_RDONLY);
	if (fileid == -1, "Failed to open file to send");

	struct sembuf[2] mutexes = {
		{SND_MUTEX,  1, 0},
		{RCV_MUTEX, -1, 0}
	}
	while ((nbytes = read(fileid, smbuf, BUF_SIZE)) > 0)
	{
		*nbytes_to_save = nbytes;
		cond = semop(semid, mutexes, 2);
		CHECK(cond == 0, "Failed to set semaphors");
	}

	//struct sembuf finished = {SND_FINISHED, }			<< FINISH HERE
		

}

#define F_CHECK_EXIT_CODE return -1;

int get_sems(const char* filename, int num)
{
	CHECK(filename, "Argumented filename pointer is NULL");
	key_t file_key = ftok(filename, 1);
	CHECK(file_key != -1, "Failed to get System V key");
	int sem_id = semget(file_key, num, IPC_CREAT | 0600);	
	CHECK(sem_id != -1, "Failed to get semaphor id from System V key");
	return sem_id;
}

int get_memptr(const char* filename, size_t size)
{
	CHECK(filename, "Argumented filename pointer is NULL");
	WARN(size < PAGESIZE, "Requested size of shared memory will be rounded up to PAGESIZE");

	int shared_id = set_memory(FILE_NAME_SHMEM_ATTACH, 
		    		   BUF_SIZE);
	CHECK(shared_id != -1, "Failed to get shared memory");
	void* shm_ptr = shmat(shared_id, NULL, 0);
	CHECK(shm_ptr == (void* -1), "Failed to get pointer from share memory id");
	memset(shm_ptr, size, 0);

	return shm_ptr;
}


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
