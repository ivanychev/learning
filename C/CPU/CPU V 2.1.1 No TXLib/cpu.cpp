#define _TX_ALLOW_TRACE

#include "cpu.h"

// #define IS_ZERO(x) (fabs(x) < 0.000000000001) //DBL_EPSILON хреново работает

/**
                cpu_construct				constructs cpu struct
                @param		stack_size		the size of cpu stack
                @return						the pointer to
the constructed cpu
**/
cpu *cpu_construct(int stack_size);

/**
                cpu_destruct				carefully destructs cpu,
freeing the dynamic memory and poisoning everything
                @param[out]		my_cpu		destructing cpu
                @return						void
**/

void cpu_destruct(cpu *my_cpu);

/**
                cpu_check					checks whether
the cpu is healthy or not
                @param[out]		my_cpu		pointer of cpu
                @return
CPU_CHECK_NULL if the pointer is null CPU_CHECK_INV_STACK if the cpu is invalid
                                                                        CPU_CHECK_OK
if ok
**/

int cpu_check(cpu *my_cpu);

/**
                cpu_push					pushes the input
value or register (ax, bx, cx or dx) value to the cpu stack Otherwise returns
error code

                @param[out]		my_cpu		pointer of cpu
                @param			push_arg	value that sets the
source of pushing

                @return
CPU_ERROR_STACK_FULL if the stack is full CPU_PUSH_INV_TOKEN if the token is
invalid CPU_OK if it's fine
**/
int cpu_push(cpu *my_cpu, int push_arg, ...);

/**
                cpu_pop
pops one element from cpu stack, saves it to the input pointer or register

                @param[out]		my_cpu			pointer of cpu
                @param			pop_arg
argument that sets the way of putting popped value
                @param[out]		return_value	where the popped value
would be saved

                @return
CPU_BROKEN_START		if the CPU is bad at the beginning
                                                                                CPU_BROKEN_FINISH		if the CPU is bad at the end
                                                                                CPU_POP_VALUE_NULL		if return_value is null
                                                                                CPU_ERROR_STACK_EMPTY	if the stack is empty
                                                                                CPU_OK					if it's fine

**/
int cpu_pop(cpu *my_cpu, int pop_arg, double *return_value);

/**
                cpu_add
pops op2 and op1, pushes op1 + op2
                @param[out]		my_cpu			pointer of cpu
                @return
CPU_BROKEN_START		if the CPU is bad at the beginning
                                                                                CPU_BROKEN_FINISH		if the CPU is bad at the end
                                                                                CPU_NOT_ENOUGH_ARGS		if there's not enough arguments in the stack
                                                                                CPU_OK if it's fine

**/

int cpu_add(cpu *my_cpu);

/**
                cpu_mul						pops op2 and
op1, pushes op1 * op2
                @param[out]		my_cpu			pointer of cpu
                @return
CPU_BROKEN_START		if the CPU is bad at the beginning
                                                                                CPU_BROKEN_FINISH		if the CPU is bad at the end
                                                                                CPU_NOT_ENOUGH_ARGS		if there's not enough arguments in the stack
                                                                                CPU_OK if it's fine

**/

int cpu_mul(cpu *my_cpu);
/**
                cpu_sub
pops op2 and op1, pushes op1 - op2
                @param[out]		my_cpu			pointer of cpu
                @return
CPU_BROKEN_START		if the CPU is bad at the beginning
                                                                                CPU_BROKEN_FINISH		if the CPU is bad at the end
                                                                                CPU_NOT_ENOUGH_ARGS		if there's not enough arguments in the stack
                                                                                CPU_OK if it's fine

**/
int cpu_sub(cpu *my_cpu);

/**
                cpu_div
pops op2 and op1, pushes op1 / op2
                @param[out]		my_cpu			pointer of cpu
                @return
CPU_BROKEN_START		if the CPU is bad at the beginning
                                                                                CPU_BROKEN_FINISH		if the CPU is bad at the end
                                                                                CPU_NOT_ENOUGH_ARGS		if there's not enough arguments in the stack
                                                                                CPU_ERROR_DIV_BY_ZERO	if op2 is zero
                                                                                CPU_OK if it's fine

**/
int cpu_div(cpu *my_cpu);

