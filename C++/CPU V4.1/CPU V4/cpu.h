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
// #include <crtdbg.h>
// #include "command_codes.h"

const double EPSILON = 0.00000000001;

const int CPU_STACK_SIZE = 1000;

const int POISON = 666;

const int POISON_MARK = -228;

const int CMD_MAXLEN = 30;

const int NUM_OF_POINTERS = 1000;

const int SIZE_OF_FUNC_STACK = 1000;

const int MAXCODES = 1000;

const int MAXVARS = 50;

const int MAX_VAR_NAME = 20;

const int NUM_OF_VARS = 50;

const int LENGTH_MARKS = 50;

const int NAME_LEN = 30;

#define IS_ZERO(x) (fabs(x) < EPSILON) // DBL_EPSILON fucks up

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/*
#define _EJC

#ifdef _EJC
        #define OUT
#else
        #define OUT if (0)
#endif
*/

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

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

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#define DEBUG 1

#ifndef DEBUG
#error You should define DEBUG as 0 or 1.
#endif

#if (DEBUG == 0)
#define DEBUG_OUT if (0)
#define ASSERT(cond)
//	#define CHECK_MEMORY

#else
#define DEBUG_OUT
#define ASSERT(cond) VERIFY(cond)
#define CHECK_MEMORY // free(NULL); printf("%s %d\n", (_CrtCheckMemory() == 1)?
                     // "OK": "BAD", _CrtCheckMemory());
#endif

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#define ARR_ASSERT(i, left, right)                                             \
  if (!(((left) <= (i)) && ((i) <= (right)))) {                                \
    printf("Program %s crashed, Array index is out of range, Line %d",         \
           __FILE__, __LINE__);                                                \
    abort();                                                                   \
  }

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/**
                cpu				this struct includes stack and
(for now) 4 registers
**/

struct stack {
private:
  double *_data; //!<	pointer to data set

public:
  stack(int size);
  ~stack();
  int _size;    //!<    current size of stack
  int _maxsize; //!<	maximum size of stack
  double pop();
  void push(double input);
  int full();
  int empty();
  int ok();
  int print();
  int dump(FILE *stream);
  int error_catch(int error_code, char *string, ...);
};

struct cpu {
  stack *cpu_stack;
  double ax, bx, cx, dx, sys_reg;
  stack *func_stack;
  double memory[MAXCODES];
  double cash[MAXVARS];
  int siz_mem;
  int cur;
};

/**
                pointer			structure with MARK - the integer
pointer itself and NAME - name of mark
**/
typedef struct pointer_s {
  int mark;
  char name[NAME_LEN];
} pointer;

typedef struct var_s {
  char name[MAX_VAR_NAME];
} var;

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/**
                stack			type defines stack itself, which works
in "First in, first one" way

                @par			(WIKIPEDIA) In computer science, a stack
is a particular kind of abstract data type\ or collection in which the principal
(or only) operations on the collection are the addition of an entity to the
collection, known as push and removal of an entity, known as pop
**/

/*
double stack_pop(stack* user_stack);

void stack_push(stack* user_stack, double input);

int stack_full(stack* user_stack);

int stack_empty(stack* user_stack);

int stack_ok(stack* user_stack);

int stack_destruct(stack* user_stack);

int stack_print(stack* user_stack);

int stack_dump(FILE* stream, stack* user_stack);

int system_out(stack* user_stack);

int stack_err_catch(int error_code, char* string, ...);
*/

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

cpu *cpu_construct(int stack_size);

int cpu_def(cpu *my_cpu, int def_arg);

void cpu_destruct(cpu *my_cpu);

int cpu_check(cpu *my_cpu, FILE *strerr);

int cpu_push(cpu *my_cpu, int push_arg1, double push_arg2);

int cpu_pop(cpu *my_cpu, int pop_arg1, int pop_arg2, double *return_value);

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

//------------> TO DO FUNCTIONS

int cpu_ctan(cpu *my_cpu);

int cpu_ln(cpu *my_cpu);

int cpu_log(cpu *my_cpu);

int cpu_arcsin(cpu *my_cpu);

int cpu_arccos(cpu *my_cpu);

int cpu_arctg(cpu *my_cpu);

int cpu_exp(cpu *my_cpu);

int cpu_pow(cpu *my_cpu);

int cpu_fac(cpu *my_cpu);

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

int cpu_core(FILE *strout, FILE *strerr, cpu *my_cpu, double *value,
             int (*error_catcher)(FILE *strerr, cpu *my_cpu, int error_code));

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

int plot(char *input_stream, char *output_stream, char *error_stream,
         cpu *my_cpu, double x_begin, double x_end, double dx, double ymin,
         double ymax, int display_width, int display_height);

//--------------------ASSEMBLER-----------------------------------------
double *assemble(FILE *strin, FILE *strerr, pointer *pts, var *vars,
                 int (*error_catcher)(FILE *strerr, int cond));

int asm_main(char *filename);

int asm_cmd_def(FILE *strin, var *vars, double *codes, int *cur_code);

int asm_is_mrk(FILE *strin, FILE *strerr, char *word, int *cur_code,
               pointer *pts, int (*error_catcher)(FILE *strerr, int cond));

int asm_mark(char *word, int cur_code, pointer *pts);

int asm_cmd_convert(const char *word, int *c);

int asm_push_code(double *codes, int *cur_code, double value);

int asm_str_convert(char *word, double *reg);

int asm_cmd_push(FILE *strin, var *var, double *codes, int *cur_code);

int asm_str_convert(char *word, double *reg);

int asm_cmd_in(FILE *strin, double *codes, int *cur_code);

int asm_cmd_pop(FILE *strin, var *var, double *codes, int *cur_code);

int asm_cmd_out(FILE *strin, double *codes, int *cur_code);

int asm_cmd_mov(FILE *strin, double *codes, int *cur_code);

int asm_cmd_jump_like(FILE *strin, double *codes, int *cur_code, const int arg,
                      pointer *pts);

int asm_error_catcher(FILE *strerr, int cond);
