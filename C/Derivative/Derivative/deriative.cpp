#include "compiler.h"

/**
                        @par		That file contain deriative library. The
majority of functions explains derivating of functions, whish are declared in
file function.h

                                                V 1.01


**/

extern FILE *strerr;
extern FILE *strlog;

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int build_derivative(tree *my_tree, tree_head **derivative);

int d_node(tree *my_tree, tree *to_tree, int side, char *var);

int d_add(tree *my_tree, tree *to_tree, char *var);

int d_sub(tree *my_tree, tree *to_tree, char *var);

int d_mul(tree *my_tree, tree *to_tree, char *var);

int d_div(tree *my_tree, tree *to_tree, char *var);

int d_sin(tree *my_tree, tree *to_tree, char *var);

int d_cos(tree *my_tree, tree *to_tree, char *var);

int d_tg(tree *my_tree, tree *to_tree, char *var);

int d_ctg(tree *my_tree, tree *to_tree, char *var);

int d_ln(tree *my_tree, tree *to_tree, char *var);

int d_log(tree *my_tree, tree *to_tree, char *var);

int d_sqrt(tree *my_tree, tree *to_tree, char *var);

int d_arcsin(tree *my_tree, tree *to_tree, char *var);

int d_arccos(tree *my_tree, tree *to_tree, char *var);

int d_arctg(tree *my_tree, tree *to_tree, char *var);

int d_exp(tree *my_tree, tree *to_tree, char *var);

int d_pow(tree *my_tree, tree *to_tree, char *var);

int d_n(tree *my_tree, tree *to_tree, char *var);

int d_v(tree *my_tree, tree *to_tree, char *var);

int d_f(tree *my_tree, tree *to_tree, char *var);

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

/**
                @par			Here's defenition of function, which are
declared and defined in current file. That array is used by D_F() function to
call corresponding function

**/
typedef int (*d_func)(tree *my_tree, tree *to_tree, char *var);

d_func funcs[FUNC_NUM] = {
#define _S(func_def, func_name, argc) func_def,
#define _NUM(n)
#include "functions.h"
#undef _S
#undef _NUM
};

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#define HEAD(my_tree) (my_tree->head)
#define ROOT(my_tree) (my_tree->head->root)
#define WORD(my_tree) (char *)(my_tree->value)
#define DOUBLE(my_tree) *(double *)(my_tree->value)
#define INT(my_tree) *((int *)(my_tree->value))

#ifdef DEBUG
#define TREE(name)                                                             \
  putc('\n', stdout);                                                          \
  tree_dump(stdout, name);                                                     \
  putc('\n', stdout);
#else
#define TREE(name)
#endif

#define CALL(func)                                                             \
  ret = func;                                                                  \
  if (ret != CPLR_OK)                                                          \
    return ret;