/**
                cpu_sin
pops op, pushes sin(op)
                @param[out]		my_cpu			pointer of cpu
                @return
CPU_BROKEN_START		if the CPU is bad at the beginning
                                                                                CPU_BROKEN_FINISH		if the CPU is bad at the end
                                                                                CPU_NOT_ENOUGH_ARGS		if there's not enough arguments in the stack
                                                                                CPU_OK if it's fine

**/

int cpu_sin(cpu *my_cpu);

/**
                cpu_cos
pops op, pushes cos(op)
                @param[out]		my_cpu			pointer of cpu
                @return
CPU_BROKEN_START		if the CPU is bad at the beginning
                                                                                CPU_BROKEN_FINISH		if the CPU is bad at the end
                                                                                CPU_NOT_ENOUGH_ARGS		if there's not enough arguments in the stack
                                                                                CPU_OK if it's fine

**/
int cpu_cos(cpu *my_cpu);
/**
                cpu_tan
pops op, pushes tan(op)
                @param[out]		my_cpu			pointer of cpu
                @return
CPU_BROKEN_START		if the CPU is bad at the beginning
                                                                                CPU_BROKEN_FINISH		if the CPU is bad at the end
                                                                                CPU_NOT_ENOUGH_ARGS		if there's not enough arguments in the stack
                                                                                CPU_ERROR_DIV_BY_ZERO	if cos(op) is zero
                                                                                CPU_OK if it's fine

**/

int cpu_tan(cpu *my_cpu);

/**
                cpu_sqrt						pops op,
pushes sqrt(op)
                @param[out]		my_cpu			pointer of cpu
                @return
CPU_BROKEN_START		if the CPU is bad at the beginning
                                                                                CPU_BROKEN_FINISH		if the CPU is bad at the end
                                                                                CPU_NOT_ENOUGH_ARGS		if there's not enough arguments in the stack
                                                                                CPU_ERROR_SQRT_NEGATIVE if the argumen is negative
                                                                                CPU_OK if it's fine

**/

int cpu_sqrt(cpu *my_cpu);

/**
                cpu_sqrt						pops op2
and op1, pushes op1 ^ op2
                @param[out]		my_cpu			pointer of cpu
                @return
CPU_BROKEN_START		if the CPU is bad at the beginning
                                                                                CPU_BROKEN_FINISH		if the CPU is bad at the end
                                                                                CPU_NOT_ENOUGH_ARGS		if there's not enough arguments in the stack
                                                                                CPU_ERROR_SQRT_NEGATIVE if the op1 is negative
                                                                                CPU_OK if it's fine

**/

int cpu_pow(cpu *my_cpu);

/**
                cpu_catch_error					Standart error
handler Catches the codes of errors and prints error messages to the file
stream, or does nothing if everything is fine
                @param[out]		stream			file stream
                @param[out]		my_cpu			pointer of cpu
                @param			condition		error code
                @return
CPU_ERROR_CATCHER_BAD if there were errors CPU_ERROR_CATCHER_OK if there weren't
errors
**/

int cpu_catch_error(FILE *stream, cpu *my_cpy, int condition);

/**
                cpu_dump						Proceeds
dump print of the cpu
                @param[out]		stream			Output file
stream
                @param[out]		my_cpu			Pointer of cpu
                @return
CPU_OK of CPU_CHECK_NULL, if the pointer is null
**/

int cpu_dump(FILE *stream, cpu *my_cpu);

/**
                cpu_mov
function that saves the input or other register value to the register

                @param[out]			my_cpu		the pointer of
cpu
                @param				mov_arg		the constant of
the destination register
                @param				mov_arg2	the type of
source value of register, if it is STR_value there's an extra double argument

                @return
CPU_BROKEN_START			if the CPU is bad at the beginning
                                                                                CPU_BROKEN_FINISH			if the CPU is bad at the end
                                                                                CPU_MOV_BAD_TOKEN			if there's bad token
                                                                                CPU_OK						if it's fine

**/
int cpu_mov(cpu *my_cpu, int mov_arg, int mov_arg2, ...);

