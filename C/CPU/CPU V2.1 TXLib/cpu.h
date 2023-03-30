#define _CRT_SECURE_NO_WARNINGS
#define _TX_ALLOW_TRACE

#include "TXLib_102.h"
#include "string.h"
#include <float.h>
#include <math.h>
#include <memory.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

enum errors {
  OK = 0,
  ERR_INIT = 1,
  ERR_NULL = 2,
  ERR_WRONG_SZ = 3,
  ERR_PRINT = 4
};

enum cpu_errors {
  // CPU_ERROR_NULL = 1100,
  CPU_CHECK_NULL = 1101,
  CPU_CHECK_OK = 1102,
  CPU_CHECK_INV_STACK = 1103,
  CPU_ERROR_STACK_FULL = 1104,
  CPU_ERROR_STACK_EMPTY = 1105,
  CPU_OK = 1106,
  CPU_PUSH_INV_TOKEN = 1107,
  CPU_BROKEN_START = 1108,
  CPU_BROKEN_FINISH = 1109,
  CPU_NOT_ENOUGH_ARGS = 1110,
  CPU_POP_VALUE_NULL = 1111,
  CPU_ERROR_DIV_BY_ZERO = 1112,
  CPU_ERROR_NEGATIVE_BASE = 1113,
  CPU_ERROR_SQRT_NEGATIVE = 1114,
  CPU_ERROR_CATCHER_OK = 1115,
  CPU_ERROR_CATCHER_BAD = 1116,
  CPU_ERROR_PUSH_BAD_TOKEN = 1117,
  CPU_OUT_STREAM_IN_NULL = 1118,
  CPU_OUT_STREAM_OUT_NULL = 1119,
  CPU_OUT_BAD_TOKEN = 1120,
  CPU_OUT_STREAM_ERROR_NULL = 1121,
};

enum draw_conditions {
  DRAW_BAD = 1301,
  DRAW_OK = 1302,
};

enum calc_errors {
  CALC_BAD = 1201,
  CALC_OK = 1202,
};

const int CPU_STACK_SIZE = 10;

const int POISON = 666;

#define IS_ZERO(x) (fabs(x) < 0.000000000001) // DBL_EPSILON fucks up

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

#define _EJC

#ifdef _EJC
#define OUT
#else
#define OUT if (0)
#endif

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

#define VERIFICATIONS 1

#ifndef VERIFICATIONS
#error You should define VERIFICATIONS as 0 or 1.
#endif

#if (VERIFICATIONS == 1)
/*	#define VERIFY(cond)
   \
                if ((cond) == false)
   \
                                {
   \
                                        printf("Program %s died in battle on
   line %d with the mistake of (%s)", __FILE__, __LINE__, #cond);
   \
                                        abort();
   \
                                }
                                */
#define VERIFY(cond)                                                           \
  if (!(cond)) {                                                               \
    printf("Program %s died in battle on line %d with the mistake of (%s)",    \
           __FILE__, __LINE__, #cond);                                         \
    abort();                                                                   \
  }
#else
#define VERIFY(cond)
#endif

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

#define DEBUG 1

#ifndef DEBUG
#error You should define DEBUG as 0 or 1.
#endif

#if (DEBUG == 0)
#define DEBUG_OUT if (0)
#define ASSERT(cond)

#else
#define DEBUG_OUT
#define ASSERT(cond) VERIFY(cond)
#endif

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

#define ARR_ASSERT(i, left, right)                                             \
  if (!(((left) <= (i)) && ((i) <= (right)))) {                                \
    printf("Program %s crashed, Array index is out of range, Line %d",         \
           __FILE__, __LINE__);                                                \
    abort();                                                                   \
  }

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

/**
                stack			type defines stack itself, which works
in "First in, first one" way

                @par			(WIKIPEDIA) In computer science, a stack
is a particular kind of abstract data type\ or collection in which the principal
(or only) operations on the collection are the addition of an entity to the
collection, known as push and removal of an entity, known as pop
**/
typedef struct {
  int maxsize;  //!<	maximum size of stack
  double *data; //!<	pointer to data set
  int size;     //!<    current size of stack
} stack;

/**
                cpu				this struct includes stack and
(for now) one register
**/
typedef struct {
  stack *cpu_stack;
  double ax, bx, cx, dx;
} cpu;

stack *stack_construct(int size);

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

double stack_pop(stack *user_stack);

void stack_push(stack *user_stack, double input);

int stack_full(stack *user_stack);

int stack_empty(stack *user_stack);

int stack_ok(stack *user_stack);

int stack_destruct(stack *user_stack);

int stack_print(stack *user_stack);

int stack_dump(FILE *stream, stack *user_stack);

int system_out(stack *user_stack);

int stack_err_catch(int error_code, char *string, ...);

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

cpu *cpu_construct(int stack_size);

void cpu_destruct(cpu *my_cpu);

int cpu_check(cpu *my_cpu);

int cpu_push(cpu *my_cpu, char *input);

int cpu_pop(cpu *my_cpu, double *return_value);

int cpu_add(cpu *my_cpu);

int cpu_mul(cpu *my_cpu);

int cpu_sub(cpu *my_cpu);

int cpu_div(cpu *my_cpu);

int cpu_sin(cpu *my_cpu);

int cpu_cos(cpu *my_cpu);

int cpu_tan(cpu *my_cpu);

int cpu_sqrt(cpu *my_cpu);

int cpu_pow(cpu *my_cpu);

int cpu_catch_error(FILE *stream, cpu *my_cpy, int condition);

int cpu_dump(FILE *stream, cpu *my_cpu);

int cpu_mov_ax(cpu *my_cpu, double value);

int cpu_space(FILE *stream, cpu *my_cpu);

int cpu_enter(FILE *stream, cpu *my_cpu);

int cpu_tab(FILE *stream, cpu *my_cpu);

int cpu_out(FILE *fi, FILE *fo, FILE *strerr, cpu *my_cpu);

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

int calculator(FILE *strin, FILE *strout, FILE *strerr, cpu *my_cpu,
               double *value,
               int (*error_catcher)(FILE *strerr, cpu *my_cpu, int error_code));

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

int plot(char *input_stream, char *output_stream, char *error_stream,
         cpu *my_cpu, double x_begin, double x_end, double dx, double ymin,
         double ymax, int display_width, int display_height);
