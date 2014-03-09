#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>



#define DBL_IS_ZERO(arg) (fabs(arg) < DBL_EPSILON) 

#define CREATE_MATRIX(matrix, n)																								\
	double** matrix = (double **) calloc(n, sizeof(double*));																	\
	VERIFY(matrix);																												\
    for (int i = 0; i < n; ++i)																									\
	{																															\
			matrix[i] = (double *)calloc(n, sizeof(double));																	\
			VERIFY(matrix);																										\
	}

//----------------------------------------------------------------------------------------------------------------------------

#define PRINT_MATRIX(matrix,edge)																								\
	{																															\
		for (int i = 0; i < edge; ++i)																							\
		{																														\
			for (int j = 0; j < edge; ++j)	printf("%lg ", matrix[i][j]);														\
			putchar('\n');																										\
		}																														\
	putchar('\n');																												\
	}

//----------------------------------------------------------------------------------------------------------------------------

#define COPY_MATRIX(to, from, n)																								\
	for (int i = 0; i < n; ++i)																									\
		for (int j = 0; j < n; ++j)																								\
		{																														\
			ASSERT(i >= 0); ASSERT(i < n); ASSERT(j >= 0); ASSERT( j < n);														\
			to[i][j] = from[i][j] ;																								\
		}


//----------------------------------------------------------------------------------------------------------------------------
#define _EJC

#ifdef _EJC
	#define OUT
#else
	#define OUT if (0)
#endif

#define VERIFY(cond)																											\
	if (!(cond))																												\
			{																													\
				printf("Program %s died in battle on line %d with the mistake of (%s)", __FILE__, __LINE__, #cond);				\
				abort();																										\
			}

//----------------------------------------------------------------------------------------------------------------------------

#define DEBUG 0

#if (DEBUG == 1)
	#define DEBUG_OUT
	#define ASSERT(cond)																									\
	
#else
	#define DEBUG_OUT if (0)
	#define ASSERT(cond) VERIFY(cond)
#endif

//----------------------------------------------------------------------------------------------------------------------------

double determinant(double** matrix, const int EDGE);