/**
                cpu_out
function prints values of stack, registers or any character from the ascii
                @param[out]			fi input stream
                @param[out]			fo output stream
                @param[out]			strerr		error stream
                @param[out]			my_cpu		the pointer of
cpu

                @par
Syntax of out is very easy. There are four registers in cpu at the moment (1.1
Beta 2) out ax   -   printing the value of ax register
                                                                                out st		-	popping and printing the value of the first element of stack
                                                                                out ch 10	-   printing tenth character from the ascii.

                @return
CPU_BROKEN_START			if the CPU is bad at the beginning
                                                                                CPU_BROKEN_FINISH			if the CPU is bad at the end
                                                                                CPU_OK						if it's fine
                                                                                CPU_OUT_STREAM_IN_NULL		input stream pointer is NULL
                                                                                CPU_OUT_STREAM_OUT_NULL		output stream pointer is NULL
                                                                                CPU_OUT_STREAM_ERROR_NULL	error stream pointer is NULL
**/

int cpu_out(FILE *fo, FILE *strerr, cpu *my_cpu, int out_arg, ...);
/**
                cpu_swap						changes
the positions of first pair of stack elements

                @param[out]			my_cpu		pointer of cpu

                @return
CPU_BROKEN_START			if the CPU is bad at the beginning
                                                                                CPU_BROKEN_FINISH			if the CPU is bad at the end
                                                                                CPU_NOT_ENOUGH_ARGS			if there are less than 2 elements inside
                                                                                CPU_OK						if it's fine
**/
int cpu_swap(cpu *my_cpu);

/**
                cpu_dub
dublicates the first element of stack

                @param[out]			my_cpu		pointer of cpu

                @return
CPU_BROKEN_START			if the CPU is bad at the beginning
                                                                                CPU_BROKEN_FINISH			if the CPU is bad at the end
                                                                                CPU_NOT_ENOUGH_ARGS			if there are less than 1 elements inside
                                                                                CPU_OK						if it's fine
**/
int cpu_dub(cpu *my_cpu);

cpu *cpu_construct(int stack_size) {
  stack *constructed_stack = stack_construct(CPU_STACK_SIZE);
  VERIFY(constructed_stack);
  cpu *out_cpu = (cpu *)calloc(1, sizeof(cpu));
  VERIFY(out_cpu);
  out_cpu->cpu_stack = stack_construct(stack_size);
  out_cpu->ax = 0;
  out_cpu->bx = 0;
  out_cpu->cx = 0;
  out_cpu->dx = 0;
  VERIFY(out_cpu->cpu_stack);
  return out_cpu;
}

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

int cpu_dump(FILE *stream, cpu *my_cpu) {
  ASSERT(stream);
  int ret = 0;
  if (my_cpu == NULL) {
    ret = fprintf(stream, "Pointer is null, no cpu\n");
    VERIFY(ret);
    return CPU_CHECK_NULL;
  }
  fprintf(stream,
          "\\/ \\/ \\/ \\/ \\/ \\/ \\/ \\/ \\/ \\/ \\/ \\/ \\/ \\/ \\/ \\/\n");
  ret = fprintf(stream, "\nI'm CPU[%08x]\n", my_cpu);
  VERIFY(ret);
  int check = cpu_check(my_cpu);

  switch (check) {
  case (CPU_CHECK_OK):
    ret = fprintf(stream, "I'm OK\n");
    VERIFY(ret);
    break;
  case (CPU_CHECK_INV_STACK):
    ret = fprintf(stream, "I'm BAD\n");
    VERIFY(ret);
  default:
    VERIFY("CPU_CHECK ISN'T WORKING" || 0);
    break;
  }
  ret = fprintf(stream, "\nPrinting registers...\n");
  VERIFY(ret);
  ret = fprintf(stream, "ax = %lg\n", my_cpu->ax);
  VERIFY(ret);
  fprintf(stream, "Calling dump of stack...");
  stack_dump(stream, my_cpu->cpu_stack);
  ret = fprintf(stream, "\nCPU: end of dump\n");
  fprintf(stream,
          "/\\ /\\ /\\ /\\ /\\ /\\ /\\ /\\ /\\ /\\ /\\ /\\ /\\ /\\ /\\ /\\ \n");
  VERIFY(ret);
  return CPU_OK;
}

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

void cpu_destruct(cpu *my_cpu) {
  // if (my_cpu == NULL) CPU_ERROR_NULL;
  stack_destruct(my_cpu->cpu_stack);
  my_cpu->cpu_stack = NULL;
  my_cpu->ax = POISON;
  my_cpu->bx = POISON;
  my_cpu->cx = POISON;
  my_cpu->dx = POISON;

  free(my_cpu);
}

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

