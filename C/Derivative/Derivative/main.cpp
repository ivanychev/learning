/**
                        @file						main.cpp
                        @author
Sergey Ivanychev, 376 group, DCAM

                        @mainpage

                        @par						That
program builds derivative tree and LaTeX article with input expression and
derivated one. Inputted data must contain in file input.txt

                                                                                First line - derivating variable
                                                                                Other lines- derivating expressin

                                                                                Program directory will containg file article.tex and derivative_log.txt,
                                                                                where all trees will be described

                        @version					V 1.03

                        @par Changelog V 1.01
                                                                                -- Updated memory manage
                                                                                -- Added TeX support
                                                                                -- Instant PDF compiling and opening support added

                                                                                Changelog V 1.02
                                                                                -- Critical bug while building '+-' or '/ *' component of tree fixed
                                                                                                In the earlier version expression like "2 + 3 - 4 - 5" was built like (2 + (3 - (4 - 5)))
                                                                                -- Cotangent, square root and logarythm derivative fixed
                                                                                -- Get_t() and get_p() function enchanced with new operator "side"

                                                                                Changelog V 1.03
                                                                                -- Memory leaks fixed
                                                                                -- Unused variables removed

                        @todo
Program crashes if "sin(x" is inserted. Falling happens while freeing memory

**/

#include "compiler.h"

FILE *strlog = NULL;
FILE *strerr = NULL;

#define VERIFY_RET(str, ret_arg)                                               \
  if (ret != ret_arg) {                                                        \
    fprintf(strerr, str);                                                      \
    fputc('\n', strerr);                                                       \
    BREAK;                                                                     \
  }

#define CLOSE(file)                                                            \
  if (file) {                                                                  \
    fclose(file);                                                              \
    file = NULL;                                                               \
  }
#define DESTROY(my_tree)                                                       \
  if (my_tree) {                                                               \
    head_destr(my_tree, TREE_DESTR_ALL);                                       \
    my_tree = NULL;                                                            \
  }
#define BREAK goto pgm_break;
#define BREAK_POINT                                                            \
  pgm_break:;

int main() {
  FILE *strin = fopen("input.txt", "r");
  strlog = fopen("derivative_log.txt", "w");
  FILE *strout = strlog;
  strerr = strout;
  FILE *strcode = fopen("code.txt", "w");
  FILE *tex_output = fopen("article.tex", "w");
  FILE *tex_template = fopen("tex_template.txt", "r");

  assert(strin);
  assert(strlog);
  assert(strout);
  assert(strerr);
  assert(strcode);
  assert(tex_output);
  assert(tex_template);

  tree_head *syntax_tree = NULL;
  tree_head *func_nonopt = NULL;
  tree_head *der = NULL;
  tree_head *der_nonopt = NULL;

  token **token_stream = (token **)calloc(1, sizeof(token *));

  char var[MAX_VAR_NAME] = {};
  int ret = fscanf_s(strin, "%s", var, MAX_VAR_NAME);
  assert(ret);

  if (var[MAX_VAR_NAME - 1] != '\0') {
    fprintf(strout, "Variable name is bigger than expected. Maximum size is %d",
            MAX_VAR_NAME);
    BREAK;
  }

  VERIFY(token_stream == NULL, -1,
         "MAIN(): Calloc fail, token_stream hasn't been initialized");
  int stream_size = 0;
  ret = tokenize_stream(strin, token_stream, &stream_size);

  VERIFY_RET("MAIN(): Tokenize fail", CPLR_OK);
  fprintf(strlog, "Size = %d\n", stream_size);

  ret = get_pgm(*token_stream, &syntax_tree);
  tree_dump(strout, syntax_tree);
  VERIFY_RET("MAIN(): Tree build fail", CPLR_OK);

  fprintf(strout, "\n\n>>>>>>>>>>>>>>>>>>Non-optimized input "
                  "tree<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");

  ret = tree_copy(syntax_tree->root, &func_nonopt);
  VERIFY(ret != TREE_OK, 0, "MAIN(): Copying func tree failed");

  bool is_optimized = true;
  while (is_optimized) {
    is_optimized = false;
    ret = tree_optimize(syntax_tree->root, &is_optimized);
    VERIFY_RET("MAIN(): Optimize failed", SNTX_OK);
  }

  fprintf(strout, "\n\n>>>>>>>>>>>>>>>>>>>>Optimized input "
                  "tree<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");
  tree_dump(strout, syntax_tree);

  ret = build_derivative(syntax_tree->root->right, &der, var);
  VERIFY_RET("MAIN(): Derivative build fail", CPLR_OK);
  int __size = 0;
  VERIFY(tree_check(der->root, &__size) != TREE_CHECK_OK, -1,
         "Built derivative tree is injured!");
  fprintf(strout, "\n\n>>>>>>>>>>>>>>>>>>>>>>>>Fresh derivative "
                  "tree<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");
  tree_dump(strout, der);

  ret = tree_copy(der->root, &der_nonopt);
  VERIFY(ret != TREE_OK, 0, "MAIN(): Copying der tree failed");

  is_optimized = true;
  while (is_optimized) {
    is_optimized = false;
    ret = tree_optimize(der->root, &is_optimized);
    VERIFY_RET("MAIN(): Optimize failed", SNTX_OK);
  }

  ret = tex_build(tex_output, tex_template, func_nonopt->root->right,
                  syntax_tree->root->right, der_nonopt->root->right,
                  der->root->right, var);

  VERIFY_RET("MAIN(): Tex build failed", CPLR_OK);

  fprintf(strout, "\n\n>>>>>>>>>>>>>>>>>>>>>>>>>Optimized derivative "
                  "tree<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");
  tree_dump(strout, der);
  // tree_dump(stdout, der);

  // free(*token_stream);
  // free(token_stream);
  tree *temp_tree = NULL;

  printf("DONE\n");

  BREAK_POINT;

  if (token_stream != NULL) {
    if (*token_stream != NULL)
      free(*token_stream);
    *token_stream = NULL;
    free(token_stream);
    token_stream = NULL;
  }

  DESTROY(syntax_tree);
  DESTROY(der);
  DESTROY(func_nonopt);
  DESTROY(der_nonopt);

  CLOSE(tex_output);
  CLOSE(tex_template);
  CLOSE(strin);
  CLOSE(strout);
  CLOSE(strerr);
  CLOSE(strlog);
  CLOSE(strcode);

  system("\"C:\\Program Files (x86)\\MiKTeX 2.9\\miktex\\bin\\pdflatex.exe\" "
         "article.tex");
  system("start article.pdf");

  return 0;
}