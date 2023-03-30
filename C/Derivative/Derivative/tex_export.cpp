/**
                @par		tex article export contained here

                @par		V 1.01

**/

#include "compiler.h"

extern FILE *strlog;
extern FILE *strerr;

int tex_build(tree *my_tree, FILE *tex_output, FILE *tex_template, char *var);

int tex_add_sub(tree *my_tree, FILE *tex_output);

int tex_mul(tree *my_tree, FILE *tex_output);

int tex_div(tree *my_tree, FILE *tex_output);

int tex_f(tree *my_tree, FILE *tex_output);

int tex_pow(tree *my_tree, FILE *tex_output);

int tex_log(tree *my_tree, FILE *tex_output);

int tex_print(tree *my_tree, FILE *tex_output);

int tex_sign(tree *my_tree, FILE *tex_output);

int tex_at_deal(FILE *tex_output, FILE *tex_template, tree *func,
                tree *opt_func, tree *der, tree *opt_der, char *var);

#define CALL(func)                                                             \
  ret = func;                                                                  \
  if (ret != CPLR_OK)                                                          \
    return ret;
#define TEX_PRINT(tree)                                                        \
  if (strcmp(word, #tree) == 0) {                                              \
    CALL(tex_print(tree, tex_output));                                         \
    return CPLR_OK;                                                            \
  }
#define TYPE(my_tree) (my_tree->type)
#define DOUBLE(my_tree) *(double *)(my_tree->value)
#define WORD(my_tree) (char *)(my_tree->value)
#define INT(my_tree) *(int *)(my_tree->value)

#define PUTC(c) fputc(c, tex_output);
#define PUT(str) fprintf(tex_output, str);
#define PUT1(str, arg1) fprintf(tex_output, str, arg1);
#define PUT2(str, arg1, arg2) fprintf(tex_output, str, arg1, arg2);

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int tex_build(FILE *tex_output, FILE *tex_template, tree *func, tree *opt_func,
              tree *der, tree *opt_der, char *var) {
  VERIFY(func == NULL, CPLR_BAD, "TEX EXPORT: Argumented func pointer is NULL");
  VERIFY(opt_func == NULL, CPLR_BAD,
         "TEX EXPORT: Argumented optimized func pointer is NULL");
  VERIFY(der == NULL, CPLR_BAD,
         "TEX EXPORT: Argumented derivative pointer is NULL");
  VERIFY(opt_der == NULL, CPLR_BAD,
         "TEX EXPORT: Argumented optimized derivative pointer is NULL");

  VERIFY(tex_output == NULL, CPLR_BAD,
         "TEX EXPORT: Argumented output stream is NULL");
  VERIFY(tex_template == NULL, CPLR_BAD,
         "TEX EXPORT: Argumented tex template pointer is NULL");
  VERIFY(var == NULL, CPLR_BAD, "TEX_EXPORT: Argumented variable is NULL");

  int ret = 0;
  int c = 0;
  while ((c = fgetc(tex_template)) != EOF) {
    if (c != '@') {
      fputc(c, tex_output);
      continue;
    }
    CALL(tex_at_deal(tex_output, tex_template, func, opt_func, der, opt_der,
                     var));
  }

  return CPLR_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int tex_at_deal(FILE *tex_output, FILE *tex_template, tree *func,
                tree *opt_func, tree *der, tree *opt_der, char *var) {
  char word[MAXLINE] = {};
  int ret = fscanf_s(tex_template, "%[A-Za-z_]", word, MAXLINE);

  if (strcmp(word, "arg") == 0) {
    fprintf(tex_output, "%s", var);
    return CPLR_OK;
  }

  TEX_PRINT(func);
  TEX_PRINT(opt_func);
  TEX_PRINT(der);
  TEX_PRINT(opt_der);

  return CPLR_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int tex_print(tree *my_tree, FILE *tex_output) {
  VERIFY(my_tree == NULL, CPLR_BAD,
         "TEX PRINT: Argumented tree pointer is NULL");
  assert(tex_output);
  int ret = 0;

  switch (TYPE(my_tree)) {
  case TR_SIGN:
    CALL(tex_sign(my_tree, tex_output));
    break;
  case TR_F:
    CALL(tex_f(my_tree, tex_output));
    break;
  case TR_V:
    fprintf(tex_output, "%s", WORD(my_tree));
    break;
  case TR_N:
    fprintf(tex_output, "%lg", DOUBLE(my_tree));
    break;
  default:
    VERIFY(true, CPLR_BAD, "TEX PRINT: Unknown type of tree");
    break;
  }

  return CPLR_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int tex_sign(tree *my_tree, FILE *tex_output) {
  assert(my_tree);
  assert(tex_output);
  VERIFY1(INT(my_tree) != '+' && INT(my_tree) != '-' && INT(my_tree) != '*' &&
              INT(my_tree) != '/',
          CPLR_BAD, "TEX SIGN: Invalid sign, got [%c]", INT(my_tree));

  int ret = 0;

  switch (INT(my_tree)) {
  case '+':
  case '-':
    CALL(tex_add_sub(my_tree, tex_output));
    break;
  case '*':
    CALL(tex_mul(my_tree, tex_output));
    break;
  case '/':
    CALL(tex_div(my_tree, tex_output));
    break;
  default:
    assert(0);
  }

  return CPLR_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

bool is_papa_add_sub(tree *my_tree) {
  assert(my_tree);
  assert(my_tree->papa);

  if (TYPE(my_tree->papa) == TR_SIGN &&
      (INT(my_tree->papa) == '+' || INT(my_tree->papa) == '-'))
    return true;
  return false;
}

int tex_add_sub(tree *my_tree, FILE *tex_output) {
  assert(my_tree);
  assert(tex_output);
  assert(TYPE(my_tree) == TR_SIGN);
  assert(INT(my_tree) == '+' || INT(my_tree) == '-');
  int ret = 0;
  VERIFY(my_tree->left == NULL || my_tree->right == NULL, CPLR_BAD,
         "TEX ADD SUB: Invalid sum node");

  bool no_brackets = false;
  if (my_tree->papa != NULL && is_papa_add_sub(my_tree) == true)
    no_brackets = true;
  if (my_tree->papa != NULL && TYPE(my_tree->papa) == TR_SIGN &&
      INT(my_tree->papa) == '/')
    no_brackets = true;
  if (my_tree->papa != NULL &&
      (my_tree->papa->type == TR_PGM || my_tree->papa->type == TR_F))
    no_brackets = true;

  if (!(no_brackets))
    PUTC('(');

  CALL(tex_print(my_tree->left, tex_output));
  PUT1(" %c ", INT(my_tree));
  CALL(tex_print(my_tree->right, tex_output));

  if (!(no_brackets))
    PUTC(')');

  return CPLR_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int tex_mul(tree *my_tree, FILE *tex_output) {
  assert(my_tree);
  assert(tex_output);
  assert(TYPE(my_tree) == TR_SIGN);
  assert(INT(my_tree) == '*');
  int ret = 0;
  VERIFY(my_tree->left == NULL || my_tree->right == NULL, CPLR_BAD,
         "TEX ADD SUB: Invalid mul node");

  CALL(tex_print(my_tree->left, tex_output));

  bool put_dot = false;
  if (TYPE(my_tree->right) == TR_N) {
    PUT(" \\cdot ");
    put_dot = true;
  }

  if (put_dot == false && my_tree->left->right && my_tree->right->left &&
      TYPE(my_tree->right->left) == TR_N &&
      TYPE(my_tree->left->right) == TR_N) {
    PUT(" \\cdot ");
    put_dot = true;
  }

  CALL(tex_print(my_tree->right, tex_output));

  return CPLR_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int tex_div(tree *my_tree, FILE *tex_output) {
  assert(my_tree);
  assert(tex_output);
  assert(TYPE(my_tree) == TR_SIGN);
  assert(INT(my_tree) == '/');
  int ret = 0;
  VERIFY(my_tree->left == NULL || my_tree->right == NULL, CPLR_BAD,
         "TEX ADD SUB: Invalid div node");

  PUT("\\frac{");
  CALL(tex_print(my_tree->left, tex_output));
  PUT("}{");
  CALL(tex_print(my_tree->right, tex_output));
  PUTC('}');

  return CPLR_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#define FUNC_IS(word) (strcmp(WORD(my_tree), word) == 0)

int tex_f(tree *my_tree, FILE *tex_output) {

  assert(my_tree);
  assert(tex_output);
  assert(TYPE(my_tree) == TR_F);
  int ret = 0;

  if (FUNC_IS("pow") || FUNC_IS("exp")) {
    CALL(tex_pow(my_tree, tex_output));
    return CPLR_OK;
  }

  if (FUNC_IS("log")) {
    CALL(tex_log(my_tree, tex_output));
    return CPLR_OK;
  }

  if (FUNC_IS("ln")) {
    PUT("\\ln{}");

    bool is_sign = false;
    if (TYPE(my_tree->right) == TR_SIGN)
      is_sign = true;

    if (is_sign)
      PUTC('(');
    CALL(tex_print(my_tree->right, tex_output));
    if (is_sign)
      PUTC(')');
    return CPLR_OK;
  }

  if (FUNC_IS("sqrt")) {
    PUT("\\sqrt{");
    CALL(tex_print(my_tree->right, tex_output));
    PUT("} ");
    return CPLR_OK;
  }

  PUT1("\\%s(", WORD(my_tree));
  CALL(tex_print(my_tree->right, tex_output));
  PUTC(')');

  return CPLR_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#define IS_ONE(ch_tree)                                                        \
  (TYPE(ch_tree) == TR_N && fabs(DOUBLE(ch_tree) - 1.0) < DBL_EPSILON)
int tex_pow(tree *my_tree, FILE *tex_output) {
  assert(TYPE(my_tree) == TR_F);
  assert(my_tree->right);
  // assert(my_tree -> right -> left);
  // assert(my_tree -> right -> right);
  int ret = 0;

  bool is_e = false;

  if (strcmp(WORD(my_tree), "exp") == 0)
    is_e = true;

  if (!(is_e)) {
    if (TYPE(my_tree->right->left) == TR_SIGN)
      PUTC('(');
    CALL(tex_print(my_tree->right->left, tex_output));
    if (TYPE(my_tree->right->left) == TR_SIGN)
      PUTC(')');
  } else
    PUTC('e');
  PUTC('^');

  PUTC('{');
  if (!(is_e)) {
    if (!(IS_ONE(my_tree->right->right))) {
      CALL(tex_print(my_tree->right->right, tex_output));
    }
  } else {
    if (!(IS_ONE(my_tree->right))) {
      CALL(tex_print(my_tree->right, tex_output));
    }
  }
  PUTC('}');

  return CPLR_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int tex_log(tree *my_tree, FILE *tex_output) {
  assert(TYPE(my_tree) == TR_F);
  assert(my_tree->right);
  assert(my_tree->right->left);
  assert(my_tree->right->right);
  int ret = 0;

  PUT("\\log_{");
  CALL(tex_print(my_tree->right->left, tex_output));
  PUTC('}');

  bool is_sign = false;
  if (TYPE(my_tree->right->right) == TR_SIGN)
    is_sign = true;

  if (is_sign)
    PUTC('(');
  CALL(tex_print(my_tree->right->right, tex_output));
  if (is_sign)
    PUTC(')');

  return CPLR_OK;
}