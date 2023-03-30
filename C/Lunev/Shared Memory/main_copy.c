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
int main(int argc, char const *argv[]) {
  if (argc > 1)
    send(argv[1]);
  else
    receive();
}

//===================================================================================
//===================================================================================

void last_cleaner() {
  unlink(FILE_NAME_SHMEM_ATTACH);
  unlink(SND_FLAG);
  unlink(RCV_FLAG);
}

//===================================================================================
//===================================================================================

#undef F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE last_cleaner();
int receive() {
  int flagid = 0;
  int master_receiver = is_receiver(&flagid);
  if (!master_receiver)
    exit(EXIT_SUCCESS);

  int semid = get_sems(FILE_NAME_SHMEM_ATTACH, 5);
  CHECK(semid != -1, "Failed to get semaphors id");

  int cond = rcv_protect_connection(semid);
  CHECK(cond == 0, "Failed to set up protected connection");

  int shmemid = 0;
  void *smbuf =
      get_memptr(FILE_NAME_SHMEM_ATTACH, BUF_SIZE + sizeof(long), &shmemid);
  CHECK(smbuf != (void *)-1, "Failed to get shared memory pointer");
  struct sembuf activate = {RCV_CONNECT, -1, 0};
  cond = semop(semid, &activate, 1);
  OUT("# Activated\n");

  struct sembuf mutexes[3] = {
      {SND_MUTEX, -1, 0}, {RCV_MUTEX, 1, 0}, {RCV_MUTEX, 0, 0}};
  long *nbytes_to_save = smbuf + BUF_SIZE;

  cond = semop(semid, &mutexes[2], 1);
  CHECK(cond == 0, "Failed to set semaphors");

  while (*nbytes_to_save != -1) {
    OUT1("# Printing %ld bytes\n", *nbytes_to_save);
    cond = write(STDOUT_FILENO, smbuf, *nbytes_to_save);

    if (cond != *nbytes_to_save)
      fprintf(stderr, "Printed = %d\nExpected = %ld\n", cond, *nbytes_to_save);

    CHECK(cond == *nbytes_to_save, "Printed ammount of bytes isn't valid");
    OUT("# Getting...\n");
    cond = semop(semid, &mutexes[1], 1);
    cond = semop(semid, &mutexes[0], 1);
    OUT1("# Current SND_MUTEX is %d\n", semctl(semid, SND_MUTEX, GETVAL));
    OUT1("# Current RCV_MUTEX is %d\n", semctl(semid, RCV_MUTEX, GETVAL));

    cond = semop(semid, &mutexes[2], 1);
    OUT("# Got package\n");
    CHECK(cond == 0, "Failed to set semaphors");
  };

  OUT("# Finishing receiving\n");
  semop(semid, &mutexes[0], 1);
  unlink(RCV_FLAG);
  semctl(flagid, 0, IPC_RMID);

  exit(EXIT_SUCCESS);
}

//===================================================================================
//===================================================================================

int send(const char *filename) {
  int flagid = 0;
  int master_sender = is_sender(&flagid);
  if (!master_sender)
    exit(EXIT_SUCCESS);

  int shmemid = 0;
  void *smbuf =
      get_memptr(FILE_NAME_SHMEM_ATTACH, BUF_SIZE + sizeof(long), &shmemid);
  CHECK(smbuf != (void *)-1, "Failed to get shared memory pointer");
  long *nbytes_to_save = smbuf + BUF_SIZE;
  *nbytes_to_save = 0;

  CHECK(smbuf != (void *)-1, "Failed to get memory pointer");

  int semid = get_sems(FILE_NAME_SHMEM_ATTACH, 5);
  CHECK(semid != -1, "Failed to get semaphors id");

  int cond = snd_protect_connection(semid);
  CHECK(cond == 0, "Failed to set up protected connection");

  int fileid = open(filename, O_RDONLY);
  CHECK(fileid != -1, "Failed to open file to send");

  struct sembuf rcv_activate[2] = {{RCV_MUTEX, 1, 0}, {RCV_CONNECT, 1, 0}};
  cond = semop(semid, rcv_activate, 2);
  CHECK(cond != -1, "Failed to connect to receiver");

  struct sembuf mutexes[3] = {
      {SND_MUTEX, 1, 0}, {RCV_MUTEX, -1, 0}, {SND_MUTEX, 0, 0}};
  int nbytes = 0;
  while ((nbytes = read(fileid, smbuf, BUF_SIZE)) > 0) {
    *nbytes_to_save = nbytes;
    OUT("# Sending\n");
    cond = semop(semid, &mutexes[0], 1);
    cond = semop(semid, &mutexes[1], 1);
    cond = semop(semid, &mutexes[2], 1);
    CHECK(cond == 0, "# Failed to set semaphors");
    OUT("# Package sent\n");
  }

  OUT("# Finishing...\n");
  *nbytes_to_save = -1;
  cond = semop(semid, &mutexes[0], 1);
  cond = semop(semid, &mutexes[1], 1);
  cond = semop(semid, &mutexes[2], 1);
  OUT("# Finished!\n");

  cond = snd_clean(semid, fileid, shmemid, flagid);
  exit(EXIT_SUCCESS);
}
#undef F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE return -1;

