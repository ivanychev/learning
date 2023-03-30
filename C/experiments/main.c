// #define _POSIX_C_SOURCE
#include "assert.h"
#include "stdio.h"
#include "stdlib.h"
#include <time.h>
#include <unistd.h>

int main() {
  struct timespec temp;
  clock_gettime(CLOCK_REALTIME, &temp);
  return 0;
}