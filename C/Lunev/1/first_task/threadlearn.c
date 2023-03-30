#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
// #include <pthread.h>
#include <assert.h>

#define true 1
#define false 0
#define bool int
#define SUCCESS 13
#define POISON -13

void *born_print(void *index) {
  int index_copy = 0;

  printf("Process id = [%d], number of thread = [%ld]\n", getpid(),
         (long int)index);

  return index;
}

//================================================================================
int main(int argc, char **argv) {
  int base = 10;
  char *endptr = NULL;
  char *str = NULL;
  long val = 0;

  if (argc < 2) {
    fprintf(stderr, "Usage: %s str [base]\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  str = argv[1];
  base = (argc > 2) ? atoi(argv[2]) : 10;

  errno = 0;
  val = strtol(str, &endptr, base);

  if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN)) ||
      (errno != 0 && val == 0)) {
    perror("strtol");
    exit(EXIT_FAILURE);
  }

  if (endptr == str) {
    fprintf(stderr, "No digits were found\n");
    exit(EXIT_FAILURE);
  }

  // Let's create some threads here

  pthread_t *threads = calloc(val, sizeof(pthread_t));
  void *thread_return = NULL;
  int i = 0, cond = 0;

  for (i = 0; i < val; ++i) {
    int index_copy = i;
    cond = pthread_create(&threads[i], NULL, born_print, (void *)((long int)i));

    if (cond != 0) {
      fprintf(stderr, "pthread_create() return error code [%d]\n", cond);
      exit(EXIT_FAILURE);
    }
  }

  for (i = 0; i < val; i++)
    pthread_join(threads[i], &thread_return);
  free(threads);
  return 0;
}