#define TYPE(node) node->type
#define CHECK_ARGS(name)                                                       \
  VERIFY(my_tree == NULL, CPLR_BAD, name ": Argumented tree pointer is NULL"); \
  VERIFY(to_tree == NULL, CPLR_BAD,                                            \
         name ": Argumented destination tree pointer is NULL");                \
  int _1_size = 0;                                                             \
  VERIFY(tree_check(my_tree, &_1_size) != TREE_CHECK_OK, CPLR_BAD,             \
         #name ": Argumented tree is invalid");                                \
  _1_size = 0;                                                                 \
  VERIFY(var == NULL, CPLR_BAD, name ":Argumented string pointer is NULL");

#define CHECK_TEMPLATE(name, string)                                           \
  VERIFY(ret != TREE_OK, CPLR_BAD, #name string);
#define CHECK_BURN(name)                                                       \
  VERIFY1(ret != TREE_OK, CPLR_BAD, "%s: Tree burn failed", name);
#define CHECK_INIT(name) CHECK_TEMPLATE(name, ": Initialization failed");
#define CHECK_COPY(name) CHECK_TEMPLATE(name, ": Copying failed");
#define CHECK_ADD(name) CHECK_TEMPLATE(name, ": Sticking failed");

enum data_types {
  TYPE_DOUBLE = 1001,
  TYPE_INT = 1002,
  TYPE_STRING_V = 1003,
  TYPE_STRING_F = 1004,
};

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

/**
                                        tree_copy_add
That function copies tree and sticks it to argumented tree from argumented side

                @param[out]	copying_tree
Tree to copy
                @param[out]	tree_to_stick_to
Well, you know
                @param		side
Constant describes side
                @param[out]	func_name
Name of function, that called current. Needed for debug print

                @return
CPLR_BAD CPLR_OK

**/

int tree_copy_add(tree *copying_tree, tree *tree_to_stick_to, int side,
                  char *func_name) {

  assert(copying_tree);
  assert(tree_to_stick_to);
  assert(side == LEFT || side == RIGHT);
  assert(func_name);
  // tree_dump(stdout, tree_to_stick_to -> head);

  tree_head *temp_tree_head = NULL;
  int ret = tree_copy(copying_tree, &temp_tree_head);
  TREE(temp_tree_head);

  putc('\n', stdout);
  tree_dump_in_order(stdout, copying_tree, "");
  putc('\n', stdout);
  tree_dump_in_order(stdout, temp_tree_head->root, "");

  tree_save_head(temp_tree_head->root, temp_tree_head);
  // tree_save_head(temp_tree_head

  VERIFY1(ret != TREE_OK, CPLR_BAD, "%s: Copying failed", func_name);

  if (side == LEFT)
    tree_add_left(tree_to_stick_to, temp_tree_head->root);
  else
    tree_add_right(tree_to_stick_to, temp_tree_head->root);

  VERIFY1(ret != TREE_OK, CPLR_BAD, "%s: Adding failed", func_name);
  // tree_dump(stdout, tree_to_stick_to -> head);
  tree *temp_tree = NULL;
  ret = head_destr(temp_tree_head, TREE_DESTR_HEAD, &temp_tree);

  VERIFY1(ret != TREE_OK, CPLR_BAD, "%s: Head destruction failed", func_name);

  return CPLR_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

/**
                                                        tree_init_va
Creates tree, saves type and value, and sticks to current

                @param[out]			dest_save_tree_token
Tree head pointer, which is needed for that function
                @param[out]			head_ptr
The pointer of what head would be saved in created tree
                @param[out]			tree_to_stick_to
Well, you know
                @param[out]			func_name
Name of function, that called current. Needed for debug print
                @param				tree_type
Saving tree type
                @param				add_side
Sticking side

                @return
CPLR_BAD CPLR_OK

**/

int tree_init_va(tree **dest_save_tree_token, tree_head *head_ptr,
                 tree *tree_to_stick_to, char *func_name, int tree_type,
                 int add_side, ...) {

  va_list vl;
  va_start(vl, add_side);
  assert(add_side == LEFT || add_side == RIGHT);
  int ret = tree_init(dest_save_tree_token, head_ptr, tree_to_stick_to,
                      func_name, tree_type, add_side);
  VERIFY1(ret != TREE_OK, CPLR_BAD, "%s: Tree initialization failed",
          func_name);

  ret = TREE_OK;
  switch (tree_type) {
  case TR_N:
    if (add_side == LEFT)
      ret = tree_burn(tree_to_stick_to->left, TR_N, va_arg(vl, double));
    else
      ret = tree_burn(tree_to_stick_to->right, TR_N, va_arg(vl, double));
    va_end(vl);
    break;
  case TR_SIGN:
    if (add_side == LEFT)
      ret = tree_burn(tree_to_stick_to->left, TR_SIGN, va_arg(vl, int));
    else
      ret = tree_burn(tree_to_stick_to->right, TR_SIGN, va_arg(vl, int));
    va_end(vl);
    break;
  case TR_F:
    if (add_side == LEFT)
      ret = tree_burn(tree_to_stick_to->left, TR_F, va_arg(vl, char *));
    else
      ret = tree_burn(tree_to_stick_to->right, TR_F, va_arg(vl, char *));
    va_end(vl);
    break;
  case TR_V:
    if (add_side == LEFT)
      ret = tree_burn(tree_to_stick_to->left, TR_V, va_arg(vl, char *));
    else
      ret = tree_burn(tree_to_stick_to->right, TR_V, va_arg(vl, char *));
    va_end(vl);
    break;
  default:
    break;
  }

  VERIFY1(ret != TREE_OK, CPLR_BAD, "%s: Tree burning failed", func_name);

  return CPLR_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

/**
                                                                build_derivative
The main function in current library. Builds derivative tree for argumented
expression tree

                @param[out]				my_tree
tree to derivate
                @param[out]				derivative
where to save tree head of derivative tree
                @param[out]				var
Derivating variable

                @return					CPLR_BAD
                                                                CPLR_OK

**/

int build_derivative(tree *my_tree, tree_head **derivative, char *var) {
  VERIFY(my_tree == NULL, CPLR_BAD,
         "BUILD DERIVATIVE: Argumented tree is NULL");
  VERIFY(derivative == NULL, CPLR_BAD,
         "BUILD DERIVATIVE: Argumented tree head is NULL");
  int __size = 0;
  VERIFY(tree_check(my_tree, &__size) != TREE_CHECK_OK, CPLR_BAD,
         "BUILD DERIVATIVE: Argumented tree is invalid");
  VERIFY(var == NULL, CPLR_BAD,
         "BUILD DERIVATIVE: Argumented string pointer is NULL");
  __size = 0;

  tree_head *out_der = NULL;
  int ret = head_ctr(&out_der);
  // tree_dump(stdout, out_der);
  out_der->root->type = TR_PGM;

  VERIFY(ret != TREE_OK, ret, "BUILD DERIVATIVE: Tree construction failed");
  ret = d_node(my_tree, out_der->root, RIGHT, var);
  VERIFY(ret != CPLR_OK, CPLR_BAD,
         "BUILD DERIVATIVE: Deriative is taken wrong");
  VERIFY(tree_check(out_der->root, &__size) != TREE_CHECK_OK, CPLR_BAD,
         "BUILD DERIVATIVE: Built derivative is invalid");

  *derivative = out_der;

  return CPLR_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

/**

                                                                        d_node
asseses current tree node and call corresponding function to deal with it

                @param[out]					my_tree
argumented derivating tree
                @param[out]					to_tree
tree to build
                @param						side
side of sticking
                @param[out]					var
derivating variable

                @return						CPLR_BAD
                                                                        CPLR_OK

**/

int d_node(tree *my_tree, tree *to_tree, int side, char *var) {
  CHECK_ARGS("D NODE");
  VERIFY(side != LEFT && side != RIGHT, CPLR_BAD, "D NODE: No such side");
  VERIFY(var == NULL, CPLR_BAD, "D NODE: Argumented string pointer is NULL");
  int ret = 0;
  tree *d_tree = NULL;
  assert(to_tree->head);
  ret = tree_ctr(&d_tree, to_tree->head);
  VERIFY(ret != TREE_OK, CPLR_BAD, "D NODE: Tree construction failed");

  if (side == LEFT)
    ret = tree_add_left(to_tree, d_tree);
  else
    ret = tree_add_right(to_tree, d_tree);

  TREE(to_tree->head);
  VERIFY(ret != TREE_OK, CPLR_BAD, "D NODE: Sticking failed");

  switch (TYPE(my_tree)) {
  case TR_N:
    CALL(d_n(my_tree, d_tree, var));
    break;
  case TR_V:
    CALL(d_v(my_tree, d_tree, var));
    break;
  case TR_SIGN:

    switch (INT(my_tree)) {
    case '+':
      CALL(d_add(my_tree, d_tree, var));
      break;
    case '-':
      CALL(d_sub(my_tree, d_tree, var));
      break;
    case '*':
      CALL(d_mul(my_tree, d_tree, var));
      break;
    case '/':
      CALL(d_div(my_tree, d_tree, var));
      break;
    default:
      VERIFY1(true, CPLR_BAD, "D NODE: Value of sign node is invalid, got [%c]",
              TYPE(my_tree));
      break;
    }
    break;
  case TR_F:
    CALL(d_f(my_tree, d_tree, var));
    break;
  default:
    VERIFY(true, CPLR_BAD, "D NODE: Invalid type of tree node");
    break;
  }
  assert(_CrtCheckMemory());

  return CPLR_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// #define CALL_FUNC_ANALYSE(func_name) CALL(d_##func

/**
                                                                        d_f
function deals with function trees and calls corresponding function to deal with
it
                @param[out]					my_tree
argumented derivating tree
                @param[out]					to_tree
tree to build
                @param[out]					var
derivating variable

                @return						CPLR_BAD
                                                                        CPLR_OK

**/
int d_f(tree *my_tree, tree *to_tree, char *var) {
  CHECK_ARGS("D NODE");
  int i = 0;
  int ret = 0;

  for (i = 0; i < FUNC_NUM; ++i)
    if (strcmp(WORD(my_tree), (math_funcs[i]).name) == 0)
      break;
  VERIFY1(i == FUNC_NUM, CPLR_BAD, "GET F: No such function [%s]", var);

  VERIFY(strcmp(WORD(my_tree), "fac") == 0, CPLR_BAD,
         "D NODE: Do not support facterial derivative");
  CALL((funcs[i])(my_tree, to_tree, var));

  return CPLR_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

/**
                                                                        d_n
derivating number

                @param[out]					my_tree
argumented derivating tree
                @param[out]					to_tree
tree to build
                @param[out]					var
derivating variable

                @return						CPLR_BAD
                                                                        CPLR_OK


**/
int d_n(tree *my_tree, tree *to_tree, char *var) {
  CHECK_ARGS("D N");
  int ret = 0;

  ret = tree_burn(to_tree, TR_N, 0.0);
  // tree_dump(stdout, to_tree -> head);
  CHECK_BURN("D N");

  return CPLR_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

/**
                                                                        d_v
derivating variable

                @param[out]					my_tree
argumented derivating tree
                @param[out]					to_tree
tree to build
                @param[out]					var
derivating variable

                @return						CPLR_BAD
                                                                        CPLR_OK



**/
int d_v(tree *my_tree, tree *to_tree, char *var) {
  CHECK_ARGS("D V");
  int ret = 0;
  int is_var = 0;
  if (strcmp(var, WORD(my_tree)) == 0)
    is_var = 1;

  ret = tree_burn(to_tree, TR_N, (double)is_var);
  // tree_dump(stdout, to_tree -> head);
  CHECK_BURN("D V");

  return CPLR_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

/**
                                                                        d_add
derivating adding

                @param[out]					my_tree
argumented derivating tree
                @param[out]					to_tree
tree to build
                @param[out]					var
derivating variable

                @return						CPLR_BAD
                                                                        CPLR_OK



**/

int d_add(tree *my_tree, tree *to_tree, char *var) {
  char *name = "D ADD";

  CHECK_ARGS("D ADD");
  VERIFY1(my_tree->left == NULL || my_tree->right == NULL, CPLR_BAD,
          "%s: Adding operator has a null child", name);

  int ret = tree_burn(to_tree, TR_SIGN, '+');
  CHECK_BURN(name);

  CALL(d_node(my_tree->left, to_tree, LEFT, var));
  CALL(d_node(my_tree->right, to_tree, RIGHT, var));

  return CPLR_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

/**
                                                                        d_sub
derivating subtraction

                @param[out]					my_tree
argumented derivating tree
                @param[out]					to_tree
tree to build
                @param[out]					var
derivating variable

                @return						CPLR_BAD
                                                                        CPLR_OK



**/

int d_sub(tree *my_tree, tree *to_tree, char *var) {
  char *name = "D SUB";

  CHECK_ARGS("D SUB");
  VERIFY1(my_tree->left == NULL || my_tree->right == NULL, CPLR_BAD,
          "%s: Adding operator has a null child", name);

  int ret = tree_burn(to_tree, TR_SIGN, '-');
  CHECK_BURN(name);

  CALL(d_node(my_tree->left, to_tree, LEFT, var));
  CALL(d_node(my_tree->right, to_tree, RIGHT, var));

  return CPLR_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

/**
                                                                        d_mul
derivating multiplying

                @param[out]					my_tree
argumented derivating tree
                @param[out]					to_tree
tree to build
                @param[out]					var
derivating variable

                @return						CPLR_BAD
                                                                        CPLR_OK



**/

int d_mul(tree *my_tree, tree *to_tree, char *var) {
  CHECK_ARGS("D MUL");

  int ret = tree_burn(to_tree, TR_SIGN, '+');
  CHECK_BURN("D DIV");

  tree *temp_tree = NULL;

  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree, "D MUL", TR_SIGN, LEFT,
                    '*'));
  TREE(to_tree->head);

  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree, "D MUL", TR_SIGN, RIGHT,
                    '*'));
  TREE(to_tree->head);

  CALL(tree_copy_add(my_tree->left, to_tree->right, LEFT, "D MUL"));
  TREE(to_tree->head);

  CALL(tree_copy_add(my_tree->right, to_tree->left, RIGHT, "D MUL"));
  TREE(to_tree->head);

  CALL(d_node(my_tree->right, to_tree->right, RIGHT, var));
  CALL(d_node(my_tree->left, to_tree->left, LEFT, var));

  return CPLR_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

/**
                                                                        d_div
derivating dividing

                @param[out]					my_tree
argumented derivating tree
                @param[out]					to_tree
tree to build
                @param[out]					var
derivating variable

                @return						CPLR_BAD
                                                                        CPLR_OK



**/

int d_div(tree *my_tree, tree *to_tree, char *var) {
  CHECK_ARGS("D DIV");

  int ret = tree_burn(to_tree, TR_SIGN, '/');
  CHECK_BURN("D DIV");
  tree *temp_tree = NULL;

  //------Denominator
  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree, "D DIV", TR_F, RIGHT,
                    "pow"));
  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree->right, "D DIV", TR_NONE,
                    RIGHT));
  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree->right->right, "D DIV",
                    TR_N, RIGHT, 2.0));
  CALL(tree_copy_add(my_tree->right, to_tree->right->right, LEFT, "D DIV"));
  //-------Term

  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree, "D DIV", TR_SIGN, LEFT,
                    '-'));
  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree->left, "D DIV", TR_SIGN,
                    LEFT, '*'));
  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree->left, "D DIV", TR_SIGN,
                    RIGHT, '*'));

  //------Structure done

  CALL(tree_copy_add(my_tree->left, to_tree->left->right, LEFT, "D DIV"));
  CALL(tree_copy_add(my_tree->right, to_tree->left->left, RIGHT, "D DIV"));
  CALL(d_node(my_tree->right, to_tree->left->right, RIGHT, var));
  CALL(d_node(my_tree->left, to_tree->left->left, LEFT, var));

  return CPLR_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

