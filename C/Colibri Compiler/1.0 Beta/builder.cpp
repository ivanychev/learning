#include "compiler.h"

extern FILE *strlog;
extern FILE *strerr;

int build_pgm(tree *my_tree, FILE *strout);

int build_b(tree *my_tree, FILE *strout);

int build_assgn(tree *my_tree, FILE *strout);

int build_if(tree *my_tree, FILE *strout);

int build_while(tree *my_tree, FILE *strout);

int build_do(tree *my_tree, FILE *strout);

int build_cmp(tree *my_tree, FILE *strout, char *label);

int build_print(tree *my_tree, FILE *strout);

int build_prval(tree *my_tree, FILE *strout);

int build_e(tree *my_tree, FILE *strout);

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#define CHECK_ARGS(func, tr_type)                                              \
  int __check_size = 0;                                                        \
  VERIFY(my_tree == NULL, COMP_NULL_ARG,                                       \
         #func ": Argumented tree pointer is NULL");                           \
  VERIFY(strout == NULL, COMP_NULL_ARG,                                        \
         #func ": Argumented file stream is NULL");                            \
  VERIFY(tree_check(my_tree, &__check_size) != TREE_CHECK_OK, COMP_BAD_TREE,   \
         "TREE COMPILE: Inputted tree is injured");                            \
  VERIFY(my_tree->type != TR_##tr_type, COMP_BAD_TYPE,                         \
         "BUILD PGM: Bad type of inputted tree");

#define CALL(func)                                                             \
  ret = func;                                                                  \
  if (ret != COMP_OK)                                                          \
    return ret;                                                                \
  ret = 0;

#define CMD(num)                                                               \
  fprintf(strout, "%s", cmd[num]);                                             \
  fputc('\n', strout);
#define CMD_STR(num, str)                                                      \
  fprintf(strout, "%s", cmd[num]);                                             \
  fprintf(strout, str);                                                        \
  fputc('\n', strout);
#define CMD_STR1(num, str, arg)                                                \
  fprintf(strout, "%s", cmd[num]);                                             \
  fprintf(strout, str, arg);                                                   \
  fputc('\n', strout);

#define ADD(line) fprintf(strout, line);
#define ENTER fputc('\n', strout);
#define ADD1(line, arg1) fprintf(strout, line, arg1);
#define ADD2(line, arg1, arg2) fprintf(strout, line, arg1, arg2);
#define ADD3(line, arg1, arg2, arg3) fprintf(strout, line, arg1, arg2, arg3);

#define WORD(my_tree) (char *)(my_tree->value)
#define DOUBLE(my_tree) *(double *)(my_tree->value)
#define INT(my_tree) *((int *)(my_tree->value))

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

var vars[MAXVARS] = {}; // Global variables array. Used because the common
                        // namespace of the whole program

int label_counter = 0;

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int search_word(var *vars, char *word) {
  assert(vars);
  assert(word);

  for (int i = 0; i < MAXVARS; ++i)
    if (strcmp(word, (vars[i]).name) == 0)
      return i;
  return -1;
}

int search_last_free(var *vars) {
  assert(vars);
  for (int i = 0; i < MAXVARS; ++i)
    if ((vars[i]).name[0] == 0)
      return i;
  return -1;
}

int save_var(char *word, var *vars) {
  assert(strlen(word) < MAX_VAR_NAME);
  strcpy(vars->name, word);
  return COMP_OK;
}

int create_label(char *op, char *to_save) {
  assert(op != NULL);

  sprintf(to_save, "__%s_%d", op, label_counter++);

  return COMP_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int tree_compile(tree_head *my_tree, FILE *strout) {
  int __check_size = 0;
  VERIFY(my_tree == NULL, COMP_NULL_ARG,
         "TREE COMPILE: Argumented tree pointer is NULL");
  VERIFY(strout == NULL, COMP_NULL_ARG,
         "TREE COMPILE: Argumented file stream is NULL");
  VERIFY(tree_check(my_tree->root, &__check_size) != TREE_CHECK_OK,
         COMP_BAD_TREE, "TREE COMPILETREE COMPILE: Inputted tree is injured");

  int ret = build_pgm(my_tree->root, strout);

  if (ret != COMP_OK)
    return COMP_BAD;

  return COMP_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int build_pgm(tree *my_tree, FILE *strout) {
  CHECK_ARGS(BUILD PGM, PGM);
  int ret = 0;
  ret = build_b(my_tree->right, strout);
  if (ret != COMP_OK)
    return CPLR_BAD;
  CMD(END);

  return CPLR_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int proceed_op(tree *ptr, FILE *strout) {
  assert(ptr != NULL);
  assert(strout != NULL);
  int ret = 0;
  int type = ptr->type;

  switch (type) {
  case TR_ASSN:
    CALL(build_assgn(ptr, strout));
    break;
  case TR_IF:
    CALL(build_if(ptr, strout));
    break;
  case TR_WHILE:
    CALL(build_while(ptr, strout));
    break;
  case TR_PRINT:
    CALL(build_print(ptr, strout));
    break;
  case TR_PRVAL:
    CALL(build_prval(ptr, strout));
    break;
  case TR_DO:
    CALL(build_do(ptr, strout));
    break;
  case TR_NONE:
    break;
  default:
    VERIFY(true, COMP_BAD_TYPE,
           "BUILD_B: Type of operator hasn't been reckognized");
    break;
  }
  return COMP_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int build_b(tree *my_tree, FILE *strout) {
  CHECK_ARGS(BUILD B, B);
  VERIFY(my_tree->right == NULL, COMP_UNEXP_END,
         "BUILD B: Unexprected end of tree");
  tree *ptr = my_tree->right;

  while ((ptr->type) != TR_NONE) {
    VERIFY(ptr->left == NULL, COMP_UNEXP_END, "BUILD B: Can't find operator");

    int ret = 0;
    CALL(proceed_op(ptr->left, strout));

    VERIFY(ptr->right == NULL, COMP_UNEXP_END,
           "BUILD B: Unexprected end of tree");
    ptr = ptr->right;
  }

  return COMP_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int build_assgn(tree *my_tree, FILE *strout) {
  CHECK_ARGS(BUILD ASSIGN, ASSN);

  int ret = 0;

  int ptr = search_word(vars, WORD(my_tree->left));
  if (ptr == -1)

  {
    VERIFY(strlen(WORD(my_tree->left)) >= MAX_VAR_NAME, COMP_TOO_LONG_VAR,
           "BUILD ASSGN: defined variablie has too long name");

    ptr = search_last_free(vars);

    if (ptr == -1)
      return COMP_OUT_OF_VARS;

    CALL(save_var(WORD(my_tree->left), &(vars[ptr])));

    CMD_STR1(DEF, "%s", WORD(my_tree->left));
  }

  CALL(build_e(my_tree->right, strout));

  switch (INT(my_tree)) {
  case ASSGN:
    CMD_STR1(POP, "var %s", WORD(my_tree->left));
    break;
  case ASSGN_ADD:
    CMD_STR1(PUSH, "var %s", WORD(my_tree->left));
    CMD(ADD);
    CMD_STR1(POP, "var %s", WORD(my_tree->left));
    break;
  case ASSGN_DIV:
    CMD_STR1(PUSH, "var %s", WORD(my_tree->left));
    CMD(DIV);
    CMD_STR1(POP, "var %s", WORD(my_tree->left));
    break;
  case ASSGN_MUL:
    CMD_STR1(PUSH, "var %s", WORD(my_tree->left));
    CMD(MUL);
    CMD_STR1(POP, "var %s", WORD(my_tree->left));
    break;
  case ASSGN_SUB:
    CMD_STR1(PUSH, "var %s", WORD(my_tree->left));
    CMD(SUB);
    CMD_STR1(POP, "var %s", WORD(my_tree->left));
    break;
  default:
    VERIFY(true, COMP_BAD_VALUE, "BUILD ASSGN: Wrong type of assign operator");
  }

  ENTER;

  return COMP_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

bool verify_e(tree *my_tree) {
  assert(my_tree != NULL);
  if (my_tree->type != TR_N && my_tree->type != TR_SIGN &&
      my_tree->type != TR_F && my_tree->type != TR_V &&
      my_tree->type != TR_NONE)
    return false;
  return true;
}

int print_sign(FILE *strout, tree *my_tree) {
  assert(strout);
  assert(my_tree);
  switch (INT(my_tree)) {
  case '+':
    CMD(ADD);
    break;
  case '-':
    CMD(SUB);
    break;
  case '*':
    CMD(MUL);
    break;
  case '/':
    CMD(DIV);
    break;
  default:
    VERIFY(true, COMP_BAD_VALUE, "BUILD E: Invalid sign value");
  }
  return COMP_OK;
}

int build_e(tree *my_tree, FILE *strout) {
  int __check_size = 0;
  VERIFY(my_tree == NULL, COMP_NULL_ARG,
         "BUILD E: Argumented tree pointer is NULL");
  VERIFY(strout == NULL, COMP_NULL_ARG,
         "BUILD E: Argumented file stream is NULL");
  VERIFY(tree_check(my_tree, &__check_size) != TREE_CHECK_OK, COMP_BAD_TREE,
         "BUILD E: Inputted tree is injured");
  VERIFY(!(verify_e(my_tree)), COMP_BAD_TYPE,
         "BUILD E: Type of E node is invalid");

  int ret = 0;
  if (my_tree->left != NULL)
    CALL(build_e(my_tree->left, strout));
  if (my_tree->right != NULL)
    CALL(build_e(my_tree->right, strout));

  switch (my_tree->type) {
  case TR_N:
    assert(my_tree->value != NULL);
    CMD_STR1(PUSH, "%lg", DOUBLE(my_tree));
    break;

  case TR_V:
    assert(my_tree->value != NULL);
    VERIFY(search_word(vars, WORD(my_tree)) == -1, COMP_UNDEF_VAR,
           "BUILD E: Undefined var found [%s]" _ WORD(my_tree));
    CMD_STR1(PUSH, "var %s", WORD(my_tree));
    break;

  case TR_F:
    assert(my_tree->value != NULL);
    CMD_STR1(CALL, ":__%s", WORD(my_tree));
    break;

  case TR_SIGN:
    CALL(print_sign(strout, my_tree));
    break;
  }
  return COMP_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int build_cmp(tree *my_tree, FILE *strout, char **out_label) {
  int __check_size = 0;
  VERIFY(out_label == NULL, COMP_NULL_ARG,
         "BUILD CMP: Argumented char** pointer is NULL");
  VERIFY(my_tree == NULL, COMP_NULL_ARG,
         "BUILD CMP: Argumented tree pointer is NULL");
  VERIFY(strout == NULL, COMP_NULL_ARG,
         "BUILD CMP: Argumented file stream is NULL");
  VERIFY(tree_check(my_tree, &__check_size) != TREE_CHECK_OK, COMP_BAD_TREE,
         "BUILD CMP: Inputted tree is injured");
  VERIFY(my_tree->left == NULL || my_tree->right == NULL, COMP_NULL_CHILD,
         "BUILD CMP: NULL child");

  int ret = 0;
  CALL(build_e(my_tree->left, strout));
  CALL(build_e(my_tree->right, strout));
  // CMD(SUB);

  char *label = (char *)calloc(SYS_LABEL_LEN, sizeof(char));

  switch (INT(my_tree)) {
  case CMP_A:
    CALL(create_label("cmp_a", label));
    CMD_STR1(JBE, ":%s", label);
    break;
  case CMP_B:
    CALL(create_label("cmp_b", label));
    CMD_STR1(JAE, ":%s", label);
    break;
  case CMP_AE:
    CALL(create_label("cmp_ae", label));
    CMD_STR1(JB, ":%s", label);
    break;
  case CMP_BE:
    CALL(create_label("cmp_be", label));
    CMD_STR1(JA, ":%s", label);
    break;
  case CMP_E:
    CALL(create_label("cmp_e", label));
    CMD_STR1(JNE, ":%s", label);
    break;
  case CMP_NE:
    CALL(create_label("cmp_ne", label));
    CMD_STR1(JE, ":%s", label);
    break;
  default:
    VERIFY(true, COMP_BAD_VALUE, "BUILD CMD: Wrong sign [%d]" _ INT(my_tree));
    break;
  }
  ENTER;

  *out_label = label;

  return COMP_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int build_if(tree *my_tree, FILE *strout) {
  CHECK_ARGS(BUILD IF, IF);
  VERIFY(my_tree->left == NULL || my_tree->right == NULL, COMP_NULL_CHILD,
         "BUILD IF: NULL child");
  int ret = 0;
  char *label_free_me = NULL;

  CALL(build_cmp(my_tree->left, strout, &label_free_me));

  if (my_tree->right->type == TR_B) {
    CALL(build_b(my_tree->right, strout))
  } else if (my_tree->right->type == TR_OP) {
    assert(my_tree->right->left);
    CALL(proceed_op(my_tree->right->left, strout));
  } else {
    VERIFY(true, COMP_BAD_VALUE, "BUILD IF: Invalid left branch");
  }

  printf("%s\n", label_free_me);
  ADD1(":%s\n", label_free_me);

  free(label_free_me);

  return COMP_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int build_while(tree *my_tree, FILE *strout) {
  CHECK_ARGS(BUILD WHILE, WHILE);
  VERIFY(my_tree->left == NULL || my_tree->right == NULL, COMP_NULL_CHILD,
         "BUILD WHILE: NULL child");
  int ret = 0;
  char *label_free_me = NULL;
  char *label_begin_free_me = (char *)calloc(SYS_LABEL_LEN, sizeof(char));

  CALL(create_label("while_begin", label_begin_free_me));
  ADD1(":%s\n", label_begin_free_me);

  CALL(build_cmp(my_tree->left, strout, &label_free_me));

  if (my_tree->right->type == TR_B) {
    CALL(build_b(my_tree->right, strout))
  } else if (my_tree->right->type == TR_OP) {
    assert(my_tree->right->left);
    CALL(proceed_op(my_tree->right->left, strout));
  } else {
    VERIFY(true, COMP_BAD_VALUE, "BUILD WHILE: Invalid left branch");
  }

  CMD_STR1(JMP, ":%s", label_begin_free_me);
  ADD1(":%s\n", label_free_me);

  free(label_begin_free_me);
  free(label_free_me);

  return COMP_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int build_do(tree *my_tree, FILE *strout) {
  CHECK_ARGS(BUILD DO, DO);
  VERIFY(my_tree->left == NULL || my_tree->right == NULL, COMP_NULL_CHILD,
         "BUILD WHILE: NULL child");
  char *label_free_me = NULL;
  char *label_begin_free_me = (char *)calloc(SYS_LABEL_LEN, sizeof(char));

  int ret = 0;
  CALL(create_label("do_begin", label_begin_free_me));
  ADD1(":%s\n", &label_begin_free_me);

  VERIFY(my_tree->right->type != TR_B, COMP_BAD_VALUE,
         "BUILD DO: Invalid left branch");

  CALL(build_b(my_tree->right, strout));

  CALL(build_cmp(my_tree->left, strout, &label_free_me));
  CMD_STR1(JMP, ":%s", label_begin_free_me);
  ADD1(":%s\n", label_free_me);

  free(label_begin_free_me);
  free(label_free_me);

  return COMP_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int build_prval(tree *my_tree, FILE *strout) {
  CHECK_ARGS(BUILD PRVAL, PRVAL);

  VERIFY(my_tree->right == NULL, COMP_NULL_CHILD,
         "BUILD PRVAL: Variable child is NULL");
  // VERIFY(my_tree -> right -> value == NULL, COMP_NULL_CHILD, "BUILD PRVAL: No
  // value found"); VERIFY(search_word(vars, WORD(my_tree -> right)) == -1,
  // COMP_UNDEF_VAR, "BUILD PRVAL: Undefined variable [%s]" _ WORD(my_tree ->
  // right));

  int ret = 0;
  CALL(build_e(my_tree->right, strout));

  // CMD_STR1(PUSH, "var %s", WORD(my_tree -> right));
  ADD("out st\n");

  return COMP_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int build_print(tree *my_tree, FILE *strout) {
  CHECK_ARGS(BUILD PRINT, PRINT);
  VERIFY(my_tree->right == NULL, COMP_NULL_CHILD,
         "BUILD PRINT: Variable child is NULL");
  VERIFY(my_tree->right->value == NULL, COMP_NULL_CHILD,
         "BUILD PRVAL: No value found");
  char *ptr = WORD(my_tree->right);

  while (*ptr != '\0') {
    CMD_STR1(OUT, "ch %d", *ptr);
    ptr++;
  }

  return COMP_OK;
}
