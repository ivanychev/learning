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

**/

int head_destr(tree_head *my_head, int cond, ...);

int tree_delete(tree *my_tree, int side);

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

bool is_num_leaf(tree *my_tree) {
  if (my_tree != NULL && my_tree->left == NULL && my_tree->right == NULL &&
      my_tree->type == TR_N)
    return true;
  return false;
};
#define IS_ZERO(num) (fabs((double)(num)) < 0.0000000000001)

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int calc_operand(double op1, double op2, int operand, double *res) {
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

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int tree_optimize(tree *my_tree, bool *is_optimised) {
  assert(my_tree);
  assert(is_optimised);
  int ret = 0;
  if (my_tree->left == NULL && my_tree->right == NULL)
    return SNTX_OK;

  if (my_tree->left != NULL) {
    ret = tree_optimize(my_tree->left, is_optimised);
    if (ret != SNTX_OK)
      return ret;
  }
  if (my_tree->right != NULL) {
    ret = tree_optimize(my_tree->right, is_optimised);
    if (ret != SNTX_OK)
      return ret;
  }

  if (my_tree->left == NULL || my_tree->right == NULL)
    return SNTX_OK;

  if (my_tree->type == TR_SIGN && *(int *)(my_tree->value) == '/' &&
      my_tree->right != NULL && my_tree->right->type == TR_N &&
      IS_ZERO(*(double *)(my_tree->right->value)))
    return SNTX_DIV_BY_ZERO;

  double res = 0;

  if (is_num_leaf(my_tree->left) & is_num_leaf(my_tree->right) &
      my_tree->type == TR_SIGN) {

    calc_operand(*(double *)(my_tree->left->value),
                 *(double *)(my_tree->right->value), *(int *)(my_tree->value),
                 &res);

    clear_leafs(my_tree);

    free(my_tree->value);
    my_tree->value = calloc(1, sizeof(double));
    *(double *)(my_tree->value) = res;
    my_tree->type = TR_N;
    *is_optimised = true;
    return SNTX_OK;
  }

  if (my_tree->type == TR_SIGN &&
      (*(int *)(my_tree->value) == '*' || *(int *)(my_tree->value) == '/') &&
      ((is_num_leaf(my_tree->left) &&
        IS_ZERO(*(double *)(my_tree->left->value))) ||
       (is_num_leaf(my_tree->right) &&
        IS_ZERO(*(double *)(my_tree->right->value))))) {
    clear_leafs(my_tree);

    free(my_tree->value);
    my_tree->value = calloc(1, sizeof(double));
    *(double *)(my_tree->value) = 0.0;
    my_tree->type = TR_N;
    *is_optimised = true;
    return SNTX_OK;
  }

  if ((my_tree->type == TR_SIGN && *(int *)(my_tree->value) == '*' &&
       (is_tree_value_num(my_tree->left, 1) ||
        is_tree_value_num(my_tree->right, 1))) ||
      (my_tree->type == TR_SIGN && *(int *)(my_tree->value) == '/' &&
       (is_tree_value_num(my_tree->right, 1)))) {
    if (is_tree_value_num(my_tree->left, 1)) {
      tree_delete(my_tree, RIGHT);
    } else {
      tree_delete(my_tree, LEFT);
    }
    *is_optimised = true;
    return SNTX_OK;
  }

  if ((my_tree->type == TR_SIGN && *(int *)(my_tree->value) == '+' &&
       (is_tree_value_num(my_tree->left, 0) ||
        is_tree_value_num(my_tree->right, 0))) ||
      (my_tree->type == TR_SIGN && *(int *)(my_tree->value) == '-' &&
       (is_tree_value_num(my_tree->right, 0)))) {
    if (is_tree_value_num(my_tree->left, 0)) {
      tree_delete(my_tree, RIGHT);
    } else {
      tree_delete(my_tree, LEFT);
    }
    *is_optimised = true;
    return SNTX_OK;
  }

  return SNTX_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int tree_delete(tree *my_tree, int side) {
  // assert(my_tree);
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
      type == TR_ASSN || type == TR_SIGN || type == TR_CMP)
    free(my_tree->value);

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
    VERIFY(ret != TREE_OK, ret, "TREE DELETE: Tree hasn't been destroyed");
  }

  if (my_tree->right != NULL) {
    ret = tree_destr(my_tree->right);
    VERIFY(ret != TREE_OK, ret, "TREE DELETE: Tree hasn't been destroyed");
  }

  my_tree->left = NULL;
  my_tree->right = NULL;
  my_tree->papa = NULL;
  my_tree->value = NULL;
  my_tree->type = POISON;
  my_tree->head->size -= 1;
  free(my_tree);

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
  PRECOND((my_tree->type != TR_NONE) || (my_tree->value != NULL), TREE_BAD,
          "TREE UNIT: tre has been already initialized");
  int _size = 0;
  VERIFY(tree_check(my_tree, &_size) != TREE_CHECK_OK, TREE_BAD,
         "TREE INIT: Initialization failed, tree is not ok");
  va_list vl;
  va_start(vl, type);
  char *str = NULL;
  double val = 0;
  int int_val = 0;

  switch (type) {
  case TR_V:
  case TR_STR:
  case TR_F:
    str = va_arg(vl, char *);
    VERIFY(strlen(str) >= MAXLINE, TREE_BAD,
           "TREE INIT: Argumented string is out of range");
    my_tree->value = (void *)calloc(strlen(str) + 1, sizeof(char));
    strcpy((char *)(my_tree->value), str);

    break;
  case TR_N:
    val = va_arg(vl, double);
    my_tree->value = (void *)calloc(1, sizeof(double));
    *((double *)(my_tree->value)) = val;
    break;
  case TR_SIGN:
  case TR_ASSN:
  case TR_CMP:
    int_val = va_arg(vl, int);
    my_tree->value = (void *)calloc(1, sizeof(int));
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

  VERIFY(ret != TREE_OK, TREE_CTR_FAILED,
         "# HEAD CTR ERROR: TREE_CTR() failed to construct tree, error [%d]\n" _
             ret);

  return TREE_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int tree_ctr(tree **my_tree, tree_head *my_head) {
  PRECOND(my_tree == NULL, TREE_ARG_TREE_NULL,
          "# TREE CTR ERROR: argumented tree pointer is NULL\n");
  *my_tree = (tree *)calloc(1, sizeof(tree));
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

  fputc('+', strout);

  tree_dump_print_elem(strout, my_tree);
  fputc('\n', strout);

  DRAW_BRANCH_(L);

  char next_space[MAXLINE] = {};
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
    RETURN_BAD(TREE_CHECK_BAD_TYPE,
               "TREE CHECK: Invalid type of tree, got [%d]" _ my_tree->type);
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

int tree_add_left(tree *my_tree, tree *adding) {
  PRECOND(tree_check(my_tree->head->root, NULL) != TREE_CHECK_OK, TREE_BAD,
          "ADD LEFT ERROR: PRECONDITION FAILED\n");
  int tr_counter = 0;
  VERIFY(tree_check(my_tree, &tr_counter) == TREE_CHECK_BAD, TREE_INJURED,
         "# ADD LEFT ERROR: [%08x] element, tree is broken\n");
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
  adding->head->size += 1;
  POSTCOND(tree_check(my_tree->head->root, NULL) != TREE_CHECK_OK, TREE_BAD,
           "ADD LEFT ERROR: POSTCONDITION FAILED\n");
  return TREE_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int tree_add_right(tree *my_tree, tree *adding) {
  PRECOND(tree_check(my_tree->head->root, NULL) != TREE_CHECK_OK, TREE_BAD,
          "ADD LEFT ERROR: PRECONDITION FAILED\n");
  int tr_counter = 0;
  VERIFY(tree_check(my_tree, &tr_counter) == TREE_CHECK_BAD, TREE_INJURED,
         "# ADD RIGHT ERROR: [%08x] element, tree is broken\n");
  tr_counter = 0;
  VERIFY(tree_check(adding, &tr_counter) == TREE_CHECK_BAD, TREE_ADD_INJURED,
         "# ADD RIGHT ERROR: [%08] adding element, tree is broken\n");

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
  adding->head->size += 1;
  POSTCOND(tree_check(my_tree->head->root, NULL) != TREE_CHECK_OK, TREE_BAD,
           "ADD LEFT ERROR: POSTCONDITION FAILED\n");
  return TREE_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

/*

int tree_get_token(FILE* strin, tree* my_tree, int* type)
{
        PRECOND(tree_check(my_tree -> head -> root, NULL) != TREE_CHECK_OK,
TREE_BAD, "GET TOKEN ERROR: PRECONDITION FAILED\n"); assert(strin   != NULL);
        assert(my_tree != NULL);

        if (is_there_num(strin) > 0)
        {
                double value = 0;
                fscanf(strin, " %lg", &value);
                my_tree -> type = NUM;
                my_tree -> value = value;
                *type = NUM;
                POSTCOND(tree_check(my_tree -> head -> root, NULL) !=
TREE_CHECK_OK, TREE_BAD, "GET TOKEN ERROR: POSTCONDITION FAILED\n"); return
TREE_OK;
        }
        else
        {
                int c = 0;
                fscanf(strin, " %c", &c);
                switch (c)
                {
                case ADD:
                case SUB:
                case MUL:
                case DIV:
                        my_tree -> type = c;
                        my_tree -> value = (double)POISON;
                        *type = c;
                        POSTCOND(tree_check(my_tree -> head -> root, NULL) !=
TREE_CHECK_OK, TREE_BAD, "GET TOKEN ERROR: POSTCONDITION FAILED\n"); return
TREE_OK; case OP_BRAC: case CL_BRAC: *type = c; ungetc(c, strin);
                        POSTCOND(tree_check(my_tree -> head -> root, NULL) !=
TREE_CHECK_OK, TREE_BAD, "GET TOKEN ERROR: POSTCONDITION FAILED\n"); return
TREE_OK; default: fprintf(strerr, "TREE GET TOKE ERROR: wrong token [%c]\n" _
c); return TREE_BAD;
                }
        }
}

*/

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/*

#define BRAKETS_(which)
\
        add_tree = NULL;
\
        ret = tree_ctr(&add_tree, my_tree -> head);
\
        VERIFY(ret != TREE_OK, TREE_CTR_FAILED,			"# TREE WRITE IN
ORD ERROR: Failed to construct tree element\n");		\
        assert(add_tree != NULL);
\
        tree_add_##which(my_tree, add_tree);
\
        ret = tree_read_in_order(strin, my_tree -> which);
\ if (ret != TREE_OK) return ret;


int tree_read_in_order(FILE* strin, tree* my_tree)
{
        PRECOND(tree_check(my_tree -> head -> root, NULL) != TREE_CHECK_OK,
TREE_BAD, "READ ERROR: PRECONDITION FAILED\n"); VERIFY(strin   == NULL,
TREE_ARG_STR_NULL,		"# TREE READ ERROR: Argumented stream pointer is
NULL\n"); VERIFY(my_tree == NULL, TREE_ARG_TREE_NULL,		"# TREE READ
ERROR: Argumented tree pointer is NULL\n"); int c = 0;

        fscanf(strin, " %c", &c);
        VERIFY(c != '(', TREE_INVALID_INPUT,			"# TREE READ IN
ORD ERROR: Invalid input!\n");


        int got_type = 0;
        int ret = tree_get_token(strin, my_tree, &got_type);
        VERIFY(ret != TREE_OK, TREE_INVALID_INPUT,		"# TREE READ IN
ORD ERROR: error happened while tree_get_token()\n");

        if (got_type == NUM)
        {
                my_tree -> left  = NULL;
                my_tree -> right = NULL;
                fscanf(strin, " %c", &c);
                VERIFY(c != ')', TREE_INVALID_INPUT,		"# TREE READ IN
ORD ERROR: Invalid input! Got [%c] after double\n" _ c);
                POSTCOND(tree_check(my_tree -> head -> root, NULL) !=
TREE_CHECK_OK, TREE_BAD, "READ ERROR: POSTCONDITION FAILED\n"); return TREE_OK;
        }
        VERIFY(got_type != OP_BRAC, TREE_INVALID_INPUT, "# TREE READ IN ORD
ERROR: Invalid input! Got [%c] type after '('\n");

        tree* add_tree = NULL;
        BRAKETS_(left);

        ret = tree_get_token(strin, my_tree, &got_type);
        VERIFY(!( (got_type == ADD) || (got_type == SUB) || (got_type == MUL) ||
(got_type == DIV) ), TREE_INVALID_INPUT, "# TREE WRITE IN ORD ERROR: Invalid
input! Got [%c] type after ')'\n");

        BRAKETS_(right);

        fscanf(strin, " %c", &c);
        VERIFY(c != ')', TREE_INVALID_INPUT,			"# TREE WRITE IN
ORD ERROR: Invalid input!\n");


        POSTCOND(tree_check(my_tree -> head -> root, NULL) != TREE_CHECK_OK,
TREE_BAD, "READ ERROR: POSTCONDITION FAILED\n"); return TREE_OK;
}

#undef BRACKETS_

*/

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

  int type = my_tree->type;

  if (type == TR_V || type == TR_F || type == TR_STR || type == TR_N ||
      type == TR_ASSN || type == TR_SIGN || type == TR_CMP)
    free(my_tree->value);

  my_tree->head->size -= 1;
  my_tree->left = NULL;
  my_tree->right = NULL;
  my_tree->papa = NULL;
  my_tree->value = NULL;
  my_tree->type = POISON;
  free(my_tree);

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
  free(my_head);
  if (cond == TREE_DESTR_HEAD) {
    *ret_tree = tree_head;
    return TREE_OK;
  } else {
    int ret = tree_destr(tree_head);
    return ret;
  }
}