int cpu_check(cpu *my_cpu) {
  if (my_cpu == NULL)
    return CPU_CHECK_NULL;
  if (stack_ok(my_cpu->cpu_stack) == OK)
    return CPU_CHECK_OK;
  return CPU_CHECK_INV_STACK;
}

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

#define REG_PUSH_(name)                                                        \
  STR_##name : stack_push(my_cpu->cpu_stack, my_cpu->name);                    \
  return CPU_OK;

int cpu_push(cpu *my_cpu, int push_arg, ...) {
  if (stack_full(my_cpu->cpu_stack) != 0)
    return CPU_ERROR_STACK_FULL;
  double input_number = 0;

  switch (push_arg) {
  case STR_value:
    va_list args;
    va_start(args, push_arg);
    stack_push(my_cpu->cpu_stack, va_arg(args, double));
    va_end(args);
    return CPU_OK;

  case REG_PUSH_(ax); case REG_PUSH_(bx); case REG_PUSH_(cx);
      case REG_PUSH_(dx);

      default:
    return CPU_PUSH_INV_TOKEN;
  }
}

#undef REG_PUSH_

/*!!!!!!!!!!!!!!!!!!!
int cpu_dub(cpu* my_cpu)
{
        if (stack_full(my_cpu -> cpu_stack) != 0) return CPU_ERROR_STACK_FULL;

*/

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

#define REG_POP_(name)                                                         \
  STR_##name : my_cpu->name = pop_value;                                       \
  if (cpu_check(my_cpu) != CPU_CHECK_OK)                                       \
    return CPU_BROKEN_FINISH;                                                  \
  return CPU_OK;

int cpu_pop(cpu *my_cpu, int pop_arg, double *return_value) {

  if (cpu_check(my_cpu) != CPU_CHECK_OK)
    return CPU_BROKEN_START;
  if (return_value == NULL)
    return CPU_POP_VALUE_NULL;
  if (stack_empty(my_cpu->cpu_stack) == 1)
    return CPU_ERROR_STACK_EMPTY;

  double pop_value = stack_pop(my_cpu->cpu_stack);

  switch (pop_arg) {
  case STR_out:
    *return_value = pop_value;
    if (cpu_check(my_cpu) != CPU_CHECK_OK)
      return CPU_BROKEN_FINISH;
    return CPU_OK;
  case REG_POP_(ax); case REG_POP_(bx); case REG_POP_(cx); case REG_POP_(dx);

      default:
    return CPU_PUSH_INV_TOKEN;
  }
}
#undef REG_POP_

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

#define REG_OUT_(name)                                                         \
  STR_##name : fprintf(fo, "%lg", my_cpu->name);                               \
  if (cpu_check(my_cpu) != CPU_CHECK_OK)                                       \
    return CPU_BROKEN_FINISH;                                                  \
  return CPU_OK;

int cpu_out(FILE *fo, FILE *strerr, cpu *my_cpu, int out_arg, ...) {

  if (cpu_check(my_cpu) != CPU_CHECK_OK)
    return CPU_BROKEN_START;
  if (fo == NULL)
    return CPU_OUT_STREAM_OUT_NULL;
  if (strerr == NULL)
    return CPU_OUT_STREAM_ERROR_NULL;
  // int check_type = 0;
  int ret = 0;
  double out_value = 0;
  int chr = 0;

  switch (out_arg) {
  case STR_st:
    ret = cpu_pop(my_cpu, STR_out, &out_value);
    if (ret != CPU_OK) {
      fprintf(strerr, "CPU_OUT: ERROR while popping\n");
      return ret;
    }
    fprintf(fo, "%lg", out_value);
    if (cpu_check(my_cpu) != CPU_CHECK_OK)
      return CPU_BROKEN_FINISH;
    return CPU_OK;

  case STR_ch:
    va_list args;
    va_start(args, out_arg);
    chr = va_arg(args, int);
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! HOW TO CHECK WHETHER THERE IS EXTRA
    //! ARGUMENT OR NOT
    va_end(args);
    if (!((0 <= chr) && (chr <= 255))) {
      fprintf(strerr, "CPU_OUT: ERROR: invalid number of character");
      return CPU_OUT_BAD_TOKEN;
    }
    fputc((char)chr, fo);
    if (cpu_check(my_cpu) != CPU_CHECK_OK)
      return CPU_BROKEN_FINISH;
    return CPU_OK;

  case REG_OUT_(ax); case REG_OUT_(bx); case REG_OUT_(cx); case REG_OUT_(dx);
      default:
    return CPU_OUT_BAD_TOKEN;
  }
}