/**
                                                                        d_sin
derivating sin

                @param[out]					my_tree
argumented derivating tree
                @param[out]					to_tree
tree to build
                @param[out]					var
derivating variable

                @return						CPLR_BAD
                                                                        CPLR_OK
**/

int d_sin(tree *my_tree, tree *to_tree, char *var) {
  char *name = "D SIN";
  CHECK_ARGS("D SIN");

  int ret = tree_burn(to_tree, TR_SIGN, '*');
  CHECK_BURN(name);

  tree *temp_tree = NULL;

  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree, name, TR_SIGN, RIGHT,
                    '*'));
  CALL(d_node(my_tree->right, to_tree, LEFT, var));
  CALL(tree_copy_add(my_tree, to_tree->right, LEFT, name));
  TREE(to_tree->head);
  tree_save_string(to_tree->right->left, "cos");
  TREE(to_tree->head);
  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree->right, name, TR_N,
                    RIGHT, 1.0));
  TREE(to_tree->head);
  return CPLR_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

/**
                                                                        d_cos
derivating cos

                @param[out]					my_tree
argumented derivating tree
                @param[out]					to_tree
tree to build
                @param[out]					var
derivating variable

                @return						CPLR_BAD
                                                                        CPLR_OK
**/

int d_cos(tree *my_tree, tree *to_tree, char *var) {
  char *name = "D COS";
  CHECK_ARGS("D COS");

  int ret = tree_burn(to_tree, TR_SIGN, '*');
  CHECK_BURN(name);

  tree *temp_tree = NULL;

  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree, name, TR_SIGN, RIGHT,
                    '*'));
  CALL(d_node(my_tree->right, to_tree, LEFT, var));
  CALL(tree_copy_add(my_tree, to_tree->right, LEFT, name));
  TREE(to_tree->head);
  tree_save_string(to_tree->right->left, "sin");
  TREE(to_tree->head);
  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree->right, name, TR_N,
                    RIGHT, -1.0));
  TREE(to_tree->head);
  return CPLR_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

