#include "compiler.h"

/**

                        @file						main.cpp

                        @author
Sergey Ivanychev, DCAM MIPT, 376 group
                        @mainpage

                        @par						This is
a compiler of Colibri language, which's grammar can be seen below. Code must be
inputted in file "input.txt". Compiler builds the assembler code which's
compatible to CPU V4 virtual processor assembler. To run the program, just use
the .exe file of that processor

                        @version					V 1.1

                        @par Changelog V 1.1
                                                                                -- Libraries updated. Lot's of fixes have been made

**/

/**


                                @par
                                                        Grammar V 1.1

                                                        - Removed Id, because
that was useless
                                                        - Added Print and
Print_val types into Op
                                                        - Now programmer is
allowed only to write comparison in While, If and Do

                                                        Pgm		::= B
                                                        B		::= '{'
Op* '}' Op		::= IfOp | AssnOp| WhileOp| DoOp| Print | Print_val';'
                                                        IfOp	::= "if" (Cmp)
Op|B AssnOp	::= V [+-/*]?' =' E WhileOp	::= "while" (Cmp) Op|B
                                                        DoOp	::= "do" B (Cmp)
                                                        Print ::= "print(" Str
")" Print_val ::= "print_val(" E ")" V		::= [A-Za-z_]+
                                                        F		::=
[A-Za-z_]+ '('E {,E}* ')' E		::= T{[+-]T}* T		::= P{[/*]P}* P
::= [+-]* N | V | F | '('E')' N		::= [0-9]+ {'.'[0-9]+}? Cmp
::= E {"=="|"<="|">="|"!="E}? Str		::= '"' "[- \n\t,.!?A-Za-z]" '"'

                                @par
                                                        Tree types

                                                        TR_PGM
                                                        TR_B
                                                        TR_OP
                                                        TR_ASSN
                                                        TR_WHILE
                                                        TR_DO
                                                        TR_PRINT
                                                        TR_PRVAL
                                                        TR_V
//contain string TR_F					//contain string TR_E
                                                        TR_T
                                                        TR_P
                                                        TR_N
//contain double value TR_CMP
                                                        TR_STR
//contain string TR_NONE

                                                        Types of tokens

                                                        TKN_OP
// + - / * TKN_COMP				// < > <= >= == != TKN_ID
// various names, check whether it is key word or built in function TKN_NUM
// 25.936, -9.0 TKN_SEP					// { } ( ) ; , TKN_ASSGN
// += -= *= /= TKN_STR					// "aASDasdfasdfaSDFa"
                                                        TKN_END
// \0


**/

FILE *strlog = NULL;
FILE *strerr = NULL;

#define VERIFY_RET(str)                                                        \
  if (ret != CPLR_OK) {                                                        \
    fprintf(strerr, str);                                                      \
    fputc('\n', strerr);                                                       \
    if (token_stream != NULL) {                                                \
      free(*token_stream);                                                     \
      free(token_stream);                                                      \
    }                                                                          \
    if (syntax_tree != NULL)                                                   \
      head_destr(syntax_tree, TREE_DESTR_ALL);                                 \
    return -1;                                                                 \
  }

int tree_optimize(FILE *strout, tree_head *syntax_tree);
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

void save_library(FILE *strcode, FILE *lib) {
  assert(lib);
  assert(strcode);
  int c = 0;
  c = fgetc(lib);
  while (c != EOF) {
    fputc(c, strcode);
    c = fgetc(lib);
  }
  fputc('\n', strcode);
  fputc('\n', strcode);
}

int main() {
  FILE *strin = fopen("input.txt", "r");
  FILE *strout = stdout;
  strlog = fopen("compiler_log.txt", "w");
  strerr = strout;
  FILE *strcode = fopen("code.txt", "w");
  FILE *start_lib = fopen("START_LIB.txt", "r");

  save_library(strcode, start_lib);

  token **token_stream = (token **)calloc(1, sizeof(token *));

  VERIFY(token_stream == NULL, -1,
         "MAIN(): Calloc fail, token_stream hasn't been initialized");
  int stream_size = 0;
  int ret = tokenize_stream(strin, token_stream, &stream_size);
  tree_head *syntax_tree = NULL;
  VERIFY_RET("MAIN(): Tokenize fail");

  fprintf(strlog, "Size = %d\n", stream_size);

  ret = get_pgm(*token_stream, &syntax_tree);

  VERIFY_RET("MAIN(): Tree build fail");
  // tree_dump(strout, syntax_tree);

  ret = tree_optimize(strout, syntax_tree);
  VERIFY_RET("MAIN(): Optimization fail");

  ret = build_pgm(syntax_tree->root, strcode);
  VERIFY_RET("MAIN(): Build fail");

  printf(">>>[%08x]\n", *token_stream);
  printf("%c\n", *(int *)((*token_stream + 1)->value));

  free(*token_stream);
  free(token_stream);
  head_destr(syntax_tree, TREE_DESTR_ALL);

  fclose(strin);
  fclose(strout);
  fclose(strerr);
  fclose(strlog);

  // system("CPUV4.exe \"code.txt\"");

  return 0;
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

int tree_optimize(FILE *strout, tree_head *syntax_tree) {
  fprintf(strout, "\n\nOptimizing...........\n");
  bool is_optimized = false;
  int ret = tree_optimize(syntax_tree->root, &is_optimized);
  int _size = 0;
  ret = tree_check(syntax_tree->root, &_size);

  VERIFY(ret == SNTX_DIV_BY_ZERO, 0, "MAIN: There's division by zero");

  while (is_optimized == true) {
    is_optimized = false;
    ret = tree_optimize(syntax_tree->root, &is_optimized);
    VERIFY(ret == SNTX_DIV_BY_ZERO, 0, "MAIN: There's division by zero");
  }
  fprintf(strout, "\n\nDONE!\n");

  tree_dump(strout, syntax_tree);

  return CPLR_OK;
}