#undef REG_OUT_
//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

int cpu_dub(cpu *my_cpu) {
  if (cpu_check(my_cpu) != CPU_CHECK_OK)
    return CPU_BROKEN_START;
  if (stack_empty(my_cpu->cpu_stack))
    return CPU_NOT_ENOUGH_ARGS;

  double value = 0;
  int ret = 0;

  cpu_pop(my_cpu, STR_out, &value);

  cpu_push(my_cpu, STR_value, value);

  cpu_push(my_cpu, STR_value, value);

  if (cpu_check(my_cpu) != CPU_CHECK_OK)
    return CPU_BROKEN_FINISH;
  return CPU_OK;
}

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

int cpu_swap(cpu *my_cpu) {
  if (cpu_check(my_cpu) != CPU_CHECK_OK)
    return CPU_BROKEN_START;
  if ((my_cpu->cpu_stack->size) < 2)
    return CPU_NOT_ENOUGH_ARGS;
  double val1 = 0;
  double val2 = 0;
  cpu_pop(my_cpu, STR_out, &val1);
  cpu_pop(my_cpu, STR_out, &val2);
  cpu_push(my_cpu, STR_value, val1);
  cpu_push(my_cpu, STR_value, val2);
  if (cpu_check(my_cpu) != CPU_CHECK_OK)
    return CPU_BROKEN_FINISH;
  return CPU_OK;
}

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

int cpu_add(cpu *my_cpu) {
  if (cpu_check(my_cpu) != CPU_CHECK_OK)
    return CPU_BROKEN_START;
  if ((my_cpu->cpu_stack->size) < 2)
    return CPU_NOT_ENOUGH_ARGS;
  double op2 = stack_pop(my_cpu->cpu_stack);
  double op1 = stack_pop(my_cpu->cpu_stack);

  stack_push(my_cpu->cpu_stack, op1 + op2);
  if (cpu_check(my_cpu) != CPU_CHECK_OK)
    return CPU_BROKEN_FINISH;
  return CPU_OK;
}

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

int cpu_mul(cpu *my_cpu) {
  if (cpu_check(my_cpu) != CPU_CHECK_OK)
    return CPU_BROKEN_START;
  if ((my_cpu->cpu_stack->size) < 2)
    return CPU_NOT_ENOUGH_ARGS;
  double op2 = stack_pop(my_cpu->cpu_stack);
  double op1 = stack_pop(my_cpu->cpu_stack);

  stack_push(my_cpu->cpu_stack, op1 * op2);
  if (cpu_check(my_cpu) != CPU_CHECK_OK)
    return CPU_BROKEN_FINISH;
  return CPU_OK;
}

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

int cpu_sub(cpu *my_cpu) {
  if (cpu_check(my_cpu) != CPU_CHECK_OK)
    return CPU_BROKEN_START;
  if ((my_cpu->cpu_stack->size) < 2)
    return CPU_NOT_ENOUGH_ARGS;
  double op2 = stack_pop(my_cpu->cpu_stack);
  double op1 = stack_pop(my_cpu->cpu_stack);

  stack_push(my_cpu->cpu_stack, op1 - op2);
  if (cpu_check(my_cpu) != CPU_CHECK_OK)
    return CPU_BROKEN_FINISH;
  return CPU_OK;
}

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

int cpu_div(cpu *my_cpu) {
  if (cpu_check(my_cpu) != CPU_CHECK_OK)
    return CPU_BROKEN_START;
  if ((my_cpu->cpu_stack->size) < 2)
    return CPU_NOT_ENOUGH_ARGS;
  double op2 = stack_pop(my_cpu->cpu_stack);
  if (IS_ZERO(op2)) {
    stack_push(my_cpu->cpu_stack, op2);
    return CPU_ERROR_DIV_BY_ZERO;
  }
  double op1 = stack_pop(my_cpu->cpu_stack);

  stack_push(my_cpu->cpu_stack, op1 / op2);
  if (cpu_check(my_cpu) != CPU_CHECK_OK)
    return CPU_BROKEN_FINISH;
  return CPU_OK;
}

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

