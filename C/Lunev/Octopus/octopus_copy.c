/**
 * 	@mainpage
 *
 * 	@author		Sergey Ivanychev, DCAM MIPT, 376 group
 *
 * 	@brief		Program is given a number and file. Using select() it
 * does with that some things and prints to STDOUT. Its structure looks like
 * obstacle
 *
 * 	@version	v 1.0
 */

#include "iv_standard.h"
#include "octopus.h"

//================================= GLOBALS
//============================================================================

unsigned long long *TRANSFER_INFO = 0;
const int SCANNED = 0;
const int WRITTEN = 1;
const int FINISHED = 2;

//================================= CODE
//============================================================================

int main(int argc, char const *argv[]) {
  int cond = 0;
  long kids_num = 0;
  CHECKN(argc == 3, IVINVALARGNUM);
  const char *filename = argv[1];
  CALL(cond, get_long(&kids_num, argv[2]), cond == 0,
       "Failed to get kids number");
  CHECK(0 < kids_num && kids_num < 1024,
        "Kids quantity is too big for select()");

  tentacle *kids_info = (tentacle *)calloc(kids_num, sizeof(tentacle));

  CHECKN(kids_info, IVALLOCFAIL);
  CALL(cond, activate_kids(kids_num, kids_info, filename), cond == 0,
       "Failed to activate kids");
  CALL(cond, create_bufs(kids_num, kids_info), cond == 0,
       "Failed to set buffers");
  CALL(cond, nonblock_ids(kids_num, kids_info), cond == 0,
       "Failed to set pipes to nonblocking mode");
  CALL(cond, proceed(kids_num, kids_info), cond == 0, "Failed to send file");

  return 0;
}

//====================================================================================================================================

#undef F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE return -1;

int activate_kids(int num, tentacle *kids_info, const char *filename) {
  assert(kids_info);
  assert(num > 0);
  int cond = 0;
  pipe_io kid_read = {};
  pipe_io kid_write = {};

  tentacle_in send = {};

  CALL(cond, first_kid_deal(kids_info, filename), cond == 0,
       "Failed to create first kid");

  for (int i = 1; i < num; ++i) {

    CALL(cond, pipe(kid_read.rw), cond == 0, "Failed to get pipe");
    CALL(cond, pipe(kid_write.rw), cond == 0, "Failed to get pipe");
    CALL(cond, fork(), cond >= 0, "Failed to fork");
    if (cond == 0) {
      CALL(cond, shmdt(TRANSFER_INFO), cond == 0,
           "Failed to detach shared memory segment");
      CALL(cond, close(kid_read.rw[WRITE]), cond == 0, "Failed to close pipe");
      CALL(cond, close(kid_write.rw[READ]), cond == 0, "Failed to close pipe");
      CALL(cond, close_pipes(i, kids_info), cond == 0,
           "Failed to close pipes of parent");
      send.to_read = kid_read.rw[READ];
      send.to_write = kid_write.rw[WRITE];
      send.index = i;
      tentacle_proceed(send);
    }

    // OUT2("NEW KID %d, PID = %d\n", i, cond);
    CALL(cond, close(kid_read.rw[READ]), cond == 0, "Failed to close pipe");
    CALL(cond, close(kid_write.rw[WRITE]), cond == 0, "Failed to close pipe");
    kids_info[i].to_read = kid_write.rw[READ];
    kids_info[i].to_write = kid_read.rw[WRITE];
    kids_info[i].procid = cond;
    kids_info[i].index = i;
  }

  return 0;
}

//====================================================================================================================================

int create_bufs(int num, tentacle *kids) {
  assert(num > 0);
  assert(kids);

  for (int i = 0; i < num; ++i) {
    kids[i].buf = (char *)calloc((i + 1) * BUFBLOCK, 1);
    CHECKN(kids[i].buf, IVALLOCFAIL);
    kids[i].size = (i + 1) * BUFBLOCK;
    kids[i].contain = 0;
  }

  return 0;
}

//====================================================================================================================================

int nonblock_ids(int kids_num, tentacle *kids_info) {
  assert(kids_info);
  int cond = 0;
  for (int i = 0; i < kids_num; i++) {
    if (i != 0) {
      cond = fcntl(kids_info[i].to_write, F_GETFL, 0);
      CHECK(cond != -1, "Failed to proceed fcntl");
      fcntl(kids_info[i].to_write, F_SETFL, cond | O_NONBLOCK);
      CHECK(cond != -1, "Failed to proceed fcntl");
    }
    cond = fcntl(kids_info[i].to_read, F_GETFL, 0);
    CHECK(cond != -1, "Failed to proceed fcntl");
    fcntl(kids_info[i].to_read, F_SETFL, cond | O_NONBLOCK);
    CHECK(cond != -1, "Failed to proceed fcntl");
  }
  return 0;
}