/**
                                                                        d_tg
derivating tan

                @param[out]					my_tree
argumented derivating tree
                @param[out]					to_tree
tree to build
                @param[out]					var
derivating variable

                @return						CPLR_BAD
                                                                        CPLR_OK
**/

int d_tg(tree *my_tree, tree *to_tree, char *var) {
  char *name = "D TG";

  CHECK_ARGS("D TG");
  int ret = tree_burn(to_tree, TR_SIGN, '/');
  CHECK_BURN(name);
  tree *temp_tree = NULL;

  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree, name, TR_SIGN, LEFT,
                    '*'));
  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree->left, name, TR_N, LEFT,
                    1.0));
  CALL(d_node(my_tree->right, to_tree->left, RIGHT, var));

  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree, name, TR_F, RIGHT,
                    "pow"));
  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree->right, name, TR_NONE,
                    RIGHT));
  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree->right->right, name,
                    TR_N, RIGHT, 2.0));
  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree->right->right, name,
                    TR_F, LEFT, "cos"));

  CALL(tree_copy_add(my_tree->right, to_tree->right->right->left, RIGHT, name));

  return CPLR_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

/**
                                                                        d_ctg
derivating cotan

                @param[out]					my_tree
argumented derivating tree
                @param[out]					to_tree
tree to build
                @param[out]					var
derivating variable

                @return						CPLR_BAD
                                                                        CPLR_OK
**/

