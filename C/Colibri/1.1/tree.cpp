/**
                @par			Tree library is contained here.

                                                V 1.03

                @par			Changelog V 1.01
                                                -- Added function optimization
(sin(5), log(6, 2.7))

                                                Changelog V 1.02
                                                -- Added node_insert() function



**/

#include "compiler.h"

extern FILE *strerr;
extern FILE *strlog;

/**
                is_there_num
that function checks. whether there's a number in front. That function has been
                                                                                                created because of bug with '+' and fscanf.
                @param[out]			strin
input file stream

                @return
1 - if yes, 0 - if no

**/

int is_there_num(FILE *strin);

/**
                head_ctr
constructor of head structure of tree. Contain information of current tree and
pointer to root element
                @param[out]			my_tree
pointer to the pointer of head_element

                @return
TREE_ARG_TREE_NULL - argumented tree pointer is NULL TREE_CALLOC_FAILED - calloc
failed to establish memory TREE_CTR_FAILED	- tree construction failed
                                                                                                TREE_OK
**/

int head_ctr(tree_head **my_tree);

/**
                tree_ctr
constructs tree element

                @param[out]			my_tree
pointer to pointer of tree

                @return
TREE_ARG_TREE_NULL - argumented tree pointer is NULL TREE_CALLOC_FAILED - calloc
failed to establish memory TREE_OK

**/

int tree_ctr(tree **my_tree, tree_head *my_head);

/**
                tree_print_elem_value
prints the value in output file print

                @param[out]			strout
output file stream
                @param[out]			my_tree
tree element

                @return
TREE_UNEXPECTED_TYPE - unknown type contained in tree element TREE_ARG_TREE_NULL
- argumented tree pointer is NULL TREE_OK
**/

int tree_print_elem_value(FILE *strout, tree *my_tree, char *extra_space);

/**
                tree_dump_in_order
creates dump print in argumented file stream

                @param[out]			strout
output file stream
                @param[out]			my_tree
tree

                @return
void
**/

void tree_dump_in_order(FILE *strout, tree *my_tree, char *space); //!!!!!!

/**
                tree_print_in_order
prints the tree in output stream, interpretating it as bracket construction

                @param[out]			strout
output stream
                @param[out]			my_tree
printing tree

                @return
TREE_ARG_STR_NULL -	argumented stream is NULL TREE_PRINT_ELEM_FAILED -
printing of some element failed TREE_OK
**/

int tree_print_in_order(FILE *strout, tree *my_tree);

/**
                tree_add_left
adds left tree element to current tree element

                @param[out]			my_tree
current tree element
                @param[out]			adding
adding tree (element)

                @return
TREE_OK TREE_INJURED - current tree is not OK TREE_ADD_INJURED - adding tree is
not OK TREE_ALREADY_THERE - there's left element already
**/

int tree_add_left(tree *my_tree, tree *adding);

/**
                tree_add_right
adds right tree element to current tree element

                @param[out]			my_tree
current tree element
                @param[out]			adding
adding tree (element)

                @return
TREE_OK TREE_INJURED - current tree is not OK TREE_ADD_INJURED - adding tree is
not OK TREE_ALREADY_THERE - there's right element already
**/

int tree_add_right(tree *my_tree, tree *adding);

/**
                tree_check
checks whether tree is valid or not

                @param[out]			my_tree
current tree
                @param[out]			size
pointer to the integer variable that will contain the size of tree

                @return[out]
TREE_CHECK_BAD TREE_CHECK_OK
**/

int tree_check(tree *my_tree, int *size);

/**
                tree_get_token
gets forward token from the stream and saves it to current element of tree,
saving its type to *type

                @param[out]			strin
input file stream
                @param[out]			my_tree
current tree element
                @param[out]			type
pointer to the variable that will contain type of scanned token

                @return
TREE_BAD - token hasn't been recognized TREE_OK
**/

// int tree_get_token(FILE* strin, tree* my_tree, int* type);

/**
                tree_read_in_order
scans argumented file stream for tree and interpretates it as a tree

                @param[out]			strin
input file stream
                @param[out]			my_tree
tree-to-save

                @return
TREE_INVALID_INPUT - invalid input TREE	_ARG_TREE_NULL - argumented tree pointer
is NULL TREE_ARG_STR_NULL -	argumented stream is NULL TREE_OK
**/

// int tree_read_in_order(FILE* strin, tree* my_tree);

/**
                tree_destr
destroys tree

                @param[out]			my_tree
destroying tree

                @return
TREE_OK TREE_BAD
**/

int tree_destr(tree *my_tree);

/**
                head_destr
the action depend on argument. It can destroy only head saving root pointer or
destroy the whole tree

                @param[out]			my_head
argumented head of tree
                @param				cond key

                @return
TREE_OK TREE_BAD
**/

int tree_burn(tree *my_tree, int type, ...);

/**
                        tree_burn
functions saves inputted tree type and it's value to the argumented tree

                        @param			my_tree
tree to burn
                        @param			type
saving tree type

                        @return
TREE_BAD TREE_OK
**/

int head_destr(tree_head *my_head, int cond, ...);

/**
                        head_destr
function destroys tree head and the whole tree depending on second parameter. If
the parameter is TREE_DESTR_HEAD, function is waiting for the tree** parameter
                                                                                                to save the root. Otherwise, the whole tree will be destroyed

                        @param			my_head
argumented head
                        @param			cond
deleting parameter

                        @return
TREE_OK or what tree_destr() returns


**/

int tree_delete(tree *my_tree, int side);

/**

                        tree_delete
function deletes the node and left or right tree, depending on parameter.
Another tree if it exists, will be sticked to the papa of current tree

                        @param[out]			my_tree
deleting tree
                        @param				side
the side that will be saved

                        @return
TREE_BAD TREE_OK
**/