//====================================================================================================================================

int proceed(int kids_num, tentacle *kids_info) {
  assert(kids_info);
  assert(kids_num > 0);

  fd_set sndset;
  int sndmax = 0;
  fd_set rcvset;
  int rcvmax = 0;

  struct timeval timeout_copy = {.tv_sec = 2, .tv_usec = 0};

  while (!(TRANSFER_INFO[FINISHED] &&
           TRANSFER_INFO[SCANNED] == TRANSFER_INFO[WRITTEN])) {
    getrcv(kids_num, kids_info, &rcvset, &rcvmax);
    getsnd(kids_num, kids_info, &sndset, &sndmax);
    int max = (sndmax > rcvmax) ? sndmax : rcvmax;
    struct timeval timeout = timeout_copy;
    int cond = select(max + 1, &rcvset, &sndset, NULL, &timeout);
    OUT3("[PARENT] After select FINISHED = %llu, SCANNED = %llu, WRITTEN = "
         "%llu\n",
         TRANSFER_INFO[FINISHED], TRANSFER_INFO[SCANNED],
         TRANSFER_INFO[WRITTEN]);

    CHECK(cond >= 0, "Error while select()");

    CHECK(!(cond == 0 && !(TRANSFER_INFO[FINISHED] &&
                           TRANSFER_INFO[SCANNED] == TRANSFER_INFO[WRITTEN])),
          "Timeout expired but file hasn't been transfered");
    CALL(cond, transfer_operations(kids_info, kids_num, sndset, rcvset),
         cond == 0, "Failed to proceed transfer operations");
  }

  return 0;
}

//====================================================================================================================================

int transfer_operations(tentacle *kids_info, int kids_num, fd_set sndset,
                        fd_set rcvset) {
  assert(kids_info);
  int cond = 0;

  for (int i = 0; i < kids_num; i++) {
    if (i != 0 && FD_ISSET(kids_info[i].to_write, &sndset))
      CALL(cond, write_to_tentacle(&kids_info[i - 1], kids_info[i].to_write),
           cond > 0, "Failed to write to tentacle");
    if (FD_ISSET(kids_info[i].to_read, &rcvset))
      CALL(cond, read_from_tentacle(&kids_info[i]), cond > 0,
           "Failed to write to tentacle");
  }
  if (kids_info[kids_num - 1].contain && FD_ISSET(STDOUT_FILENO, &sndset)) {
    CALL(cond, write_to_tentacle(&kids_info[kids_num - 1], STDOUT_FILENO),
         cond > 0, "Failed to write to tentacle");
    TRANSFER_INFO[WRITTEN] += cond;
  }

  return 0;
}

//====================================================================================================================================

int read_from_tentacle(tentacle *reading) {
  assert(reading);

  char *where = &(reading->buf[reading->contain]);
  int nbytes = reading->size - reading->contain;

  OUT1("[READER] nbytes before = %d\n", nbytes);
  nbytes = read(reading->to_read, where, nbytes);
  OUT1("[READER] nbytes after  = %d\n", nbytes);
  CHECK(nbytes > 0, "Failed to read from tentacle");
  reading->contain += nbytes;
  return nbytes;
}

//====================================================================================================================================

int write_to_tentacle(tentacle *from, int writeid) {

  assert(from);
  char *where = from->buf;
  int nbytes = from->contain;

  nbytes = write(writeid, where, nbytes);
  CHECK(nbytes > 0, "Failed to write to tentacle");
  memmove(where, &where[nbytes], from->size - nbytes);
  from->contain -= nbytes;

  return nbytes;
}

//====================================================================================================================================

int getsnd(int kids_num, tentacle *kids_info, fd_set *sndset, int *maxsndid) {
  assert(kids_info);
  assert(sndset);
  assert(maxsndid);

  fd_set snd;
  int max = 0;
  int count = 0;
  FD_ZERO(&snd);

  OUT("[PARENT] SNDSET: ");
  for (int i = 0; i < kids_num - 1; ++i)
    if (kids_info[i].contain) {
      FD_SET(kids_info[i + 1].to_write, &snd);
      OUT1("%d ", kids_info[i + 1].to_write);
      max = (max < kids_info[i + 1].to_write) ? kids_info[i + 1].to_write : max;
      count++;
    }
  if (kids_info[kids_num - 1].contain) {
    FD_SET(STDOUT_FILENO, &snd);
    OUT1("%d", STDOUT_FILENO);
    max = (max < STDOUT_FILENO) ? STDOUT_FILENO : max;
    count++;
  }
  OUT("\n");
  *sndset = snd;
  *maxsndid = max;
  return count;
}

//====================================================================================================================================