int d_ctg(tree *my_tree, tree *to_tree, char *var) {
  char *name = "D CTG";

  CHECK_ARGS("D CTG");
  int ret = tree_burn(to_tree, TR_SIGN, '/');
  CHECK_BURN(name);
  tree *temp_tree = NULL;

  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree, name, TR_SIGN, LEFT,
                    '*'));
  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree->left, name, TR_N, LEFT,
                    -1.0));
  CALL(d_node(my_tree->right, to_tree->left, RIGHT, var));

  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree, name, TR_F, RIGHT,
                    "pow"));
  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree->right, name, TR_NONE,
                    RIGHT));
  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree->right->right, name,
                    TR_N, RIGHT, 2.0));
  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree->right->right, name,
                    TR_F, LEFT, "sin"));

  CALL(tree_copy_add(my_tree->right, to_tree->right->right->left, RIGHT, name));

  return CPLR_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

/**
                                                                        d_arcsin
derivating asin

                @param[out]					my_tree
argumented derivating tree
                @param[out]					to_tree
tree to build
                @param[out]					var
derivating variable

                @return						CPLR_BAD
                                                                        CPLR_OK
**/

int d_arcsin(tree *my_tree, tree *to_tree, char *var) {
  char *name = "D ARCSIN";

  CHECK_ARGS("D ARCSIN");

  int ret = tree_burn(to_tree, TR_SIGN, '/');
  CHECK_BURN(name);
  tree *temp_tree = NULL;

  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree, name, TR_SIGN, LEFT,
                    '*'));
  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree->left, name, TR_N, LEFT,
                    1.0));
  CALL(d_node(my_tree->right, to_tree->left, RIGHT, var));

  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree, name, TR_F, RIGHT,
                    "sqrt"));
  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree->right, name, TR_SIGN,
                    RIGHT, '-'));
  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree->right->right, name,
                    TR_N, LEFT, 1.0));

  tree *temp = to_tree->right->right;

  CALL(tree_init_va(&temp_tree, to_tree->head, temp, name, TR_F, RIGHT, "pow"));
  CALL(tree_init_va(&temp_tree, to_tree->head, temp->right, name, TR_NONE,
                    RIGHT));
  CALL(tree_init_va(&temp_tree, to_tree->head, temp->right->right, name, TR_N,
                    RIGHT, 2.0));

  CALL(tree_copy_add(my_tree->right, temp->right->right, LEFT, name));

  return CPLR_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

