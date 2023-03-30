#include "stack.h"

//  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\ 
// /  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \
// \  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /
//  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/
//  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/

#define CHECK_STACK_NULL_                                                      \
  if (!(user_stack)) {                                                         \
    stack_err_catch(ERR_INIT, "");                                             \
    break;                                                                     \
  }

#define CHECK_EMPTY_                                                           \
  if (stack_empty(user_stack)) {                                               \
    printf("Stack is empty, sorry\n");                                         \
    break;                                                                     \
  }

#define CHECK_FULL_                                                            \
  if (stack_full(user_stack)) {                                                \
    printf("Stack is full, sorry\n");                                          \
    break;                                                                     \
  }

enum {
  CMD_NONE = 0,
  CMD_CREATE = 1,
  CMD_PUSH = 2,
  CMD_POP = 3,
  CMD_PRINT = 4,
  CMD_DUMP = 5,
  CMD_DESTRUCT = 6,
  CMD_CHECK = 7,
  CMD_EXIT = 8,
  CMD_C = 1,
  CMD_P = 2,
  CMD_O = 3,
  CMD_R = 4,
  CMD_D = 5,
  CMD_E = 6,
  CMD_H = 7,
  CMD_X = 8,
};

#define CHECK_COMMAND(str, name) (stricmp((str), #name) == 0) ? CMD_##name:

//  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\ 
// /  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \
// \  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /
//  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/
//  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/

/**
                system					configures friendly IO
and gives user the ability to create, use and delete stack

                @return					0, because the function
waits for correct arguments
**/

int system_out(stack *user_stack) {
  const char MAXLINE = 50;
  char word[MAXLINE] = {};
  char c = 0;
  const char PUTIN_IS_OUR_PRESIDENT = 1;
  int size = 0;
  int push_num = 0;
  int pop_num = 0;
  int check_ok = 0;
  int stack_created = 0;
  int print_status = 0;
  int dump_status = 0;
  while (PUTIN_IS_OUR_PRESIDENT) {

    printf("\nThere are avalable coomands:\n"
           "For example: co[M]mand means that \" command \" and \" m \" are "
           "acceptable\n"
           "[C]reate - create stack\n"
           "[P]ush - push element\n"
           "p[O]p - pop element\n"
           "p[R]int - print stack\n"
           "[D]ump - dump print\n"
           "d[E]struct - destruct stack\n"
           "c[H]eck - check stack\n"
           "e[X]it - exit\n\n");

    scanf("%s", &word);

    c = CHECK_COMMAND(word, CREATE) CHECK_COMMAND(word, PUSH)
        CHECK_COMMAND(word, POP) CHECK_COMMAND(word, PRINT)
            CHECK_COMMAND(word, DUMP) CHECK_COMMAND(word, DESTRUCT)
                CHECK_COMMAND(word, CHECK) CHECK_COMMAND(word, EXIT)
                    CHECK_COMMAND(word, C) CHECK_COMMAND(word, P)
                        CHECK_COMMAND(word, O) CHECK_COMMAND(word, R)
                            CHECK_COMMAND(word, D) CHECK_COMMAND(word, E)
                                CHECK_COMMAND(word, H) CHECK_COMMAND(word, X)
                                    CMD_NONE;

    if (user_stack)
      VERIFY(stack_ok(user_stack) == OK);

    switch (c) {
    case CMD_CREATE:
      printf("Type positive integer value of size of the stack\n");
      scanf("%d", &size);

      if (size <= 0) {
        printf("Wrong size of stack [%d]\n", size);
        break;
      }

      user_stack = stack_construct(size);
      stack_created = 1;
      break;

    case CMD_PUSH:

      CHECK_STACK_NULL_;
      CHECK_FULL_;

      printf("Type the integer number you want to push\n");
      scanf("%d", &push_num);

      stack_push(user_stack, push_num);
      printf("Now, size of stack is %d\nMaximum size is %d\n\n",
             user_stack->size, user_stack->maxsize);
      break;

    case CMD_POP:
      CHECK_STACK_NULL_;
      CHECK_EMPTY_;

      pop_num = stack_pop(user_stack);
      printf("Popped num is %d\nSize of stack is %d\nMaximum size is %d\n\n",
             pop_num, user_stack->size, user_stack->maxsize);
      break;

    case CMD_PRINT:
      stack_err_catch(stack_print(user_stack), "");
      break;

    case CMD_DUMP:
      stack_err_catch(dump_print(user_stack), "");
      break;

    case CMD_DESTRUCT:
      stack_err_catch(stack_destruct(user_stack), "");
      stack_created = 0;
      user_stack = NULL;
      printf("Stack destroyed\n\n");
      break;

    case CMD_CHECK:
      if (stack_created == 0) {
        stack_err_catch(ERR_INIT, "");
        break;
      }
      stack_err_catch(stack_ok(user_stack), "Stack is OK\n", user_stack->size,
                      user_stack->maxsize);
      break;
    case CMD_EXIT:
      return 0;
      break;

    default:
      printf("Bad token: %s\n", word);
      break;
    }
    c = 0;
    if (user_stack)
      VERIFY(stack_ok(user_stack) == OK);
    putchar('\n');
  }
}

#undef CHECK_STACK_NULL_
#undef CHECK_OK_PRINT_
#undef CHECK_EMPTY_
#undef CHECK_FULL_
#undef CONVERT_WORD_

//  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\ 
// /  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \
// \  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /\  /
//  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/
//  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/  \/