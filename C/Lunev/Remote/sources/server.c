#include "../include/iv_remote.h"
#include "../include/iv_standard.h"
#include "../include/ivmatrix.h"

void thread_sigusr1_handler(int sigid);

int thread_sigusr1_set();

int iv_getlong(long *save, const char *str);

int solver(int sk, int sem_blocker, int threads, matrix *cur, pthread_t beater);

int get_args(int argc, char const *argv[]) {
  long res = 0;
  int cond = 0;
  if (argc != 3)
    return SV_ARGS_INVALNUM;

  cond = iv_getlong(&res, argv[2]);

  if (cond != 0) {
    if (strcmp(argv[2], "auto") == 0)
      return 0;
    return SV_ARGS_INVALARG;
  }

  if (res >= MAXPROC)
    return SV_ARGS_TOOBIG;
  else if (res <= 0)
    return SV_ARGS_TOOSMALL;
  return (int)res;
}

int get_nthread(int argc, char const *argv[]) {
  int nthread = 0;
  nthread = get_args(argc, argv);
  if (nthread < 0) {
    print_error(nthread);
    fprintf(stderr, "%d\n", nthread);
    return -1;
  }

  if (nthread == 0)
    nthread = sysconf(_SC_NPROCESSORS_ONLN); //! Getting online
                                             //! cores number
  return nthread;
}