/**
                                                                        d_arccos
derivating acos

                @param[out]					my_tree
argumented derivating tree
                @param[out]					to_tree
tree to build
                @param[out]					var
derivating variable

                @return						CPLR_BAD
                                                                        CPLR_OK
**/

int d_arccos(tree *my_tree, tree *to_tree, char *var) {
  char *name = "D ARCCOS";

  CHECK_ARGS("D ARCCOS");

  int ret = tree_burn(to_tree, TR_SIGN, '/');
  CHECK_BURN(name);
  tree *temp_tree = NULL;

  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree, name, TR_SIGN, LEFT,
                    '*'));
  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree->left, name, TR_N, LEFT,
                    -1.0));
  CALL(d_node(my_tree->right, to_tree->left, RIGHT, var));

  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree, name, TR_F, RIGHT,
                    "sqrt"));
  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree->right, name, TR_SIGN,
                    RIGHT, '-'));
  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree->right->right, name,
                    TR_N, LEFT, 1.0));

  tree *temp = to_tree->right->right;

  CALL(tree_init_va(&temp_tree, to_tree->head, temp, name, TR_F, RIGHT, "pow"));
  CALL(tree_init_va(&temp_tree, to_tree->head, temp->right, name, TR_NONE,
                    RIGHT));
  CALL(tree_init_va(&temp_tree, to_tree->head, temp->right->right, name, TR_N,
                    RIGHT, 2.0));

  CALL(tree_copy_add(my_tree->right, temp->right->right, LEFT, name));

  return CPLR_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

