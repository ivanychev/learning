#include "omp.h"
#include "stdio.h"

int main() {
#pragma omp parallel
  {
    int nthreads = omp_get_num_threads();
    int rank = omp_get_thread_num();
    printf("Hello, World.\nnthreads = %d, rank = %d\n", nthreads, rank);
  }
  return 0;
}