int handshake_setsocket(int sk) {
  const int is_reuse = 1;
  int cond = 0;
  struct timeval timeout = {.tv_sec = HNDSK_TMOUT_SEC, .tv_usec = 0};
  cond = setsockopt(sk, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
  if (cond == -1) {
    print_error(SV_SETSOCK_FAIL);
    goto fail;
  }
  cond = setsockopt(sk, SOL_SOCKET, SO_REUSEADDR, &is_reuse, sizeof(is_reuse));
  if (cond == -1) {
    print_error(SV_SETSOCK_FAIL);
    goto fail;
  }
  return 0;
fail:
  return -1;
}

void *handshake(void *arg) {
  int sk = 0, cond = 0, got = 0;
  char buf[HND_BUFSIZE];
  struct sockaddr_in addr = {}, clt_addr = {};
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  addr.sin_port = htons(HANDSHAKE_PORT);

  unsigned clt_add_len = sizeof(struct sockaddr_in);

  sk = socket(PF_INET, SOCK_DGRAM, 0);
  if (sk == -1) {
    print_error(SV_GETSOCK_FAIL);
    goto fail;
  }
  cond = handshake_setsocket(sk);
  if (cond == -1) {
    print_error(SV_HNDSK_FAIL);
    goto fail;
  }
  cond = bind(sk, (struct sockaddr *)&addr, sizeof(addr));
  if (cond == -1) {
    print_error(SV_BIND_FAIL);
    goto fail;
  }
  //        while (1) {
  fprintf(stderr, "Handshaker acting...\n");
  got = recvfrom(sk, buf, sizeof(buf), 0, (struct sockaddr *)&clt_addr,
                 &clt_add_len);
  if (got == -1) {
    print_error(SV_RECV_FAIL);
    goto fail;
  }

  fprintf(stderr, "port = %d, addr = %s\n", ntohs(clt_addr.sin_port),
          inet_ntoa(clt_addr.sin_addr));
  // inet_aton(buf, &(clt_addr.sin_addr));
  clt_addr.sin_port = htons(HANDSHAKE_PORT);

  cond = sendto(sk, buf, got, 0, (struct sockaddr *)&clt_addr, clt_add_len);
  fprintf(stderr, "Sent %d bytes\n", cond);
  perror("");
  //        }
  pthread_exit(NULL);
fail:
  close(sk);

  pthread_exit((void *)-1);
}

int handshaker_set(pthread_t *to_save) {
  pthread_t handshaker;
  int cond = 0;

  cond = pthread_create(&handshaker, NULL, handshake, NULL);
  if (cond != 0) {
    print_error(SV_HND_CRTFAIL);
    return -1;
  }
  pthread_detach(handshaker);
  *to_save = handshaker;
  return 0;
}

int get_listen_socket(int *sk_tosave) {
  struct sockaddr_in addr = {};
  int sk = 0, cond = 0, is_reuse = 1;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  addr.sin_addr.s_addr = htonl(INADDR_ANY);

  sk = socket(PF_INET, SOCK_STREAM, 0);
  if (sk == -1)
    goto fail;
  if (setsockopt(sk, SOL_SOCKET, SO_REUSEADDR, &is_reuse, sizeof(is_reuse)) ==
      -1)
    goto fail;
  cond = bind(sk, (struct sockaddr *)&addr, sizeof(addr));
  if (cond == -1)
    goto fail;
  if (cond == -1) {
    print_error(SV_SETSOCK_FAIL);
    goto fail;
  }
  *sk_tosave = sk;
  return 0;
fail:
  if (sk > 0)
    close(sk);
  return -1;
}

int get_client_socket(int sk_listen, struct sockaddr_in *addr) {
  int client = 0, cond = 0, is_reuse = 1;
  unsigned size = sizeof(addr);

  client = accept(sk_listen, (struct sockaddr *)addr, &size);
  if (client <= 0) {
    print_error(SV_ACCEPT_FAIL);
    goto fail;
  }

  cond =
      setsockopt(client, SOL_SOCKET, SO_REUSEADDR, &is_reuse, sizeof(is_reuse));
  if (cond == -1)
    goto fail;
  if (set_default_timeouts(client) != 0)
    goto fail;

  return client;
fail:
  if (client > 0)
    close(client);
  return -1;
}

int get_socket(int *sk_tosave) {
  struct sockaddr_in addr = {};
  int sk = 0, cond = 0, client = 0;

  cond = get_listen_socket(&sk);
  if (cond == -1) {
    print_error(SV_GETSOCK_FAIL);
    goto fail;
  }
  cond = listen(sk, SOMAXCONN);
  if (cond == -1) {
    print_error(SV_SETSOCK_FAIL);
    goto fail;
  }

  client = get_client_socket(sk, &addr);
  if (client == -1) {
    print_error(SV_GETSOCK_FAIL);
    goto fail;
  }

  close(sk);
  *sk_tosave = client;
  return 0;

fail:
  if (sk > 0)
    close(sk);
  if (client > 0)
    close(client);
  return -1;
}

int matrix_get(int sk, matrix *cur) {
  matrix this;
  int cond = 0;
  char *data = 0;
  cond = tcp_srecv(sk, (char *)&this, sizeof(this));
  if (cond != 0) {
    print_error(NEUTRAL_ERROR);
    goto fail;
  }
  fprintf(stderr, "Received matrix structure\n");

  data = (char *)malloc(this.size * this.size * sizeof(double));
  if (data == NULL) {
    print_error(SV_ALLOC_FAIL);
    goto fail;
  }

  cond = tcp_srecv(sk, data, this.size * this.size * sizeof(double));
  if (cond != 0) {
    print_error(NEUTRAL_ERROR);
    goto fail;
  }
  fprintf(stderr, "Received matrix data\n");

  this.data = data;
  *cur = this;
  return 0;

fail:
  if (data) {
    free(data);
    data = NULL;
  }
  return -1;
}

void *beater_routine(void *arg) {
  sv_answer wait = {.status = SV_ANSWER_WAIT};
  beater_meta meta = *(beater_meta *)arg;
  int sk = meta.sk;
  int sem = meta.sem;
  int ret = 0;
  struct sembuf zero = {0, 0, 0};
  semop(sem, &zero, 1);
  while (1) {
    ret = tcp_ssend(sk, (char *)&wait, sizeof(wait));
    fprintf(stderr, "Beat sent\n");
    if (ret == -1)
      return (void *)-1;
    sleep(BEAT_TIMEOUT);
    semop(sem, &zero, 1);
  }
}

int beater_sem_get() {
  int sem = semget(IPC_PRIVATE, 1, 0666);
  union semun set;
  if (sem == -1) {
    print_error(NEUTRAL_ERROR);
    return -1;
  }
  set.val = 1;
  semctl(sem, 0, SETVAL, set);
  return sem;
}

int beater_sem_manipulate(int sem, int val) {
  struct sembuf s = {0, (short)val, 0};
  semop(sem, &s, 1);
  return sem;
}

int beater_block(int sem) { return beater_sem_manipulate(sem, 1); }

int beater_unblock(int sem) { return beater_sem_manipulate(sem, -1); }

int server(int argc, char const *argv[]) {
  int nthread = 0, cond = 0, sk = 0, sem_blocker = 0;
  matrix cur = {};
  pthread_t handshaker = {0}, beater = {0};
  nthread = get_nthread(argc, argv);
  beater_meta meta = {0};
  if (nthread == -1) {
    goto fail;
  }
  fprintf(stderr, "%d cores measured\n", nthread);
  cond = handshaker_set(&handshaker);
  fprintf(stderr, "Handshaker activated\n");
  if (cond == -1)
    goto fail;
  cond = get_socket(&sk);
  if (cond == -1) {
    print_error(SV_GETSOCK_FAIL);
    goto fail;
  }
  fprintf(stderr, "Got main socket\n");
  cond = matrix_get(sk, &cur);
  if (cond == -1) {
    print_error(SV_MATRIX_GET_FAIL);
    goto fail;
  }
  fprintf(stderr, "Received matrix from client\n");
  sem_blocker = beater_sem_get();
  if (sem_blocker == -1) {
    print_error(NEUTRAL_ERROR);
    goto fail;
  }
  meta.sk = sk;
  meta.sem = sem_blocker;

  cond = pthread_create(&beater, NULL, beater_routine, &meta);
  if (cond == -1) {
    print_error(NEUTRAL_ERROR);
    goto fail;
  }
  pthread_detach(beater);
  fprintf(stderr, "Beater created\n");

  cond = solver(sk, sem_blocker, nthread, &cur, beater);
  if (cond != 0) {
    print_error(NEUTRAL_ERROR);
    goto fail;
  }

  matrix_kill(&cur);

  pthread_cancel(beater);
  pthread_cancel(handshaker);
  semctl(sem_blocker, 0, IPC_RMID);
  return 0;
fail:
  if (sk > 0)
    close(sk);
  if (sem_blocker > 0)
    semctl(sem_blocker, 0, IPC_RMID);
  matrix_kill(&cur);
  pthread_cancel(beater);
  pthread_cancel(handshaker);
  fprintf(stderr, "Critical server error occured\n");
  return -1;
}

int solver(int sk, int sem_blocker, int threads, matrix *cur,
           pthread_t beater) {
  uint32_t temp = 0;
  double result = 0;
  matrix *minor = 0;
  sv_answer answer = {};
  int ret = 0;
  fprintf(stderr, "Solver began to execute\n");
  if (tcp_srecv(sk, (char *)&temp, sizeof(temp)) == -1) {
    print_error(NEUTRAL_ERROR);
    DP(1);
    return -1;
  }
  fprintf(stderr, "Got request from client\n");
  while (temp != FIN) {
    fprintf(stderr, "Calculating task...\n");
    beater_unblock(sem_blocker);
    fprintf(stderr, "Beater unlocked\n");
    minor = get_minor(cur, 0, temp);
    if (minor == NULL) {
      print_error(NEUTRAL_ERROR);
      DP(1);
      goto fail;
    }

    ret = get_matrix_determinant(minor, threads, &result);
    beater_block(sem_blocker);
    fprintf(stderr, "Beater locked\n");
    if (ret != 0) {
      print_error(NEUTRAL_ERROR);
      DP(1);
      goto fail;
    }
    answer.status = SV_ANSWER_VAL;
    answer.val = result * ELEM(cur, 0, temp) * ((temp % 2 == 0) ? 1.0 : -1.0);
    if (tcp_ssend(sk, (char *)&answer, sizeof(answer)) == -1) {
      print_error(NEUTRAL_ERROR);
      DP(1);
      goto fail;
    }
    fprintf(stderr, "Sent result to client\n");
    matrix_kill(minor);
    free(minor);
    minor = NULL;
    if (tcp_srecv(sk, (char *)&temp, sizeof(temp)) == -1) {
      print_error(NEUTRAL_ERROR);
      DP(1);
      goto fail;
    }
    fprintf(stderr, "Got request from client\n");
  }

  return 0;
fail:

  if (minor) {
    matrix_kill(minor);
    free(minor);
  }
  answer.status = SV_ANSWER_ERR;
  tcp_ssend(sk, (char *)&answer, sizeof(answer));
  return -1;
}