//===================================================================================
//===================================================================================

int is_sender(int *semflag) {
  int fileid = open(SND_FLAG, O_CREAT, 0600);
  CHECK(fileid != -1, "Failed to open sender flag");
  int key = ftok(SND_FLAG, 1);
  CHECK(key != -1, "Failed to get flag key");

  int semid = semget(key, 1, IPC_CREAT | 0660);
  CHECK(semid != -1, "Failed to get flag semaphore id");
  *semflag = semid;
  struct sembuf act_flag[2] = {{0, 0, IPC_NOWAIT}, {0, 1, SEM_UNDO}};

  int cond = semop(semid, act_flag, 2);

  if (cond == -1 && errno != EAGAIN)
    CHECK(0, "Unexpected error happened");
  if (cond == -1)
    return 0;
  return 1;
}

int is_receiver(int *semflag) {
  int fileid = open(RCV_FLAG, O_CREAT, 0600);
  CHECK(fileid != -1, "Failed to open receiver flag");
  int key = ftok(RCV_FLAG, 1);
  CHECK(key != -1, "Failed to get flag key");

  int semid = semget(key, 1, IPC_CREAT | 0660);
  CHECK(semid != -1, "Failed to get flag semaphore id");
  *semflag = semid;

  struct sembuf act_flag[2] = {{0, 0, IPC_NOWAIT}, {0, 1, SEM_UNDO}};

  int cond = semop(semid, act_flag, 2);

  if (cond == -1 && errno != EAGAIN)
    CHECK(0, "Unexpected error happened");
  if (cond == -1)
    return 0;
  return 1;
}
//===================================================================================
//===================================================================================

void *kill_if_died(void *ptr) {
  struct Wait_for *waiting_sem = (struct Wait_for *)ptr;
  // printf("Caught %p\n", ptr);
  assert(waiting_sem);
  int semid = waiting_sem->semid;
  // printf("Caught again%p\n", ptr);
  struct sembuf s = {waiting_sem->num, 0, 0};
  semop(semid, &s, 1);
  OUT1("%s\n", waiting_sem->msg);
  last_cleaner();
  exit(EXIT_FAILURE);
}

//===================================================================================
//===================================================================================
#undef F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE return -1;
int snd_protect_connection(int semid) {
  struct sembuf snd_ifdie = {SND_DIED, 1, SEM_UNDO};
  struct sembuf rcv_ifdie = {RCV_DIED, 1, 0};
  struct sembuf rcv_connect = {RCV_CONNECT, 1, 0};
  int cond = semop(semid, &snd_ifdie, 1);
  CHECK(cond == 0, "Failed to set SND_IFDIE semaphor");
  cond = semop(semid, &rcv_ifdie, 1);
  CHECK(cond == 0, "Failed to set RCV_IFDIE semaphor");

  pthread_t wait_for_rcv_death;
  struct Wait_for *rcv = calloc(1, sizeof(struct Wait_for));
  assert(rcv);
  rcv->semid = semid;
  rcv->num = RCV_DIED;
  rcv->msg = "\n# Receiver died\n";

  OUT1("Thrown %p\n", rcv);
  cond = pthread_create(&wait_for_rcv_death, NULL, kill_if_died, (void *)(rcv));
  CHECK(cond == 0, "Failed to create waiting thread");

  cond = semop(semid, &rcv_connect, 1);
  CHECK(cond == 0, "Failed to set connection semaphor");

  return 0;
}

