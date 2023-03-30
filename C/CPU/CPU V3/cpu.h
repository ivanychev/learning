#define _CRT_SECURE_NO_WARNINGS
// #define _TX_ALLOW_TRACE

#include "string.h"
#include <assert.h>
#include <float.h>
#include <math.h>
#include <memory.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
// #include "command_codes.h"

#define IS_ZERO(x) (fabs(x) < EPSILON) // DBL_EPSILON fucks up

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
(for now) 4 registers
**/

const int MAXCODES = 1000;

typedef struct {
  stack *cpu_stack;
  double ax, bx, cx, dx, sys_reg;
  stack *func_stack;
  double memory[MAXCODES];
  int siz_mem;
  int cur;
} cpu;

stack *stack_construct(int size);

const int NAME_LEN = 15;

/**
                pointer			structure with MARK - the integer
pointer itself and NAME - name of mark
**/
typedef struct pointer_s {
  int mark;
  char name[NAME_LEN];
} pointer;

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

int cpu_check(cpu *my_cpu, FILE *strerr);

int cpu_push(cpu *my_cpu, int push_arg, ...);

int cpu_pop(cpu *my_cpu, int pop_arg, double *return_value);

int cpu_in(cpu *my_cpu, int in_arg);

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

int cpu_mov(cpu *my_cpu, int mov_arg, int mov_arg2, ...);

int cpu_out(FILE *fo, FILE *strerr, cpu *my_cpu, int out_arg, ...);

int cpu_swap(cpu *my_cpu);

int cpu_dub(cpu *my_cpu);

int cpu_jbe(cpu *my_cpu, int ptr);

int cpu_jb(cpu *my_cpu, int ptr);

int cpu_jae(cpu *my_cpu, int ptr);

int cpu_ja(cpu *my_cpu, int ptr);

int cpu_je(cpu *my_cpu, int ptr);

int cpu_jmp(cpu *my_cpu, int ptr);

int cpu_load(cpu *my_cpu, FILE *strbin);

int cpu_ret(cpu *my_cpu);
//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

int cpu_core(FILE *strout, FILE *strerr, cpu *my_cpu, double *value,
             int (*error_catcher)(FILE *strerr, cpu *my_cpu, int error_code));

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

int plot(char *input_stream, char *output_stream, char *error_stream,
         cpu *my_cpu, double x_begin, double x_end, double dx, double ymin,
         double ymax, int display_width, int display_height);

//--------------------ASSEMBLER-----------------------------------------
double *assemble(FILE *strin, FILE *strerr, pointer *pts,
                 int (*error_catcher)(FILE *strerr, int cond));

int asm_main();

int asm_is_mrk(FILE *strin, FILE *strerr, char *word, int *cur_code,
               pointer *pts, int (*error_catcher)(FILE *strerr, int cond));

int asm_mark(char *word, int cur_code, pointer *pts);

int asm_cmd_convert(const char *word, int *c);

int asm_push_code(double *codes, int *cur_code, double value);

int asm_str_convert(char *word, double *reg);

int asm_cmd_push(FILE *strin, double *codes, int *cur_code);

int asm_str_convert(char *word, double *reg);

int asm_cmd_in(FILE *strin, double *codes, int *cur_code);

int asm_cmd_pop(FILE *strin, double *codes, int *cur_code);

int asm_cmd_out(FILE *strin, double *codes, int *cur_code);

int asm_cmd_mov(FILE *strin, double *codes, int *cur_code);

int asm_cmd_jump_like(FILE *strin, double *codes, int *cur_code, const int arg,
                      pointer *pts);

int asm_error_catcher(FILE *strerr, int cond);
