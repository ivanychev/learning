#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
  int i = 0;
  char **copy_argv = calloc(argc - 1, sizeof(char *));
  for (i = 0; i < argc - 1; i++)
    copy_argv[i] = argv[i + 1];
  int cond = execvp(argv[0], copy_argv);

  printf("EXEC returned, something bad happened\n");
  return 0;
}