int getrcv(int kids_num, tentacle *kids_info, fd_set *rcvset, int *maxrcvid) {
  assert(kids_info);
  assert(rcvset);
  assert(maxrcvid);

  fd_set rcv;
  int max = 0;
  int count = 0;
  FD_ZERO(&rcv);

  OUT("[PARENT] RCVSET: ");
  for (int i = 0; i < kids_num; ++i) {
    if (kids_info[i].size - kids_info[i].contain > 0) {
      FD_SET(kids_info[i].to_read, &rcv);
      OUT1("%d ", kids_info[i].to_read);
      max = (max < kids_info[i].to_read) ? kids_info[i].to_read : max;
    }
  }
  OUT("\n");
  *rcvset = rcv;
  *maxrcvid = max;
  return count;
}

//====================================================================================================================================

int close_pipes(int index, tentacle *kids_info) {
  assert(kids_info);
  int cond = 0;
  for (int i = 0; i < index; ++i)
    CALL(cond, close(kids_info[i].to_read), cond == 0, "Failed to close pipe");
  for (int i = 1; i < index; ++i)
    CALL(cond, close(kids_info[i].to_write), cond == 0, "Failed to close pipe");

  return 0;
}

//====================================================================================================================================

int first_kid_deal(tentacle *info, const char *filename) {
  assert(info);

  int kid_to_parent[2] = {};
  int cond = 0;
  int key = 0;
  int shmid = 0;
  int fileid = 0;

  CALL(fileid, open(filename, O_RDONLY), fileid > -1,
       "Failed to open argumented file");
  CALL(cond, pipe(kid_to_parent), cond == 0, "Failed to get pipe");
  CALL(cond, fork(), cond >= 0, "Failed to fork");
  CALL(key, ftok(filename, 1), key != -1, "Failed to get key of the process");
  CALL(shmid, shmget(key, 3 * sizeof(unsigned long long), IPC_CREAT | 0660),
       shmid != -1, "Failed to get shared memory segment");
  CALL(TRANSFER_INFO, shmat(shmid, NULL, 0), TRANSFER_INFO != (void *)-1,
       "Failed to mount shared memory");
  memset(TRANSFER_INFO, 0, 3 * sizeof(unsigned long long));

  if (cond == 0) {
    close(kid_to_parent[READ]);
    tentacle_in send = {
        .to_read = fileid, .to_write = kid_to_parent[WRITE], .index = 0};
    tentacle_proceed(send);
  }

  close(kid_to_parent[WRITE]);
  close(fileid);
  info->procid = cond;
  info->to_write = -1;
  info->to_read = kid_to_parent[READ];
  info->index = 0;

  return 0;
}

//====================================================================================================================================

#undef F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE abort();

#undef DEBUG

void tentacle_proceed(tentacle_in info) {
  // OUT2("CHILD %d, PID = %d READY\n", info.index, getpid());
  prctl(PR_SET_PDEATHSIG, SIGTERM, 0, 0, 0);
  char buf[BUFSIZE];
  int cond = 0;
  if (info.index != 0)
    while (1) {

      cond = read(info.to_read, buf, BUFSIZE);
      OUT2("[KID %d]  READ    %d bytes\n", info.index, cond);
      if (cond <= 0)
        abort();
      cond = write(info.to_write, buf, cond);
      if (cond <= 0)
        pause();
      OUT2("[KID %d]  WRITTEN %d bytes\n", info.index, cond);
    }
  while (1) {
    OUT4("[KID %d]  SCANNED = %llu, WRITTEN = %llu, FINISHED = %llu\n",
         info.index, TRANSFER_INFO[SCANNED], TRANSFER_INFO[WRITTEN],
         TRANSFER_INFO[FINISHED]);
    CALL(cond, read(info.to_read, buf, BUFSIZE), cond >= 0,
         "Child failed to read");

    OUT2("[KID %d]  READ    %d bytes\n", info.index, cond);
    TRANSFER_INFO[SCANNED] += cond;
    if (cond == 0) {

      TRANSFER_INFO[FINISHED] = 1;
      OUT4("[KID %d]  SCANNED = %llu, WRITTEN = %llu, FINISHED = %llu\n",
           info.index, TRANSFER_INFO[SCANNED], TRANSFER_INFO[WRITTEN],
           TRANSFER_INFO[FINISHED]);
      OUT1("[KID %d]  FINISHED READING\n", info.index);
      pause();
    }

    CALL(cond, write(info.to_write, buf, cond), cond > 0,
         "Child failed to write");
    OUT2("[KID %d]  TRANSFER_INFO[WRITTEN] %d bytes\n", info.index, cond);
  }
}
#undef F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE return -1;
#define DEBUG

//====================================================================================================================================

int get_long(long *save, const char *str) {
  assert(save);
  int base = 10;
  char *endptr = NULL;

  long val = strtol(str, &endptr, base);

  if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN)) ||
      (errno != 0 && val == 0)) {
    return -1;
  }

  if (endptr == str)
    return -1;

  *save = val;
  return 0;
}