/**
                                                                        d_arctg
derivating atan

                @param[out]					my_tree
argumented derivating tree
                @param[out]					to_tree
tree to build
                @param[out]					var
derivating variable

                @return						CPLR_BAD
                                                                        CPLR_OK
**/

int d_arctg(tree *my_tree, tree *to_tree, char *var) {
  char *name = "D ARCTG";
  CHECK_ARGS("D ARCTG");

  int ret = tree_burn(to_tree, TR_SIGN, '/');
  CHECK_BURN(name);
  tree *temp_tree = NULL;

  CALL(d_node(my_tree->right, to_tree, LEFT, var));
  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree, name, TR_SIGN, RIGHT,
                    '+'));
  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree->right, name, TR_N, LEFT,
                    1.0));
  /*
  CALL(tree_init_va(&temp_tree, to_tree -> head, to_tree -> right, name,
  TR_SIGN, RIGHT, '*')); CALL(tree_copy_add(my_tree -> right, to_tree -> right
  -> right, LEFT , name)); CALL(tree_copy_add(my_tree -> right, to_tree -> right
  -> right, RIGHT, name));
  */

  tree *temp = to_tree->right;

  CALL(tree_init_va(&temp_tree, to_tree->head, temp, name, TR_F, RIGHT, "pow"));
  CALL(tree_init_va(&temp_tree, to_tree->head, temp->right, name, TR_NONE,
                    RIGHT));
  CALL(tree_init_va(&temp_tree, to_tree->head, temp->right->right, name, TR_N,
                    RIGHT, 2.0));

  CALL(tree_copy_add(my_tree->right, temp->right->right, LEFT, name));

  return CPLR_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

/**
                                                                        d_log
derivating log

                @param[out]					my_tree
argumented derivating tree
                @param[out]					to_tree
tree to build
                @param[out]					var
derivating variable

                @return						CPLR_BAD
                                                                        CPLR_OK
**/

int d_log(tree *my_tree, tree *to_tree, char *var) {
  char *name = "D LOG";
  CHECK_ARGS("D LOG");

  int ret = tree_burn(to_tree, TR_SIGN, '/');
  CHECK_BURN(name);
  tree *temp_tree = NULL;

  //--------Term----------
  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree, name, TR_SIGN, LEFT,
                    '-'));

  //--------left item-----
  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree->left, name, TR_SIGN,
                    LEFT, '/'));
  tree *left_fraction = to_tree->left->left;
  CALL(tree_init_va(&temp_tree, to_tree->head, left_fraction, name, TR_SIGN,
                    LEFT, '*'));

  CALL(tree_init_va(&temp_tree, to_tree->head, left_fraction->left, name, TR_F,
                    LEFT, "ln"));
  CALL(tree_copy_add(my_tree->right->left, left_fraction->left->left, RIGHT,
                     name));
  CALL(d_node(my_tree->right->right, left_fraction->left, RIGHT, var));
  CALL(tree_copy_add(my_tree->right->right, left_fraction, RIGHT, name));

  //--------right item----
  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree->left, name, TR_SIGN,
                    RIGHT, '/'));
  tree *right_fraction = to_tree->left->right;
  CALL(tree_init_va(&temp_tree, to_tree->head, right_fraction, name, TR_SIGN,
                    LEFT, '*'));

  CALL(tree_init_va(&temp_tree, to_tree->head, right_fraction->left, name, TR_F,
                    LEFT, "ln"));
  CALL(tree_copy_add(my_tree->right->right, right_fraction->left->left, RIGHT,
                     name));
  CALL(d_node(my_tree->right->left, right_fraction->left, RIGHT, var));
  CALL(tree_copy_add(my_tree->right->left, right_fraction, RIGHT, name));

  //----denominator--------
  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree, name, TR_F, RIGHT,
                    "pow"));
  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree->right, name, TR_NONE,
                    RIGHT));
  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree->right->right, name,
                    TR_N, RIGHT, 2.0));

  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree->right->right, name,
                    TR_F, LEFT, "ln"));
  CALL(tree_copy_add(my_tree->right->left, to_tree->right->right->left, RIGHT,
                     name));

  return CPLR_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

/**
                                                                        d_ln
derivating ln

                @param[out]					my_tree
argumented derivating tree
                @param[out]					to_tree
tree to build
                @param[out]					var
derivating variable

                @return						CPLR_BAD
                                                                        CPLR_OK
**/

