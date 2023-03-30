/**
        @file			main.c
        @mainpage
        @date			10.03.2013
        @author			Sergey Ivanychev <sergeyivanychev@gmail.com>,
376 group, DCAM MIPT
        @version		1.00

        @par			This program calculates the determinant of NxN
matrix
        @				matrix_header.h must be connected
**/

#include "matrix_header.h"

/**
                main			request N and matrix of float numbers,
prints determinant
                @return			0 if arguments are correct, otherwise -1
**/
int main() {
  const long fake = 1200000000;
  OUT printf(
      "# Hello, world! I was built in %s %s\n"
      "# I have been developed by Ivanychev Sergey and it's 1.00 version\n"
      "# There's a code of mine in %s\n"
      "# I can calculate the determinant of any matrix\n"
      "# Type the size of it (edge) and then type the float matrix's numbers "
      "using SPACEs and ENTERs\n"
      "# Please, type the size\n",
      __DATE__, __TIME__, __FILE__);
  int n = 0;
  int ret = scanf("%d", &n);

  if (!(ret)) {
    OUT printf("Bad argument, program terminated");
    return -1;
  }

  OUT printf("# OK, Type the matrix below\n");

  CREATE_MATRIX(data, n);
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      scanf("%lg", &data[i][j]);
  /*
          OUT
          {
                  for (long i = 0; i < fake; ++i);
                  OUT printf("# Analysing input...\n");
                  for (long i = 0; i < fake; ++i);
                  OUT printf("# 33 percent completed\n");
                  for (long i = 0; i < fake; ++i);
                  OUT printf("# 66 percent completed\n");
                  for (long i = 0; i < fake; ++i);
                  OUT printf("# 99 percent completed\n");
                  for (long i = 0; i < fake / 2; ++i);
                  OUT printf("# OH, there's a bug. Rewriting the source
     code...\n"); for (long i = 0; i < fake; ++i); OUT printf("# All mistake are
     corrected. Compiling...\n"); for (long i = 0; i < fake; ++i); OUT printf("#
     Linking...\n"); for (long i = 0; i < fake; ++i); OUT printf("#
     Optimizing...\n"); for (long i = 0; i < fake; ++i); OUT printf("# Build
     completed, restoring the input...\n"); for (long i = 0; i < fake; ++i); OUT
     printf("# Analyzing...\n"); for (long i = 0; i < fake; ++i); OUT printf("#
     33 percent completed\n"); for (long i = 0; i < fake; ++i); OUT printf("# 66
     percent completed\n"); for (long i = 0; i < fake; ++i); OUT printf("# 99
     percent completed\n"); for (long i = 0; i < fake / 2; ++i); OUT printf("#
     WHAT THE HELL! THE SAME MISTAKE!!\n"); for (long i = 0; i < 1.5 * fake ;
     ++i); OUT printf("# Ignoring...\n"); for (long i = 0; i < fake ; ++i); OUT
     printf("# Building the pointer of pointer array...\n"); for (long i = 0; i
     < fake ; ++i); OUT printf("# Function connected. Calculating...\n"); for
     (long i = 0; i < fake ; ++i); OUT printf("# Completed.\n"); for (long i =
     0; i < 1000000; ++i); OUT printf("# Trying to return to the main
     function\n"); for (long i = 0; i < fake ; ++i); OUT printf("#
     Completed.\n"); for (long i = 0; i < 1000000; ++i); OUT printf("# Checking
     the answer...\n"); for (long i = 0; i < fake; ++i); OUT printf("# Looks
     fine, here it is\n\n"); for (long i = 0; i < 1.5 * fake; ++i); OUT
     printf("# Where's it?\n"); for (long i = 0; i < fake; ++i); OUT printf("#
     Oh, that's it, sorry\n"); for (long i = 0; i < fake; ++i);
          }
  */
  DEBUG_OUT PRINT_MATRIX(data, n);
  double det = determinant(data, n);

  printf("\n%lg\n", det);

  free(data);
  return 0;
}

