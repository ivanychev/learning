#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0
#define bool int

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

  // OK. We have good integer here

  int i = 0;
  bool is_child = false;
  int child_index = 0;

  int pid = 0;
  int returned_value = 0;

  for (i = 0; i < val; ++i) {
    pid = fork();
    wait(&returned_value);

    if (pid < 0) {
      fprintf(stderr, "Error occured during forking\n");
      exit(EXIT_FAILURE);
    }

    if (pid != 0)
      continue;

    child_index = i + 1;
    fprintf(stderr, "I'm %d'th process, id = [%d], parent_id = [%d]\n",
            child_index, getpid(), getppid());
    break;
  }

  return 0;
}