int d_ln(tree *my_tree, tree *to_tree, char *var) {
  char *name = "D LN";
  CHECK_ARGS("D LN");

  int ret = tree_burn(to_tree, TR_SIGN, '/');
  CHECK_BURN(name);

  CALL(tree_copy_add(my_tree->right, to_tree, RIGHT, name));
  CALL(d_node(my_tree->right, to_tree, LEFT, var));

  return CPLR_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

/**
                                                                        d_pow
derivating power

                @param[out]					my_tree
argumented derivating tree
                @param[out]					to_tree
tree to build
                @param[out]					var
derivating variable

                @return						CPLR_BAD
                                                                        CPLR_OK
**/

int d_pow(tree *my_tree, tree *to_tree,
          char *var) //(log(f(x), g(x)) = (f(x)^(g(x)-1)) *
                     //(g(x)f'(x)+f(x)ln(f(x))g'(x))
{
  char *name = "D POW";
  CHECK_ARGS("D POW");

  int ret = tree_burn(to_tree, TR_SIGN, '*');
  CHECK_BURN(name);
  tree *temp_tree = NULL;

  //------left factor------
  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree, name, TR_F, LEFT,
                    "pow"));
  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree->left, name, TR_NONE,
                    RIGHT));
  CALL(tree_copy_add(my_tree->right->left, to_tree->left->right, LEFT, name));
  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree->left->right, name,
                    TR_SIGN, RIGHT, '-'));

  tree *temp_sub = to_tree->left->right->right;
  CALL(tree_copy_add(my_tree->right->right, temp_sub, LEFT, name));
  CALL(tree_init_va(&temp_tree, to_tree->head, temp_sub, name, TR_N, RIGHT,
                    1.0));

  //--------right factor----
  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree, name, TR_SIGN, RIGHT,
                    '+'));
  //--------left part--------
  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree->right, name, TR_SIGN,
                    LEFT, '*'));
  CALL(tree_copy_add(my_tree->right->right, to_tree->right->left, LEFT, name));
  CALL(d_node(my_tree->right->left, to_tree->right->left, RIGHT, var));
  //--------right part-------
  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree->right, name, TR_SIGN,
                    RIGHT, '*'));
  tree *temp_mul = to_tree->right->right;
  CALL(tree_init_va(&temp_tree, to_tree->head, temp_mul, name, TR_SIGN, RIGHT,
                    '*'));
  CALL(tree_copy_add(my_tree->right->left, temp_mul->right, RIGHT, name));
  CALL(tree_init_va(&temp_tree, to_tree->head, temp_mul->right, name, TR_F,
                    LEFT, "ln"));
  CALL(tree_copy_add(my_tree->right->left, temp_mul->right->left, RIGHT, name));
  CALL(d_node(my_tree->right->right, temp_mul, LEFT, var));

  return CPLR_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

/**
                                                                        d_exp
derivating expponent

                @param[out]					my_tree
argumented derivating tree
                @param[out]					to_tree
tree to build
                @param[out]					var
derivating variable

                @return						CPLR_BAD
                                                                        CPLR_OK
**/

int d_exp(tree *my_tree, tree *to_tree, char *var) {
  char *name = "D EXP";
  CHECK_ARGS("D EXP");

  int ret = tree_burn(to_tree, TR_SIGN, '*');
  CHECK_BURN(name);

  CALL(tree_copy_add(my_tree, to_tree, LEFT, name));
  CALL(d_node(my_tree->right, to_tree, RIGHT, var));

  return CPLR_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

/**
                                                                        d_sqrt
derivating square root

                @param[out]					my_tree
argumented derivating tree
                @param[out]					to_tree
tree to build
                @param[out]					var
derivating variable

                @return						CPLR_BAD
                                                                        CPLR_OK
**/

int d_sqrt(tree *my_tree, tree *to_tree, char *var) {
  char *name = "D SQRT";
  CHECK_ARGS("D SQRT");

  int ret = tree_burn(to_tree, TR_SIGN, '/');
  CHECK_BURN(name);
  tree *temp_tree = NULL;

  CALL(d_node(my_tree->right, to_tree, LEFT, var));
  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree, name, TR_SIGN, RIGHT,
                    '*'));
  CALL(tree_init_va(&temp_tree, to_tree->head, to_tree->right, name, TR_N, LEFT,
                    2.0));
  CALL(tree_copy_add(my_tree, to_tree->right, RIGHT, name));

  return CPLR_OK;
}