/*
#define SCAN_MATRIX(matrix, n)
\
        for (int i = 0; i < n; ++i)
\ for (int j = 0; j < n; ++j) scanf("%lg", &matrix[i][j]);

#define DBL_IS_ZERO(arg) (fabs(arg) < DBL_EPSILON)

#define CREATE_MATRIX(matrix, n)
\
        double** matrix = (double **) calloc(n, sizeof(double*));
\ for (int i = 0; i < n; ++i) matrix[i] = (double *)calloc(n, sizeof(double));

#define PRINT_MATRIX(matrix,edge)
\
        {
\
                for (int i = 0; i < edge; ++i)
\
                {
\
                        for (int j = 0; j < edge; ++j) printf("%lg ",
matrix[i][j]);
\
                        putchar('\n');
\
                }
\
        putchar('\n');
\
        }

#define COPY_MATRIX(to, from, n)
\
        for (int i = 0; i < n; ++i)
\
                for (int j = 0; j < n; ++j)
\
                {
\
                        ASSERT(i >= 0); ASSERT(i < n); ASSERT(j >= 0); ASSERT( j
< n);
\
                        to[i][j] = from[i][j] ;
\
                }

#define _EJC

#ifdef _EJC
        #define OUT printf(
#else
        #define _OUT (
#endif

#define DEBUG 0

#if (DEBUG == 1)
        #define DEBUG_OUT
        #define ASSERT(cond)
\
        if (!(cond))
\
                {
\
                        printf("Program %s died in battle on line %d with the
mistake of (%s)", __FILE__, __LINE__, #cond);				\
                        abort();
\
                }
#else
        #define DEBUG_OUT if (0)
        #define ASSERT(cond)
#endif
*/

/*double det(double** matrix, const int EDGE)
{
    if (!(EDGE)) return 0.0;
        //double** copy_matrix = (double **)calloc(EDGE, sizeof(double*));
        //for (int i = 0; i < EDGE; ++i) copy_matrix[i] = (double *)
calloc(EDGE, sizeof (double)); CREATE_MATRIX(copy_matrix, EDGE);

    ASSERT(matrix);
        ASSERT(copy_matrix);

        COPY_MATRIX(copy_matrix, matrix, EDGE);


    for (int i = 0; i < EDGE; ++i)
    {
        ASSERT(i >= 0); ASSERT(i < EDGE);
                if (copy_matrix[i][i] == 0)
            {
                for (int j = i+1; j < EDGE; ++j)
                                {
                                        ASSERT(j >= 0); ASSERT( j < EDGE);

                                        if (copy_matrix[j][i] != 0)
                    {
                        for (int k = 0; k < EDGE; ++k) copy_matrix[i][k] +=
copy_matrix[j][k]; DEBUG_OUT PRINT_MATRIX(copy_matrix, EDGE); break;
                    }
                                        return 0.0;
                                }

                                DEBUG_OUT PRINT_MATRIX(copy_matrix, EDGE);
            }

                double local_factor = 0;
        for (int j = i + 1; j < EDGE; ++j)
        {
            ASSERT(i >= 0); ASSERT(i < EDGE); ASSERT(j >= 0); ASSERT( j < EDGE);
                        local_factor = copy_matrix[j][i] / copy_matrix[i][i];

                        for (int k = 0; k < EDGE; ++k) copy_matrix[j][k] -=
copy_matrix[i][k] * local_factor; DEBUG_OUT PRINT_MATRIX(copy_matrix, EDGE);
        }
    }
    double determinant = 1;
    DEBUG_OUT PRINT_MATRIX(copy_matrix, EDGE);
    for (int i = 0; i < EDGE; ++i) determinant *= copy_matrix[i][i];
    free(copy_matrix);
        if DBL_IS_ZERO(determinant) determinant = 0.0;
    return determinant;
}

*/

/*
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
*/