void tree_save_int(tree *my_tree, int value);

/**
                        tree_save_int
function saves int value to the tree

                        @param[out]			my_tree
argumented tree
                        @param				value
what will be saved

**/

void tree_save_double(tree *my_tree, double value);

/**
                        tree_save_double
function saves double value to the tree

                        @param[out]			my_tree
argumented tree
                        @param				value
what will be saved
**/

void tree_save_string(tree *my_tree, char *word);

/**
                        tree_save_string
function that saves string to the tree

                        @param[out]			my_tree
argumented tree
                        @param[out]			word
saving string

**/

int tree_init(tree **dest_save_tree_token, tree_head *head_ptr,
              tree *tree_to_stick_to, char *func_name, int tree_type,
              int add_side);

/**
                        tree_init
function creates the node, burns it with type and head pointer and sticks to the
argumented tree to the argumented side

                        @param[out]			dest_save_tree_token
where the pointer to created tree will be saved
                        @param[out]			head_ptr
head pointer that will be save to create tree
                        @param[out]			tree_to_stick_to
you know:)
                        @param[out]			func_name
name of function that calls it. Necessary for debug printing
                        @param				tree_type
saving tree type
                        @param				add_side
sticking side

                        @return
SNTX_CTR_FAILED SNTX_BURN_FAILED SNTX_ADD_FAILED TREE_OK

**/

int tree_copy(tree *copied_tree, tree_head **copy);

/**
                        tree_copy
creates a copy of current tree

                        @param[out]			copied_tree
tree to copy
                        @param[out]			copy
pointer to head pointer, where the new tree will be saved

                        @return
TREE_OK
**/

int tree_optimize(tree *my_tree, bool *is_optimized);

/**
                        tree_optimize
function that proceeds some optimizations to the tree calculates system
"num-sign-num" and examples like 0 / var, var * 0

                        @param[out]			my_tree
tree to optimize
                        @param[out]			is_optimized
where true or false will be save, verifying were the tree optimized or not

                        @return
SNTX_DIV_BY_ZERO SNTX_OK
**/

void tree_save_head(tree *my_tree, tree_head *head);

/**
                        tree_save_head
updates the head pointer in each node of the tree

                        @param[out]			my_tree
updating tree pointer
                        @param[out]			head
updating head pointer
**/

