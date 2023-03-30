#include "cpu.h"

/**
                stack_construct
constructs new stack using dynamic memory
                @param				size		the size of
stack
                @return
the pointer of constructed stack
**/
stack *stack_construct(int size);

/**
                pop
takes the element from stack and decreases its size by one
                @param[out]		user_stack		source stack
                @return taken element
**/
double stack_pop(stack *user_stack);

/**
                stack_err_catch
prints error messages to the output
                @param		error_code			error code
                @param[out]		string addition message string
                @par							if
error_code = ERR_SIZE, system_out sends two more parameters - size of stack and
maximum size of stack
                @return							void
**/
int stack_err_catch(int error_code, char *string, ...);

/**
                push							puts the
input element in stack
                @param[out]		user_stack		source stack
                @param			input			input element

                @return
0, if there were no errors, else 1
**/

void stack_push(stack *user_stack, double input);

/**
                full
finds out if the input stack is full or not
                @param[out]		user_stack		source stack
                @return							1 if
full, otherwise 0
**/

int stack_full(stack *user_stack);

/**
                empty
finds out if the input stack is empty or not
                @param[out]		user_stack		source stack
                @return							1 if
empty, otherwise 0
**/

int stack_empty(stack *user_stack);

/**
                stack_ok						analyzes
stack health by checking its input pointer and size
                @param[out]		user_stack		source stack
                @return
-1 if the pointer is incorrect, 0 if the size is incorrect, 1 if OK
**/

int stack_ok(stack *user_stack);

/**
                stack_destruct					puts the poison
in all data cells, sets dynamic memory free and turns pointers into NULL
                @param[out]		user_stack		source stack
                @return							void
**/

int stack_destruct(stack *user_stack);

/**
                stack_print
prints the elements of stack
                @param[out]		user_stack		source stack
                @return
OK = 0, if everything is fine, ERR_NULL, if pointer is incorrect
**/

int stack_print(stack *user_stack);

/**
                dumb_print						debug
print of stack. Prints all data cell, even if they aren't included into stack at
the moment
                @param[out]		user_stack		source stack
                @return							void
**/

int stack_dump(FILE *stream, stack *user_stack);

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

stack *stack_construct(int size) {
  stack *new_stack = (stack *)calloc(1, sizeof(stack));
  new_stack->size = 0;
  new_stack->maxsize = size;
  new_stack->data = (double *)calloc(size, sizeof(new_stack->data[0]));
  return new_stack;
}

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

/*
int stack_err_catch(int error_code, char* string, ...)
{
        printf("%s", string);
        switch (error_code)
        {
        case ERR_INIT:
                printf("\n\nINITIALIZATION ERROR: The stack hasn't been
initialised\n\n"); return 1; case ERR_NULL: printf("\n\nPOINTER ERROR: The
pointer to the stack is null\n\n"); return 1; case ERR_PRINT: printf("\n\nPRINT
ERROR: some elements hasn't been printed\n\n"); return 1; case ERR_WRONG_SZ:
                va_list args;
                va_start(args, string);
                printf("\n\nSIZE ERROR: wrong size of stack [SIZE = %d, MAXSIZE
= %d]\n\n", va_arg(args, int), va_arg(args, int)); return 1; default: break;
        };
        return OK;
}
*/

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

double stack_pop(stack *user_stack) {
  VERIFY(stack_ok(user_stack) == OK);
  return user_stack->data[--(user_stack->size)];
}

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

void stack_push(stack *user_stack, double input) {
  VERIFY(stack_ok(user_stack) == OK); // what means that size < maxsize
  user_stack->data[(user_stack->size)++] =
      input; // where new size <= maxsize - correct
  VERIFY(stack_ok(user_stack) == OK);
}

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

int stack_full(stack *user_stack) {
  ASSERT(user_stack);
  return (user_stack->size == user_stack->maxsize) ? 1 : 0;
}

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

int stack_empty(stack *user_stack) {
  ASSERT(user_stack);
  return (user_stack->size == 0) ? 1 : 0;
}

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

int stack_ok(stack *user_stack) {
  if (!(user_stack))
    return ERR_NULL;
  return ((user_stack->maxsize < user_stack->size) || (user_stack->size < 0)
              ? ERR_WRONG_SZ
              : OK);
}

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

int stack_destruct(stack *user_stack) {
  if (!(user_stack))
    return ERR_NULL;
  for (int i = 0; i < user_stack->maxsize; ++i)
    user_stack->data[i] = POISON;
  free(user_stack->data);
  user_stack->data = NULL;
  user_stack->size = 0;
  free(user_stack);
  return OK;
}

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

int stack_print(stack *user_stack) {
  if (!(user_stack))
    return ERR_NULL;
  fprintf(stdout, "Size of stack: %d\nMaximum size: %d\n", user_stack->size,
          user_stack->maxsize);
  for (int i = user_stack->size - 1; i >= 0; --i) {
    fprintf(stdout, "%.2d: ", i + 1);
    if (fprintf(stdout, "%lg", user_stack->data[i]) < 0)
      return ERR_PRINT;
    putchar('\n');
  }
  return OK;
}

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

int stack_dump(FILE *stream, stack *user_stack) {
  fprintf(stream, "\nI'm stack\n");
  if (!(user_stack))
    return ERR_NULL;
  fprintf(stream,
          "stack[%08x] %s\n"
          "Maxsize = %d\n"
          "Size = %d\n",
          user_stack, stack_ok(user_stack) ? "BAD" : "OK!", user_stack->maxsize,
          user_stack->size);
  for (int i = user_stack->maxsize - 1; i >= 0; --i)

  {
    fprintf(stream, "%.3: ", i + 1);
    if (fprintf(stream, "%c %lg \n",
                ((user_stack->size > i) && (i >= 0)) ? '*' : ' ',
                user_stack->data[i]) < 0)
      return ERR_PRINT;
  }
  fprintf(stream, "\nStack: end of dump\n");
  return OK;
}