int cpu_sin(cpu *my_cpu) {
  if (cpu_check(my_cpu) != CPU_CHECK_OK)
    return CPU_BROKEN_START;
  if (stack_empty(my_cpu->cpu_stack))
    return CPU_NOT_ENOUGH_ARGS;
  stack_push(my_cpu->cpu_stack, sin(stack_pop(my_cpu->cpu_stack)));
  if (cpu_check(my_cpu) != CPU_CHECK_OK)
    return CPU_BROKEN_FINISH;
  return CPU_OK;
}

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

int cpu_cos(cpu *my_cpu) {
  if (cpu_check(my_cpu) != CPU_CHECK_OK)
    return CPU_BROKEN_START;
  if (stack_empty(my_cpu->cpu_stack))
    return CPU_NOT_ENOUGH_ARGS;
  ;
  stack_push(my_cpu->cpu_stack, cos(stack_pop(my_cpu->cpu_stack)));
  if (cpu_check(my_cpu) != CPU_CHECK_OK)
    return CPU_BROKEN_FINISH;
  return CPU_OK;
}

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

int cpu_tan(cpu *my_cpu) {
  if (cpu_check(my_cpu) != CPU_CHECK_OK)
    return CPU_BROKEN_START;
  if (stack_empty(my_cpu->cpu_stack))
    return CPU_NOT_ENOUGH_ARGS;
  double op = stack_pop(my_cpu->cpu_stack);
  if (IS_ZERO(op)) {
    stack_push(my_cpu->cpu_stack, op);
    return CPU_ERROR_DIV_BY_ZERO;
  }
  stack_push(my_cpu->cpu_stack, sin(op) / cos(op));
  if (cpu_check(my_cpu) != CPU_CHECK_OK)
    return CPU_BROKEN_FINISH;
  return CPU_OK;
}

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

int cpu_sqrt(cpu *my_cpu) {
  if (cpu_check(my_cpu) != CPU_CHECK_OK)
    return CPU_BROKEN_START;
  if (stack_empty(my_cpu->cpu_stack))
    return CPU_NOT_ENOUGH_ARGS;
  ;
  double op = stack_pop(my_cpu->cpu_stack);
  if (op < 0) {
    stack_push(my_cpu->cpu_stack, op);
    return CPU_ERROR_SQRT_NEGATIVE;
  }
  stack_push(my_cpu->cpu_stack, sqrt(op));
  if (cpu_check(my_cpu) != CPU_CHECK_OK)
    return CPU_BROKEN_FINISH;
  return CPU_OK;
}

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

int cpu_pow(cpu *my_cpu) {
  if (cpu_check(my_cpu) != CPU_CHECK_OK)
    return CPU_BROKEN_START;
  if ((my_cpu->cpu_stack->size) < 2)
    return CPU_NOT_ENOUGH_ARGS;
  double op2 = stack_pop(my_cpu->cpu_stack);
  double op1 = stack_pop(my_cpu->cpu_stack);
  if (op1 < 0) {
    stack_push(my_cpu->cpu_stack, op1);
    stack_push(my_cpu->cpu_stack, op2);
    return CPU_ERROR_NEGATIVE_BASE;
  }

  stack_push(my_cpu->cpu_stack, powf((float)op1, (float)op2));
  if (cpu_check(my_cpu) != CPU_CHECK_OK)
    return CPU_BROKEN_FINISH;
  return CPU_OK;
}

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