int node_insert(tree *new_papa, tree **save_to, int side_papa, int side_child);

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int node_insert(tree *new_papa, tree **save_to, int side_papa, int side_child) {
  VERIFY(new_papa == NULL, TREE_BAD,
         "TREE INSERT: Argumented tree pointer is NULL");
  VERIFY(save_to == NULL, TREE_BAD,
         "TREE INSERT: Argumented tree save-to is NULL");
  VERIFY(side_papa != LEFT && side_papa != RIGHT, TREE_BAD,
         "TREE INSERT: Argumented side_papa is not LEFT or RIGHT");
  VERIFY(side_child != LEFT && side_child != RIGHT && side_child != NONE,
         TREE_BAD, "TREE INSERT: Argumented side_child is not LEFT or RIGHT");

  tree *new_node = NULL;

  int ret = tree_ctr(&new_node, new_papa->head);
  *save_to = new_node;
  VERIFY1(ret != TREE_OK, ret,
          "NODE INSERT: Tree construction failed, error [%d]", ret);

  new_node->papa = new_papa;
  new_node->head = new_papa->head;
  new_node->type = TR_NONE;

  (new_papa->head->size)++;
  tree *past_child = NULL;

  if (side_papa == LEFT) {
    past_child = new_papa->left;
    new_papa->left = new_node;
  } else {
    past_child = new_papa->right;
    new_papa->right = new_node;
  }

  if (past_child == NULL)
    return TREE_OK;

  if (side_child == NONE) {
    ret = tree_destr(past_child);
    VERIFY(ret != TREE_OK, TREE_BAD, "NODE INSERT: Tree destruction failed");
    return TREE_OK;
  }

  if (side_child == LEFT) {
    new_node->left = past_child;
    past_child->papa = new_node;
  } else {
    new_node->right = past_child;
    past_child->papa = new_node;
  }

  return TREE_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int tree_get_side(tree *my_tree, int *side) {
  assert(my_tree);
  if (my_tree->papa == NULL) {
    *side = NONE;
    return TREE_OK;
  }
  if (my_tree->papa->left == my_tree) {
    *side = LEFT;
    return TREE_OK;
  }
  if (my_tree->papa->right == my_tree) {
    *side = RIGHT;
    return TREE_OK;
  }

  VERIFY(true, TREE_BAD, "TREE GET SIDE: Bad papa linking");
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

bool is_num_leaf(tree *my_tree) //! That fucnction checks whether node is
                                //! numeric leaf with no children
{
  if (my_tree != NULL && my_tree->left == NULL && my_tree->right == NULL &&
      my_tree->type == TR_N)
    return true;
  return false;
};
#define IS_ZERO(num) (fabs((double)(num)) < 0.0000000000001)

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int calc_operand(double op1, double op2, int operand, double *res) {
  assert(res);
  switch (operand) {
  case '+':
    *res = op1 + op2;
    return 1;
  case '-':
    *res = op1 - op2;
    return 1;
  case '*':
    *res = op1 * op2;
    return 1;
  case '/':
    assert(op2 != 0);
    *res = op1 / op2;
    return 1;
  default:
    return 0;
  }
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

bool is_tree_value_num(tree *my_tree, double num) {
  assert(my_tree);
  if (my_tree->type == TR_N && IS_ZERO(*(double *)(my_tree->value) - num))
    return true;
  return false;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void clear_leafs(tree *my_tree) {
  assert(my_tree != NULL);
  int ret = TREE_OK;
  if (my_tree->left != NULL)
    ret = tree_destr(my_tree->left);
  my_tree->left = NULL;
  assert(ret == TREE_OK);
  if (my_tree->right != NULL)
    ret = tree_destr(my_tree->right);
  my_tree->right = NULL;
  assert(ret == TREE_OK);
}

bool calc_if_possible(tree *my_tree) {
  assert(my_tree);
  double res = 0;
  if (is_num_leaf(my_tree->left) && is_num_leaf(my_tree->right) &&
      my_tree->type == TR_SIGN) {

    calc_operand(*(double *)(my_tree->left->value),
                 *(double *)(my_tree->right->value), *(int *)(my_tree->value),
                 &res);

    clear_leafs(my_tree);

    DBG_FREE fprintf(stdout,
                     "[%08x] tree.cpp, calc_if_possible, my_tree -> value\n",
                     my_tree->value);
    free(my_tree->value);
    my_tree->value = NULL;

    my_tree->value = calloc(1, sizeof(double));
    assert(my_tree->value);
    *(double *)(my_tree->value) = res;
    my_tree->type = TR_N;
    return true;
  }
  return false;
}

bool calc_zero_operand(tree *my_tree) {
  assert(my_tree);
  int ret = 0;
  if (my_tree->type == TR_SIGN &&
      (*(int *)(my_tree->value) == '*' || *(int *)(my_tree->value) == '/') &&
      ((is_num_leaf(my_tree->left) &&
        IS_ZERO(*(double *)(my_tree->left->value))) ||
       (is_num_leaf(my_tree->right) &&
        IS_ZERO(*(double *)(my_tree->right->value))))) {
    clear_leafs(my_tree);

    DBG_FREE fprintf(stdout,
                     "[%08x] tree.cpp, calc_zero_operand, my_tree -> value\n",
                     my_tree->value);
    free(my_tree->value);

    my_tree->value = calloc(1, sizeof(double));
    assert(my_tree->value);
    *(double *)(my_tree->value) = 0.0;
    my_tree->type = TR_N;
    return true;
  }
  return false;
}

bool calc_operand_one(tree *my_tree) {
  assert(my_tree);
  int ret = 0;
  if ((my_tree->type == TR_SIGN && *(int *)(my_tree->value) == '*' &&
       (is_tree_value_num(my_tree->left, 1) ||
        is_tree_value_num(my_tree->right, 1))) ||
      (my_tree->type == TR_SIGN && *(int *)(my_tree->value) == '/' &&
       (is_tree_value_num(my_tree->right, 1)))) {
    if (is_tree_value_num(my_tree->left, 1)) {
      ret = tree_delete(my_tree, RIGHT);
      assert(ret == TREE_OK);
    } else {
      ret = tree_delete(my_tree, LEFT);
      assert(ret == TREE_OK);
    }
    return true;
  }
  return false;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

bool calc_sum_zero(tree *my_tree) {
  assert(my_tree);
  int ret = 0;
  if ((my_tree->type == TR_SIGN && *(int *)(my_tree->value) == '+' &&
       (is_tree_value_num(my_tree->left, 0) ||
        is_tree_value_num(my_tree->right, 0))) ||
      (my_tree->type == TR_SIGN && *(int *)(my_tree->value) == '-' &&
       (is_tree_value_num(my_tree->right, 0)))) {
    if (is_tree_value_num(my_tree->left, 0)) {
      ret = tree_delete(my_tree, RIGHT);
      assert(ret == TREE_OK);

    } else {
      ret = tree_delete(my_tree, LEFT);
      assert(ret == TREE_OK);
    }
    return true;
  }
  return false;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int tree_clear(tree *my_tree) {
  VERIFY(my_tree == NULL, TREE_ARG_TREE_NULL,
         "TREE CLEAR: Argumented tree pointer is NULL");
  my_tree->type = TR_NONE;
  if (my_tree->value != NULL) {
    DBG_FREE fprintf(stdout, "[%08x] tree.cpp, tree_clear, my_tree -> value\n",
                     my_tree->value);
    free(my_tree->value);
    my_tree->value = NULL;
  }
  return TREE_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#define DOUBLE(my_tree) *(double *)(my_tree->value)

int get_args(tree *my_tree, double *argv, const int argc) {
  assert(my_tree);
  assert(argv);
  assert(argc > 0);

  tree *temp_tree = my_tree->right;

  int i = 0;
  for (i = 0; i < argc - 1; ++i) {
    assert(temp_tree->left);
    argv[i] = DOUBLE(temp_tree->left);
    assert(temp_tree->right);
    temp_tree = temp_tree->right;
  }
  argv[i] = DOUBLE(temp_tree);

  return TREE_OK;
}

int count_args(tree *my_tree, int *argc) {
  assert(my_tree);
  assert(argc);

  tree *temp_tree = my_tree;
  int i = 0;

  while (i < MAXVARS && (temp_tree->type == TR_NONE || i == 0)) {
    if (temp_tree->type != TR_F)
      assert(temp_tree->left);
    assert(temp_tree->right);
    temp_tree = temp_tree->right;
    i++;
  }
  VERIFY1((i == MAXVARS && temp_tree->type == TR_NONE), TREE_BAD,
          "FUNC COUNT ARGS: Too many arguments for function [%08x]", my_tree);
  *argc = i;

  return TREE_OK;
}

#define WORD(my_tree) (char *)(my_tree->value)

int verify_func(tree *my_tree, const int argc, int *num) {
  assert(my_tree);
  assert(num);
  assert(argc > 0);

  int i = 0;
  for (i = 0; i < FUNC_NUM; ++i)
    if (strcmp(WORD(my_tree), (math_funcs[i]).name) == 0)
      break;
  VERIFY2(i == FUNC_NUM, TREE_BAD,
          "FUNC OPTIMIZE VERIFY: No such function found [%s][%08x]",
          WORD(my_tree), my_tree);
  if (argc != (math_funcs[i]).argc)
    tree_dump_in_order(strlog, my_tree, ">>");

  VERIFY3(argc != (math_funcs[i]).argc, TREE_BAD,
          "FUNC OPTIMIZE VERIFY: Argument cound doesn't match definition, got "
          "[%d], needed [%d], function [%s]",
          argc, (math_funcs[i]).argc, WORD(my_tree));
  *num = i;

  return TREE_OK;
}

bool is_possible_func_optimize(tree *my_tree, const int argc) {
  assert(my_tree);
  assert(argc > 0);

  tree *temp_tree = my_tree->right;
  for (int i = 1; i < argc; ++i) {
    assert(temp_tree->left);
    assert(temp_tree->right);
    if (temp_tree->left->type != TR_N)
      return false;
    temp_tree = temp_tree->right;
  }
  if (temp_tree->type != TR_N)
    return false;
  return true;
}

#define CALL(func)                                                             \
  if ((ret = func) != TREE_OK)                                                 \
    return ret;

int func_optimize(tree *my_tree, bool *is_optimized) {
  assert(my_tree);
  if (my_tree->type != TR_F)
    return TREE_OK;

  assert(is_optimized);
  assert(my_tree->right);

  int argc = 0;
  int ret = 0;
  int number_of_func = 0;

  CALL(count_args(my_tree, &argc));
  CALL(verify_func(my_tree, argc, &number_of_func));

  if (is_possible_func_optimize(my_tree, argc) == false)
    return TREE_OK;

  double argv[MAXVARS] = {};

  CALL(get_args(my_tree, argv, (const int)argc));

  double value = 0;

  CALL((math_funcs[number_of_func].func)(argv, &value));

  CALL(tree_destr(my_tree->right));
  CALL(tree_clear(my_tree));
  CALL(tree_burn(my_tree, TR_N, value));
  *is_optimized = true;

  return TREE_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int tree_optimize(tree *my_tree, bool *is_optimized) {
  assert(my_tree);
  assert(is_optimized);
  int ret = 0;
  // tree_dump(stdout, my_tree -> head);
  // fprintf(stdout, "I'm in [%08x]\n", my_tree);
  if (my_tree->left == NULL && my_tree->right == NULL)
    return SNTX_OK;

  if (my_tree->left != NULL) {
    ret = tree_optimize(my_tree->left, is_optimized);
    if (ret != SNTX_OK)
      return ret;
  }

  if (my_tree->right != NULL) {
    ret = tree_optimize(my_tree->right, is_optimized);
    if (ret != SNTX_OK)
      return ret;
  }

  // if (my_tree -> left == NULL || my_tree -> right == NULL) return SNTX_OK;

  if (my_tree->type == TR_SIGN && *(int *)(my_tree->value) == '/' &&
      my_tree->right != NULL && my_tree->right->type == TR_N &&
      IS_ZERO(*(double *)(my_tree->right->value)))
    return SNTX_DIV_BY_ZERO;

  double res = 0;

  bool cur_optimization = false;
  if (!(my_tree->left == NULL || my_tree->right == NULL)) {

    if (calc_if_possible(my_tree))
      *is_optimized = true;
    if (calc_zero_operand(my_tree))
      *is_optimized = true;
    if (calc_operand_one(my_tree))
      *is_optimized = true;
    if (calc_sum_zero(my_tree))
      *is_optimized = true;
  } else {
    //!				Optimizing functions, switched off by default
    // ret = func_optimize(my_tree, &cur_optimization);
    // VERIFY(ret != TREE_OK,		ret,	"TREE OPTIMIZE: Func optimize
    // failed"); if (cur_optimization) *is_optimized = true;
  }
  return SNTX_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int tree_init(tree **dest_save_tree_token, tree_head *head_ptr,
              tree *tree_to_stick_to, char *func_name, int tree_type,
              int add_side) {
  assert(dest_save_tree_token != NULL);
  assert(head_ptr != NULL);
  assert(tree_to_stick_to != NULL);
  assert(func_name != NULL);
  assert(add_side == LEFT || add_side == RIGHT);

  int ret = tree_ctr(dest_save_tree_token, head_ptr);
  VERIFY2(ret != TREE_OK, SNTX_CTR_FAILED, "%s: %s", func_name,
          sntx_errors[CTR_FAIL]);
  ret = tree_burn(*dest_save_tree_token, tree_type);
  VERIFY2(ret != TREE_OK, SNTX_BURN_FAILED, "%s: %s", func_name,
          sntx_errors[BURN_FAIL]);

  if (add_side == RIGHT)
    ret = tree_add_right(tree_to_stick_to, *dest_save_tree_token);
  else
    ret = tree_add_left(tree_to_stick_to, *dest_save_tree_token);

  VERIFY2(ret != TREE_OK, SNTX_ADD_FAILED, "%s: %s", func_name,
          sntx_errors[ADD_FAIL]);

  return TREE_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int rec_copy(tree *dest, tree *copying) {
  switch (copying->type) {
  case TR_N:
    tree_save_double(dest, *(double *)(copying->value));
    break;
  case TR_SIGN:
    tree_save_int(dest, *(int *)(copying->value));
    break;
  case TR_F:
  case TR_V:
    tree_save_string(dest, (char *)(copying->value));
    break;
  case TR_PGM:
  case TR_NONE:
    break;

  default:
    VERIFY1(true, CPLR_BAD, "WRONG TYPE OF TREE: GOT [%d]", copying->type);
  }
  dest->type = copying->type;
  int ret = 0;

  tree *temp_tree = NULL;
  if (copying->left != NULL) {
    ret = tree_ctr(&temp_tree, dest->head);
    assert(ret == TREE_OK);
    ret = tree_add_left(dest, temp_tree);
    assert(ret == TREE_OK);
    ret = rec_copy(dest->left, copying->left);
  }
  if (copying->right != NULL) {
    ret = tree_ctr(&temp_tree, dest->head);
    assert(ret == TREE_OK);
    ret = tree_add_right(dest, temp_tree);
    assert(ret == TREE_OK);
    ret = rec_copy(dest->right, copying->right);
  }

  return TREE_OK;
}

int tree_copy(tree *copied_tree, tree_head **copy) {
  assert(copy);
  assert(copied_tree);

  int ret = head_ctr(copy);
  assert(ret == TREE_OK);

  ret = rec_copy((*copy)->root, copied_tree);
  assert(ret == TREE_OK);

  return TREE_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int tree_delete(tree *my_tree, int side) {
  int _size = 0;
  VERIFY(my_tree == NULL, TREE_BAD,
         "TREE DELETE: Argumented tree pointer is null");
  VERIFY(tree_check(my_tree->head->root, &_size) != TREE_CHECK_OK, TREE_BAD,
         "TREE DELETE: Tree is not ok");
  VERIFY(my_tree->papa == NULL, TREE_BAD,
         "TREE DELETE: Argumented tree must have papa");

  int ret = 0;
  int temp_ret = TREE_OK;

  int type = my_tree->type;

  if (type == TR_V || type == TR_F || type == TR_STR || type == TR_N ||
      type == TR_ASSN || type == TR_SIGN || type == TR_CMP) {
    DBG_FREE fprintf(stdout, "[%08x] tree.cpp, tree_delete, my_tree -> value\n",
                     my_tree->value);
    free(my_tree->value);
    my_tree->value = NULL;
  }

  tree *_temp = NULL;
  tree *root = my_tree->head->root;

  if (side == LEFT && my_tree->left != NULL) {
    _temp = my_tree->left;
    my_tree->left->papa = my_tree->papa;
  }
  if (side == RIGHT && my_tree->left != NULL) {
    _temp = my_tree->right;
    my_tree->right->papa = my_tree->papa;
  }

  if (my_tree->papa->right == my_tree)
    my_tree->papa->right = _temp;
  if (my_tree->papa->left == my_tree)
    my_tree->papa->left = _temp;

  if (my_tree->left == _temp)
    my_tree->left = NULL;
  if (my_tree->right == _temp)
    my_tree->right = NULL;

  if (my_tree->left != NULL) {
    ret = tree_destr(my_tree->left);
    my_tree->left = NULL;
    VERIFY(ret != TREE_OK, ret, "TREE DELETE: Tree hasn't been destroyed");
  }

  if (my_tree->right != NULL) {
    ret = tree_destr(my_tree->right);
    my_tree->right = NULL;
    VERIFY(ret != TREE_OK, ret, "TREE DELETE: Tree hasn't been destroyed");
  }

  my_tree->left = NULL;
  my_tree->right = NULL;
  my_tree->papa = NULL;
  my_tree->value = NULL;
  my_tree->type = POISON;
  my_tree->head->size -= 1;

  DBG_FREE fprintf(stdout, "[%08x] tree.cpp, tree_delete, my_tree\n", my_tree);
  free(my_tree);
  my_tree = NULL;

  _size = 0;
  VERIFY(tree_check(root, &_size) != TREE_CHECK_OK, TREE_BAD,
         "TREE DELETE: Tree injured in the end");
  return TREE_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int tree_burn(tree *my_tree, int type, ...) {
  PRECOND(my_tree == NULL, TREE_ARG_TREE_NULL,
          "TREE INIT: argumented head pointer is NULL\n");
  // PRECOND((my_tree -> type != TR_NONE)||(my_tree -> value != NULL), TREE_BAD,
  // "TREE UNIT: tree has been already initialized");
  int _size = 0;
  VERIFY(tree_check(my_tree, &_size) != TREE_CHECK_OK, TREE_BAD,
         "TREE INIT: Initialization failed, tree is not ok");
  va_list vl;
  va_start(vl, type);
  char *str = NULL;
  double val = 0;
  int int_val = 0;
  if (my_tree->value) {
    DBG_FREE fprintf(stdout, "[%08x] tree.cpp, tree_burn, my_tree -> value\n",
                     my_tree->value);
    free(my_tree->value);
    my_tree->value = NULL;
  }

  switch (type) {
  case TR_V:
  case TR_STR:
  case TR_F:
    str = va_arg(vl, char *);
    VERIFY(strlen(str) >= MAXLINE, TREE_BAD,
           "TREE INIT: Argumented string is out of range");
    my_tree->value = (void *)calloc(strlen(str) + 2, sizeof(char));
    assert(my_tree->value);
    strcpy((char *)(my_tree->value), str);

    break;
  case TR_N:
    val = va_arg(vl, double);
    my_tree->value = (void *)calloc(1, sizeof(double));
    assert(my_tree->value);
    *((double *)(my_tree->value)) = val;
    break;
  case TR_SIGN:
  case TR_ASSN:
  case TR_CMP:
    int_val = va_arg(vl, int);
    my_tree->value = (void *)calloc(1, sizeof(int));
    assert(my_tree->value);
    *((int *)(my_tree->value)) = int_val;
    break;
  default:
    break;
  }

  my_tree->type = type;

  _size = 0;

  va_end(vl);
  POSTCOND(tree_check(my_tree, &_size) != TREE_CHECK_OK, TREE_BAD,
           "TREE INIT: Initialization failed, tree is not ok in the end");
  return TREE_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int is_there_num(FILE *strin) {
  int c = 0;
  while (isspace(c = getc(strin)))
    ;
  if (isdigit(c)) {
    ungetc(c, strin);
    return 1;
  }
  int cc = getc(strin);
  if (((c == '-') || (c == '+')) && (isdigit(cc))) {
    ungetc(cc, strin);
    ungetc(c, strin);
    return 1;
  }
  ungetc(cc, strin);
  ungetc(c, strin);
  return 0;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int head_ctr(tree_head **my_tree) {
  PRECOND(my_tree == NULL, TREE_ARG_TREE_NULL,
          "# HEAD CTR ERROR: argumented head pointer is NULL\n");

  (*my_tree) = (tree_head *)calloc(1, sizeof(tree_head));
  VERIFY((*my_tree) == NULL, TREE_CALLOC_FAILED,
         "# HEAD CTR ERROR: Calloc failed to establish memory for head\n");
  (*my_tree)->size = 1;

  int ret = tree_ctr(&((*my_tree)->root), (*my_tree));

  VERIFY1(ret != TREE_OK, TREE_CTR_FAILED,
          "# HEAD CTR ERROR: TREE_CTR() failed to construct tree, error [%d]\n",
          ret);

  return TREE_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int tree_ctr(tree **my_tree, tree_head *my_head) {
  PRECOND(my_tree == NULL, TREE_ARG_TREE_NULL,
          "# TREE CTR ERROR: argumented tree pointer is NULL\n");
  *my_tree = (tree *)calloc(1, sizeof(tree));
  assert(*my_tree);
  VERIFY(my_tree == NULL, TREE_CALLOC_FAILED,
         "# TREE CTR ERROR: Calloc failed to establish memory\n");
  (*my_tree)->papa = NULL;
  (*my_tree)->left = NULL;
  (*my_tree)->right = NULL;
  (*my_tree)->head = my_head;
  (*my_tree)->value = NULL;
  (*my_tree)->type = TR_NONE;

  return TREE_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int tree_print_elem_value(FILE *strout, tree *my_tree, char *extra_space) {
  VERIFY(my_tree == NULL, TREE_ARG_TREE_NULL,
         "PRINT TREE ELEMENT: Argumented tree pointer is NULL");
  VERIFY(strout == NULL, TREE_ARG_TREE_NULL,
         "PRINT TREE ELEMENT: Argumented file stream is NULL");
  VERIFY(extra_space == NULL, TREE_ARG_TREE_NULL,
         "PRINT TREE ELEMENT: Argumented space is NULL");
  int _size = 0;
  VERIFY(tree_check(my_tree, &_size) != TREE_CHECK_OK, TREE_INJURED,
         "PRINT TREE ELEMENT: Tree is not OK");

  fprintf(strout, "[%s", tree_types_strings[my_tree->type - TR_V]);

  switch (my_tree->type) {
  case TR_V:
  case TR_STR:
  case TR_F:
    fprintf(strout, " | %s", (char *)(my_tree->value));
    break;
  case TR_SIGN:
    fprintf(strout, " | %c", (char)(*(int *)(my_tree->value)));
    break;
  case TR_ASSN:
  case TR_CMP:
    fprintf(strout, " | %d", *(int *)(my_tree->value));
    break;
  case TR_N:
    fprintf(strout, " | %lg", *((double *)(my_tree->value)));
    break;
  default:
    break;
  }
  fputc(']', strout);
  fprintf(strout, "%s", extra_space);
  return TREE_OK;

  /*
  switch (my_tree -> type)
  {
  case '8':
          fprintf(strout, "%lg%s", my_tree -> value, extra_space);
          break;
  case '+':
  case '-':
  case '*':
  case '/':
          fprintf(strout, "%c%s", my_tree -> type, extra_space);
          break;
  default:
          return TREE_UNEXPECTED_TYPE;
  }
  return TREE_OK;
  */
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void tree_dump_print_elem(FILE *strout, tree *my_tree) {
  int ret = tree_print_elem_value(strout, my_tree, "");
  fputc('{', strout);
  fprintf(strout, "%08x", my_tree);
  fputc('}', strout);
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#define DRAW_BRANCH_(side)                                                     \
  fprintf(strout, "%s|\n", space);                                             \
  fprintf(strout, "%s" #side "---", space);

void tree_dump_in_order(FILE *strout, tree *my_tree, char *space) {
  if (strout == NULL)
    strout = strerr;
  assert(strout != NULL);
  assert(my_tree);

  fputc('+', strout);

  tree_dump_print_elem(strout, my_tree);
  fputc('\n', strout);

  DRAW_BRANCH_(L);

  char next_space[MAXLINE * 100] = {};
  sprintf(next_space, "%s|   ", space); // 4 spaces

  if (my_tree->left == NULL)
    fprintf(strout, "%s\n", nil);
  else
    tree_dump_in_order(strout, my_tree->left, next_space);

  DRAW_BRANCH_(R);
  sprintf(next_space, "%s    ", space);
  if (my_tree->right == NULL)
    fprintf(strout, "%s\n", nil);
  else
    tree_dump_in_order(strout, my_tree->right, next_space);
}

int tree_dump(FILE *strout, tree_head *my_head) {
  if (strout == NULL)
    strout = strerr;
  assert(strout);
  VERIFY(my_head == NULL, TREE_BAD, "TREE HEAD ERROR: head pointer is NULL\n");

  fprintf(strout, "Dump of tree - [%08x], size - %d\n", my_head, my_head->size);
  int tree_size = 0;
  fprintf(strout, "I'm %s\n",
          (tree_check(my_head->root, &tree_size) == TREE_CHECK_OK &&
           my_head->size == tree_size)
              ? "OK"
              : "BAD");
  fprintf(strout, "Counted size = %d\n", tree_size);
  fprintf(strout, "Calling recursive in-order dump of tree root...\n\n");

  tree_dump_in_order(strout, my_head->root, "");

  fprintf(strout, "End of tree dump\n");

  return TREE_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/*
int tree_print_in_order(FILE* strout, tree* my_tree)
{
        if (my_tree -> left  != NULL) VERIFY(my_tree -> left  -> papa !=
my_tree, TREE_ARG_STR_NULL  , "# TREE PRINT ERROR: [%08x] tree element is broken
(left link)\n" _ my_tree); if (my_tree -> right != NULL) VERIFY(my_tree -> right
-> papa != my_tree, TREE_ARG_STR_NULL  , "# TREE PRINT ERROR: [%08x] tree
element is broken (right link)\n" _ my_tree);

        fprintf(strout, "( ");
        if (my_tree -> left == NULL) fprintf(strout, " ");
        else tree_print_in_order(strout, my_tree -> left);

        int ret = 0;
        if ((ret = tree_print_elem_value(strout, my_tree, " ")) != TREE_OK)
return TREE_PRINT_ELEM_FAILED;

        if (my_tree -> right == NULL) fprintf(strout, "%s "" ");
        else tree_print_in_order(strout, my_tree -> right);
        fprintf(strout, ") ");

        return TREE_OK;
}
*/

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#define RETURN_BAD(error, msg)                                                 \
  {                                                                            \
    *size = 0;                                                                 \
    ERR(msg);                                                                  \
    return error;                                                              \
  }
#define RETURN_BAD1(error, msg, arg1)                                          \
  {                                                                            \
    *size = 0;                                                                 \
    VERIFY1(true, error, msg, arg1);                                           \
  }

int tree_check(
    tree *my_tree,
    int *size) /*and function pointer, that checks value of tree, general*/
{
  assert(my_tree);
  if (size == NULL) {
    int _size = 0;
    size = &_size;
  }

  if (*size > MAXTREE)
    RETURN_BAD(TREE_CHECK_OVERFLOW, "TREE CHECK: Size is out of range");
  if (!((TR_V <= my_tree->type) && (my_tree->type <= TR_NONE)))
    RETURN_BAD1(TREE_CHECK_BAD_TYPE,
                "TREE CHECK: Invalid type of tree, got [%d]", my_tree->type);
  if (((my_tree->type == TR_V) || (my_tree->type == TR_F) ||
       (my_tree->type == TR_STR)) &&
      (strlen((char *)(my_tree->value)) >= MAXLINE))
    RETURN_BAD(TREE_CHECK_STR_BROKEN, "TREE CHECK: String is broken");

  if ((my_tree->right != NULL) && (my_tree->right->papa != my_tree))
    RETURN_BAD(TREE_CHECK_BAD_LINK,
               "TREE CHECK: Invalid linking, right - papa");
  if ((my_tree->left != NULL) && (my_tree->left->papa != my_tree))
    RETURN_BAD(TREE_CHECK_BAD_LINK, "TREE CHECK: Invalid linking, left - papa");

  if (my_tree->head == NULL)
    RETURN_BAD(TREE_CHECK_NO_HEAD, "TREE CHECK: No head pointer");
  if (my_tree->head->root == NULL)
    RETURN_BAD(TREE_CHECK_NO_ROOT, "TREE CHECK: No root pointer in the head");

  int ret = TREE_CHECK_OK;
  if (my_tree->right != NULL)
    ret = tree_check(my_tree->right, size);
  if (ret != TREE_CHECK_OK)
    return ret;
  if (my_tree->left != NULL)
    ret = tree_check(my_tree->left, size);
  if (ret != TREE_CHECK_OK)
    return ret;

  if ((my_tree->left != NULL) && (my_tree->left == my_tree->right))
    RETURN_BAD(TREE_CHECK_BAD_LINK,
               "TREE CHECK: left and right pointers are the same");
  if ((my_tree->left != NULL) && (my_tree->left == my_tree->papa))
    RETURN_BAD(TREE_CHECK_BAD_LINK,
               "TREE CHECK: left and papa pointers are the same");
  if ((my_tree->papa != NULL) && (my_tree->papa == my_tree->right))
    RETURN_BAD(TREE_CHECK_BAD_LINK,
               "TREE CHECK: right and papa pointers are the same");

  if (size != NULL)
    (*size)++;
  return ret;
}

#undef RETURN_BAD_

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void tree_save_head(tree *my_tree, tree_head *head) {
  assert(my_tree != NULL);
  assert(head != NULL);
  my_tree->head = head;

  if (my_tree->left != NULL)
    tree_save_head(my_tree->left, head);
  if (my_tree->right != NULL)
    tree_save_head(my_tree->right, head);
}

int tree_add_left(tree *my_tree, tree *adding) {
  assert(my_tree != NULL);
  assert(adding != NULL);

  PRECOND(tree_check(my_tree->head->root, NULL) != TREE_CHECK_OK, TREE_BAD,
          "ADD LEFT ERROR: PRECONDITION FAILED\n");
  int tr_counter = 0;
  VERIFY1(tree_check(my_tree, &tr_counter) == TREE_CHECK_BAD, TREE_INJURED,
          "# ADD LEFT ERROR: [%08x] element, tree is broken\n", my_tree);
  tr_counter = 0;
  VERIFY(tree_check(adding, &tr_counter) == TREE_CHECK_BAD, TREE_ADD_INJURED,
         "# ADD LEFT ERROR: [%08] adding element, tree is broken\n");

  if (my_tree->left != NULL)
    return TREE_ALREADY_THERE;
  my_tree->left = adding;

  if (adding->papa != NULL) {
    if (adding->papa->left == adding)
      adding->papa->left = NULL;
    if (adding->papa->right == adding)
      adding->papa->right = NULL;
  }
  adding->papa = my_tree;
  adding->head = my_tree->head;
  adding->head->size += tr_counter;
  assert(my_tree->head);
  tree_save_head(adding, my_tree->head);
  POSTCOND(tree_check(my_tree->head->root, NULL) != TREE_CHECK_OK, TREE_BAD,
           "ADD LEFT ERROR: POSTCONDITION FAILED\n");
  return TREE_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int tree_add_right(tree *my_tree, tree *adding) {
  assert(my_tree != NULL);
  assert(adding != NULL);

  PRECOND(tree_check(my_tree->head->root, NULL) != TREE_CHECK_OK, TREE_BAD,
          "ADD LEFT ERROR: PRECONDITION FAILED\n");
  int tr_counter = 0;
  VERIFY1(tree_check(my_tree, &tr_counter) == TREE_CHECK_BAD, TREE_INJURED,
          "# ADD RIGHT ERROR: [%08x] element, tree is broken\n", my_tree);
  tr_counter = 0;
  VERIFY1(tree_check(adding, &tr_counter) == TREE_CHECK_BAD, TREE_ADD_INJURED,
          "# ADD RIGHT ERROR: [%08x] adding element, tree is broken\n", adding);

  if (my_tree->right != NULL)
    return TREE_ALREADY_THERE;
  my_tree->right = adding;

  if (adding->papa != NULL) {
    if (adding->papa->left == adding)
      adding->papa->left = NULL;
    if (adding->papa->right == adding)
      adding->papa->right = NULL;
  }
  adding->papa = my_tree;
  adding->head = my_tree->head;
  adding->head->size += tr_counter;
  assert(my_tree->head);
  tree_save_head(adding, my_tree->head);
  POSTCOND(tree_check(my_tree->head->root, NULL) != TREE_CHECK_OK, TREE_BAD,
           "ADD LEFT ERROR: POSTCONDITION FAILED\n");
  return TREE_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int tree_destr(tree *my_tree) {
  assert(my_tree);
  int ret = 0;
  int temp_ret = TREE_OK;
  if ((my_tree->left != NULL) && (my_tree->left->papa != my_tree))
    temp_ret = TREE_BAD;
  if ((my_tree->right != NULL) && (my_tree->right->papa != my_tree))
    temp_ret = TREE_BAD;

  if (my_tree->left != NULL)
    temp_ret = tree_destr(my_tree->left);
  if (temp_ret != TREE_OK)
    ret = temp_ret;
  if (my_tree->right != NULL)
    temp_ret = tree_destr(my_tree->right);
  if (temp_ret != TREE_OK)
    ret = temp_ret;

  if (my_tree->papa != NULL) {
    if (my_tree->papa->left == my_tree)
      my_tree->papa->left = NULL;
    if (my_tree->papa->right == my_tree)
      my_tree->papa->right = NULL;
  }

  int type = my_tree->type;

  if (type == TR_V || type == TR_F || type == TR_STR || type == TR_N ||
      type == TR_ASSN || type == TR_SIGN || type == TR_CMP) {
    DBG_FREE fprintf(stdout, "[%08x] tree.cpp, tree_destr, my_tree -> value\n",
                     my_tree->value);
    free(my_tree->value);
    my_tree->value = NULL;
  }

  my_tree->head->size -= 1;
  my_tree->left = NULL;
  my_tree->right = NULL;
  my_tree->papa = NULL;
  my_tree->value = NULL;
  my_tree->type = POISON;
  DBG_FREE fprintf(stdout, "[%08x] tree.cpp, tree_destr, my_tree\n", my_tree);
  free(my_tree);
  my_tree = NULL;

  return temp_ret;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int head_destr(tree_head *my_head, int cond, ...) {
  tree **ret_tree = NULL;
  if (cond == TREE_DESTR_HEAD) {
    va_list args;
    va_start(args, cond);
    ret_tree = va_arg(args, tree **);
    va_end(args);
  }
  tree *tree_head = my_head->root;
  my_head->root = NULL;
  my_head->size = POISON;
  DBG_FREE fprintf(stdout, "[%08x] tree.cpp, head_destr, my_head\n", my_head);
  free(my_head);
  my_head = NULL;
  if (cond == TREE_DESTR_HEAD) {
    *ret_tree = tree_head;
    return TREE_OK;
  } else {
    int ret = tree_destr(tree_head);
    return ret;
  }
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void tree_save_int(tree *my_tree, int value) {
  assert(my_tree != NULL);
  if (my_tree->value != NULL) {
    free(my_tree->value);
    DBG_FREE fprintf(stdout,
                     "[%08x] tree.cpp, tree_save_int, my_tree -> value\n",
                     my_tree->value);
    my_tree->value = NULL;
  }
  my_tree->value = calloc(1, sizeof(int));
  assert(my_tree->value);
  *(int *)(my_tree->value) = value;
}

void tree_save_double(tree *my_tree, double value) {
  assert(my_tree != NULL);
  if (my_tree->value != NULL) {
    free(my_tree->value);
    DBG_FREE fprintf(stdout,
                     "[%08x] tree.cpp, tree_save_double, my_tree -> value\n",
                     my_tree->value);
    my_tree->value = NULL;
  }
  my_tree->value = calloc(1, sizeof(double));
  assert(my_tree->value);
  *(double *)(my_tree->value) = value;
}

void tree_save_string(tree *my_tree, char *word) {
  assert(my_tree != NULL);
  assert(word != NULL);
  assert(strlen(word) < MAXLINE);

  if (my_tree->value != NULL) {
    free(my_tree->value);
    DBG_FREE fprintf(stdout,
                     "[%08x] tree.cpp, tree_save_string, my_tree -> value\n",
                     my_tree->value);
    my_tree->value = NULL;
  }
  my_tree->value = calloc(strlen(word) + 2, sizeof(char));
  assert(my_tree->value);
  strcpy((char *)(my_tree->value), word);
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