int rcv_protect_connection(int semid) {
  struct sembuf sem_undo_zero[2] = {{RCV_DIED, -1, 0}, {RCV_DIED, 1, SEM_UNDO}};
  int cond = semop(semid, sem_undo_zero, 2);
  CHECK(cond == 0, "Failed to set RCV_DIED to undo mode");

  pthread_t wait_for_snd_death;
  struct Wait_for *snd = calloc(1, sizeof(struct Wait_for));
  assert(snd);
  snd->semid = semid;
  snd->num = SND_DIED;
  snd->msg = "\n# Sender died\n";

  cond = pthread_create(&wait_for_snd_death, NULL, kill_if_died, (void *)(snd));
  CHECK(cond == 0, "Failed to create waiting thread");

  return 0;
}

#undef F_CHECK_EXIT_CODE

//===================================================================================
//===================================================================================

int snd_clean(int semid, int fileid, int shmemid, int flagid) {
  if (semid >= 0)
    semctl(semid, 0, IPC_RMID);
  if (fileid >= 0)
    close(fileid);
  if (shmemid >= 0)
    shmctl(shmemid, IPC_RMID, NULL);
  if (flagid >= 0)
    semctl(flagid, 0, IPC_RMID);
  unlink(SND_FLAG);
  /*
          int key = ftok(SND_FLAG, 1);
          int semflagid = semget(key, 1, IPC_CREAT | 0660);

          struct sembuf rm_flag = {0, -1, IPC_NOWAIT};
          semop(semflagid, &rm_flag, 1);
  */
  return 0;
}

//===================================================================================
//===================================================================================

#define F_CHECK_EXIT_CODE return -1;

int get_sems(const char *filename, int num) {
  CHECK(filename, "Argumented filename pointer is NULL");
  int fileid = creat(filename, 660);
  CHECK(fileid != -1 || (fileid == -1 && errno == EEXIST),
        "Unexpected error during sharing memory file creation");

  key_t file_key = ftok(filename, 1);
  CHECK(file_key != -1, "Failed to get System V key");
  OUT3("# File key: %d\n# Number: %d\n# Flag: %o\n", file_key, num,
       IPC_CREAT | 0660);
  int sem_id = semget(file_key, num, IPC_CREAT | 0660);
  CHECK(sem_id != -1, "Failed to get semaphor id from System V key");
  return sem_id;
}

#undef F_CHECK_EXIT_CODE
//===================================================================================
//===================================================================================

#define F_CHECK_EXIT_CODE return (void *)-1;
void *get_memptr(const char *filename, size_t size, int *id_to_save) {
  CHECK(filename, "Argumented filename pointer is NULL");
  CHECK(id_to_save, "Argumented pointer is NULL");
  WARN(size >= PAGESIZE,
       "Requested size of shared memory will be rounded up to PAGESIZE");

  int cond = creat(filename, 0660);
  if (cond == -1)
    printf("Failed to create file [%s]\n", filename);
  CHECK(cond != -1 || (cond == -1 && errno == EEXIST),
        "Unexpected error during sharing memory file creation");

  int shared_id = set_memory(filename, size);
  CHECK(shared_id != -1, "Failed to get shared memory");
  void *shm_ptr = shmat(shared_id, NULL, 0);
  CHECK(shm_ptr != (void *)-1, "Failed to get pointer from share memory id");
  memset(shm_ptr, size, 0);

  *id_to_save = shared_id;
  return shm_ptr;
}

//===================================================================================
//===================================================================================
#undef F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE return -1;
int set_memory(const char *filename, size_t size) {
  assert(filename);
  assert(size);

  key_t file_key = ftok(filename, 1);
  CHECK(file_key != -1, "Failed to get System V key");

  int memid = shmget(file_key, size, IPC_CREAT | 0660);
  CHECK(memid != -1, "Failed to get memory id from System V key");

  return memid;
}

#undef F_CHECK_EXIT_CODE