int cpu_catch_error(FILE *stream, cpu *my_cpu, int condition) {
  switch (condition) {
  case CPU_OUT_STREAM_ERROR_NULL:
    fprintf(stream, "\n CPU_OUT: The error stream pointer is invalid!\n");
    return CPU_ERROR_CATCHER_BAD;
  case CPU_OUT_STREAM_IN_NULL:
    fprintf(stream, "\n CPU_OUT: The input stream pointer is invalid!\n");
    return CPU_ERROR_CATCHER_BAD;

  case CPU_OUT_STREAM_OUT_NULL:
    fprintf(stream, "\n CPU_OUT: The output stream pointer is invalid!\n");
    return CPU_ERROR_CATCHER_BAD;

  case CPU_OUT_BAD_TOKEN:
    fprintf(stream, "\n CPU_OUT: There's bad token argument\n");
    return CPU_ERROR_CATCHER_BAD;

  case CPU_CHECK_NULL:
    fprintf(stream, "\nCPU checker found out that the pointer is NULL\n");
    return CPU_ERROR_CATCHER_BAD;
    break;

  case CPU_CHECK_OK:
    return CPU_ERROR_CATCHER_OK;
    break;

  case CPU_CHECK_INV_STACK:
    fprintf(stream, "\nCPU checker found out that something bad with CPU\n");
    cpu_dump(stream, my_cpu);
    return CPU_ERROR_CATCHER_BAD;
    break;

  case CPU_ERROR_STACK_FULL:
    fprintf(stream, "\nERROR: stack is full\n");
    cpu_dump(stream, my_cpu);
    return CPU_ERROR_CATCHER_BAD;
    break;

  case CPU_ERROR_STACK_EMPTY:
    fprintf(stream, "\nERROR: stack is empty\n");
    cpu_dump(stream, my_cpu);
    return CPU_ERROR_CATCHER_BAD;
    break;

  case CPU_OK:
    return CPU_ERROR_CATCHER_OK;
    break;

  case CPU_PUSH_INV_TOKEN:
    fprintf(stream, "\nERROR: pushed invalid token\n");
    return CPU_ERROR_PUSH_BAD_TOKEN;
    break;

  case CPU_BROKEN_START:
    fprintf(stream, "\nERROR: stack is bad at the beginning\n");
    cpu_dump(stream, my_cpu);
    return CPU_ERROR_CATCHER_BAD;
    break;

  case CPU_BROKEN_FINISH:
    fprintf(stream, "\nERROR: stack is bad at the end\n");
    cpu_dump(stream, my_cpu);
    return CPU_ERROR_CATCHER_BAD;
    break;

  case CPU_NOT_ENOUGH_ARGS:
    fprintf(stream, "\nERROR: not enough arguments\n");
    cpu_dump(stream, my_cpu);
    return CPU_ERROR_CATCHER_BAD;
    break;

  case CPU_POP_VALUE_NULL:
    fprintf(stream, "\nERROR: value pointer is null\n");
    return CPU_ERROR_CATCHER_BAD;
    break;

  case CPU_ERROR_DIV_BY_ZERO:
    fprintf(stream, "\nERROR: division by zero\n");
    cpu_dump(stream, my_cpu);
    return CPU_ERROR_CATCHER_BAD;
    break;

  case CPU_ERROR_NEGATIVE_BASE:
    fprintf(stream, "\nERROR: power base is negative\n");
    cpu_dump(stream, my_cpu);
    return CPU_ERROR_CATCHER_BAD;
    break;

  case CPU_ERROR_SQRT_NEGATIVE:
    fprintf(stream, "\nERROR: sqrt argument is negative\n");
    cpu_dump(stream, my_cpu);
    return CPU_ERROR_CATCHER_BAD;

    break;
  case CPU_MOV_BAD_TOKEN:
    fprintf(stream, "CPU_MOV: There's bad token argument)");
    return CPU_ERROR_CATCHER_BAD;
    break;
  default:
    fprintf(stream, "\n!!!ERROR: INVALID ERROR SIGNATURE!!!\n");
    return CPU_ERROR_CATCHER_BAD;
    break;
  }
}

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

#define REG_MOV_(name)                                                         \
  STR_##name : my_cpu->name = value;                                           \
  break;

int cpu_mov(cpu *my_cpu, int mov_arg, int mov_arg2, ...) {

  if (cpu_check(my_cpu) != CPU_CHECK_OK)
    return CPU_BROKEN_START;
  double value = 0;

  switch (mov_arg2) {
  case STR_ax:
    value = my_cpu->ax;
    break;
  case STR_bx:
    value = my_cpu->bx;
    break;
  case STR_cx:
    value = my_cpu->cx;
    break;
  case STR_dx:
    value = my_cpu->dx;
    break;
  case STR_value:
    va_list args;
    va_start(args, mov_arg2);
    value = va_arg(args, double);
    break;
  default:
    return CPU_MOV_BAD_TOKEN;
  }

  switch (mov_arg) {
  case REG_MOV_(ax); case REG_MOV_(bx); case REG_MOV_(cx); case REG_MOV_(dx);
      default:
    return CPU_MOV_BAD_TOKEN;
  }
  if (cpu_check(my_cpu) != CPU_CHECK_OK)
    return CPU_BROKEN_FINISH;
  return CPU_OK;
}
