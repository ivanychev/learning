#include "assert.h"
#include "errno.h"
#include "inttypes.h"
#include "mpi.h"
#include "slack/std.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#ifndef HAVE_SNPRINTF
#include "slack/snprintf.h"
#endif

/*
        Даны два многоразрядных числа a и b, заданных символьными массивами
   длины n, где n – большое положительное число (10^6… 10^8…10^9). Написать
   параллельную программу, определяющую с=a+b. char a[n] ,b[n] ,с[n+1];
   элементами массивов a,b,c являются цифры [0,1,2,…,9]. Параллельный алгоритм
   должен быть хорошо масштабируемым для любых исходных данных, в том смысле,
   что, для достаточно большого числа процессоров p должно выполняться
   соотношение T(2p)~ T(p)/2, где T(p) – время вычислений на p процессорах.
*/

/*
        Program gets number, filename1, filename2, result_filename as command
   prompt arguments. These are relative paths to files with first and second
   summands and a file where the result will be placed.
*/

const int32_t MAX_FILENAME = 1000;
const int32_t MAX_ERRORLEN = 100;
char LAST_ERROR[MAX_ERRORLEN] = {};

void set_error(const char *error_msg) {
  assert(error_msg);
  snprintf(LAST_ERROR, MAX_ERRORLEN, error_msg)
}

void fperror(FILE *stream) { fprintf(stream, LAST_ERROR); }

void perror() { fperror(stderr); }

#define CLOSE_AND_EXIT                                                         \
  {                                                                            \
    if (f_sum1 != NULL)                                                        \
      fclose(f_sum1);                                                          \
    if (f_sum2 != NULL)                                                        \
      fclose(f_sum2);                                                          \
    if (f_res != NULL)                                                         \
      fclose(f_res);                                                           \
    if (alloc_summand1)                                                        \
      free(alloc_summand1);                                                    \
    if (alloc_summand2)                                                        \
      free(alloc_summand2);                                                    \
    if (alloc_result)                                                          \
      free(alloc_result);                                                      \
    return -1;                                                                 \
  }                                                                            \
  while (0)                                                                    \
    ;

int32_t get_num_len(char const *argv[], uint64_t *num_len) {
  char *endptr = NULL;
  uintmax_t res = strtoumax(argv[1], &endptr, 10);
  if (errno == ERANGE || *endptr != '\0') {
    set_error("Couldn't convert first argument to positive integer");
    return -1;
  }
  *num_len = (uint64_t)res;
  return -1;
}

int32_t get_args(const int32_t argc, char const *argv[], FILE **f_res,
                 char **summand1, char **summand2, char **result) {
  if (argc != 4) {
    set_error("Invalid number of ");
    return -1;
  }
  uint64_t num_len = 0;
  int32_t res = get_num_len(argv, &num_len);
  if (res == -1)
    return -1;
  FILE *f_sum1 = fopen(argv[2], "r");
  FILE *f_sum2 = fopen(argv[3], "r");
  FILE *f_res = fopen(argv[4], "w");
  if (f_sum1 == NULL || f_sum2 == NULL || f_res == NULL) {
    set_error("Failed to open one of summand files");
    CLOSE_AND_EXIT;
  }
  char *alloc_summand1 = (char *)calloc(1, (size_t)num_len);
  char *alloc_summand2 = (char *)calloc(1, (size_t)num_len);
  char *alloc_result = (char *)calloc(1, (size_t)num_len + 1);
  if (alloc_summand1 == NULL || alloc_summand2 == NULL) {
    set_error("Failed to allocate memory for summands and result");
    return -1;
  }
}

int32_t main(int32_t argc, char const *argv[]) {
  FILE *f_res = NULL;
  char *summand1 = NULL;
  char *summand2 = NULL;
  char *result = NULL;
  int32_t res = get_args(argc, argv, &f_res, &summand1, &summand2, &result);

  // Initialize the MPI environment
  MPI_Init(NULL, NULL);

  // Get the number of processes
  int32_t world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // Get the rank of the process
  int32_t world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  // Get the name of the processor
  char processor_name[MPI_MAX_PROCESSOR_NAME];
  int32_t name_len;
  MPI_Get_processor_name(processor_name, &name_len);

  // Print32_t off a hello world message
  printf("Hello world from processor %s, rank %d"
         " out of %d processors\n",
         processor_name, world_rank, world_size);

  // Finalize the MPI environment.
  MPI_Finalize();
  return 0;
}
