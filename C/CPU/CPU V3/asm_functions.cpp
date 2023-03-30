
#include "command_codes.h"
#include "cpu.h"

/**
                asm_is_mrk
function figures out whether the word is "func" or mark, and calls asm_mark,
depending on result

                @param[out]		strin input file stream
                @param[out]		strerr error file stream
                @param[out]		word analysing word
                @param[out]		cur_code
current memory pointer
                @param[out]		pts
the array of memory pointers
                @param[out]		(*error_catcher)	error catcher
function

                @return
ASM_NOT_MARK ASM_ERROR_CHECKER_BAD or ASM_ERROR_CHECKER_OK, depending of
(*error_catcher)
**/
int asm_is_mrk(FILE *strin, FILE *strerr, char *word, int *cur_code,
               pointer *pts, int (*error_catcher)(FILE *strerr, int cond));
/**
                asm_error_catcher
function analyses error code, prints the message, if there's mistake
                @param[out]		strerr error file stream
                @param			cond error code

                @return
ASM_ERROR_CHECKER_BAD or ASM_ERROR_CHECKER_OK, depending of is there mistake or
not

**/
int asm_error_catcher(FILE *strerr, int cond);
/**
                asm_cmd_jump_like					this
function deals with functions, that may jump to the mark

                @param[out]		strin input file stream
                @param[out]		codes the memory array
                @param[out]		cur_code
current memory pointer
                @param			arg
variable, that brings constant of function
                @param[out]		pts
the array of memory pointers

                @return
ASM_BAD_CUR_CODE_POINTER - the pointer of cur_code is broken ASM_STRIN_BAD
- strin pointer is NULL ASM_BAD_CODES_POINTER	 - codes[] pointer is null
                                                                                        ASM_SCAN_FAILED			 - scanning failed
                                                                                        ASM_JUMP_NOT_MARK		 - invalid argument of function
                                                                                        ASM_OK					 - ok

**/
int asm_cmd_jump_like(FILE *strin, double *codes, int *cur_code, const int arg,
                      pointer *pts);
/**

                asm_cmd_mov
function deals with mov instruction

                @param[out]		strin input file stream
                @param[out]		codes the memory array
                @param[out]		cur_code
current memory pointer

                @return
ASM_BAD_CUR_CODE_POINTER - the pointer of cur_code is broken ASM_STRIN_BAD
- strin pointer is NULL ASM_BAD_CODES_POINTER	 - codes[] pointer is null
                                                                                        ASM_OK					 - OK!
**/
int asm_cmd_mov(FILE *strin, double *codes, int *cur_code);
/**
                asm_cmd_out
function deals with out instruction

                @param[out]		strin input file stream
                @param[out]		codes the memory array
                @param[out]		cur_code
current memory pointer

                @return
ASM_BAD_CUR_CODE_POINTER - the pointer of cur_code is broken ASM_STRIN_BAD
- strin pointer is NULL ASM_BAD_CODES_POINTER	 - codes[] pointer is null
                                                                                        ASM_OK					 - OK!
                                                                                        ASM_BAD_OUT_STR_TOKEN    - the argument of out is invalid
                                                                                        ASM_OUT_BAD_CHAR_ARGUMENT- the argument after CH is incorrect
**/

int asm_cmd_out(FILE *strin, double *codes, int *cur_code);
/**
                asm_cmd_pop
function deals with pop instruction

                @param[out]		strin input file stream
                @param[out]		codes the memory array
                @param[out]		cur_code
current memory pointer

                @return
ASM_BAD_CUR_CODE_POINTER - the pointer of cur_code is broken ASM_STRIN_BAD
- strin pointer is NULL ASM_BAD_CODES_POINTER	 - codes[] pointer is null
                                                                                        ASM_BAD_POP_STR_TOKEN	 - the argument of pop is invalid
                                                                                        ASM_OK					 - OK!

**/
int asm_cmd_pop(FILE *strin, double *codes, int *cur_code);
/**
                asm_cmd_in
function deals with in instruction

                @param[out]		strin input file stream
                @param[out]		codes the memory array
                @param[out]		cur_code
current memory pointer

                @return
ASM_BAD_CUR_CODE_POINTER - the pointer of cur_code is broken ASM_STRIN_BAD
- strin pointer is NULL ASM_BAD_CODES_POINTER	 - codes[] pointer is null
                                                                                        ASM_BAD_IN_STR_TOKEN	 - the argument of in is invalid
                                                                                        ASM_OK					 - OK!
**/

int asm_cmd_in(FILE *strin, double *codes, int *cur_code);
/**
                asm_str_convert
function converts the word as a stream (defined by constants in header) into
constant

                @param[out]		word analysing word
                @param[out]		reg
variable that will contain the converted value

                @return
ASM_BAD_STR_TOKEN ASM_OK
**/
int asm_str_convert(char *word, double *reg);
/**
                asm_cmd_push
function deals with push instruction

                @param[out]		strin input file stream
                @param[out]		codes the memory array
                @param[out]		cur_code
current memory pointer

                @return
ASM_BAD_CUR_CODE_POINTER - the pointer of cur_code is broken ASM_STRIN_BAD
- strin pointer is NULL ASM_BAD_CODES_POINTER	 - codes[] pointer is null
                                                                                        ASM_BAD_PUSH_STR_TOKEN   - the argument of push is invalid
                                                                                        ASM_OK					 - OK!
**/
int asm_cmd_push(FILE *strin, double *codes, int *cur_code);
/**

                asm_push_code
function saves the instruction to memory and increases the pointer

                @param[out]		codes the memory array
                @param[out]		cur_code
current memory pointer
                @param			value
the value to be saved

                @return
ASM_BAD_CUR_CODE_POINTER		- the pointer of cur_code is broken
                                                                                        ASM_BAD_CODES_POINTER			- codes[] pointer is null
                                                                                        ASM_CUR_CODE_NUM_OUT_OF_RANGE	- cur_code is invalid
                                                                                        ASM_BAD_CODES_POINTER			- codes pointer is invalid
                                                                                        ASM_OK							- ok!
**/
int asm_push_code(double *codes, int *cur_code, double value);
/**
                asm_cmd_convert
function converts the word with command into constant value from table

                @param[out]		word
the word to be converted
                @param[out]		c
the variable where the value would be saved

                @return
ASM_BAD_COMMAND_TOKEN			- the command is invalid ASM_OK
- ok!
**/
int asm_cmd_convert(const char *word, int *c);
/**
                asm_mark
the function that initializes new mark

                @param[out]		word analysing word
                @param			cur_code
current memory pointer
                @param[out]		pts
the array of pointers

                @return
ASM_MARK_NOT_MARK		- invalid mark
                                                                                        ASM_TOO_BIG_MARK		- the name of mark is too big
                                                                                        ASM_OVERUSED_MARK		- this mark has been already used
                                                                                        ASM_NO_FREE_MARKS       - not enough space for new mark
                                                                                        ASM_OK					- ok!

**/
int asm_mark(char *word, int cur_code, pointer *pts);

#define CONVERT_REG_(word, reg) (strcmp(word, #reg) == 0) ? STR_##reg:

int error_asm =
    0; //!< Global variable created for better error testing in SEC_RUN_

#define SEC_RUN_(func)                                                         \
  if ((error_asm = (func)) != ASM_OK)                                          \
    return error_asm;

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

int asm_mark(char *word, int cur_code, pointer *pts) {
  if (word[0] != ':')
    return ASM_MARK_NOT_MARK;
  bool found_name = false;
  if (strlen(word) > NAME_LEN) {
    // fprintf(strerr, "\nToo big mark [%s]", &(word[1]));
    return ASM_TOO_BIG_MARK;
  }
  for (int i = 0; i < NUM_OF_POINTERS; ++i)
    if (strcmp(pts[i].name, &(word[1])) == 0) {
      if ((pts[i].mark != POISON_MARK) && (pts[i].mark != cur_code)) {
        // fprintf(strerr, "\nMark [%s] has been used more than once",
        // &(word[1]));
        return ASM_OVERUSED_MARK;
      }
      pts[i].mark = cur_code;
      found_name = true;
      break;
    }

  if (found_name == false) {
    int i = 0;
    while ((pts[i].name[0] != 0) && (i < NUM_OF_POINTERS))
      i++;

    if (i == NUM_OF_POINTERS) {
      // fprintf(strerr, "\nMaximum quantity of marks reached\n");
      return ASM_NO_FREE_MARKS;
    }

    strcpy(pts[i].name, &(word[1]));
    pts[i].mark = cur_code;
  }
  return ASM_OK;
}

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

#define CHECK_COMMAND(str, name) (strcmp(str, #name) == 0) ? CMD_##name:

int asm_cmd_convert(const char *word, int *c) {
  *c = CHECK_COMMAND(word, PUSH) CHECK_COMMAND(word, POP) CHECK_COMMAND(
      word, ADD) CHECK_COMMAND(word, SUB) CHECK_COMMAND(word, MUL)
      CHECK_COMMAND(word, DIV) CHECK_COMMAND(word, SIN) CHECK_COMMAND(word, COS)
          CHECK_COMMAND(word, TAN) CHECK_COMMAND(word, SQRT) CHECK_COMMAND(
              word, POW) CHECK_COMMAND(word, END) CHECK_COMMAND(word, DUMP)
              CHECK_COMMAND(word, ENTER) CHECK_COMMAND(word, TAB) CHECK_COMMAND(
                  word, SPACE) CHECK_COMMAND(word, OUT) CHECK_COMMAND(word, MOV)
                  CHECK_COMMAND(word, SWAP) CHECK_COMMAND(word, DUB)
                      CHECK_COMMAND(word, JMP) CHECK_COMMAND(word, JBE)
                          CHECK_COMMAND(word, JB) CHECK_COMMAND(word, JAE)
                              CHECK_COMMAND(word, JA) CHECK_COMMAND(word, JE)
                                  CHECK_COMMAND(word, JNE)
                                      CHECK_COMMAND(word, FUNC)
                                          CHECK_COMMAND(word, CALL)
                                              CHECK_COMMAND(word, RET)
                                                  CHECK_COMMAND(word, IN)
                                                      CMD_NONE;
  if (*c == CMD_NONE)
    return ASM_BAD_COMMAND_TOKEN;
  return ASM_OK;
}

#undef CHECK_COMMAND

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

int asm_push_code(double *codes, int *cur_code, double value) {
  if (codes == NULL)
    return ASM_BAD_CODES_POINTER;
  if (cur_code == NULL)
    return ASM_BAD_CUR_CODE_POINTER;
  if ((0 > *cur_code) || (*cur_code >= MAXCODES - 1))
    return ASM_CUR_CODE_NUM_OUT_OF_RANGE;
  codes[*cur_code] = value;
  // printf("%lg\n", value);
  (*cur_code)++;
  return ASM_OK;
}

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

int asm_cmd_push(FILE *strin, double *codes, int *cur_code) {
  if (strin == NULL)
    return ASM_STRIN_BAD;
  if (codes == NULL)
    return ASM_BAD_CODES_POINTER;
  if (cur_code == NULL)
    return ASM_BAD_CUR_CODE_POINTER;

  char push_word[CMD_MAXLEN] = {};

  int cond = fscanf_s(strin, "%s", push_word, CMD_MAXLEN);
  if (cond <= 0)
    return ASM_SCAN_FAILED;

  double push_value = 0;

  int is_value = sscanf(push_word, "%lg", &push_value);

  if (is_value) {
    SEC_RUN_(asm_push_code(codes, cur_code, STR_value));
    SEC_RUN_(asm_push_code(codes, cur_code, push_value));
  } else {
    double reg = 0;
    int ret = asm_str_convert(_strlwr(push_word), &reg);
    if (ret != ASM_OK)
      return ASM_BAD_PUSH_STR_TOKEN;

    SEC_RUN_(asm_push_code(codes, cur_code, reg));
    SEC_RUN_(asm_push_code(codes, cur_code, 0));
  }
  return ASM_OK;
}

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

int asm_str_convert(char *word, double *reg) {
  VERIFY(word);
  VERIFY(reg);

  double ret = CONVERT_REG_(word, ax) CONVERT_REG_(word, bx)
      CONVERT_REG_(word, cx) CONVERT_REG_(word, dx) CONVERT_REG_(word, st)
          CONVERT_REG_(word, out) CONVERT_REG_(word, ch) STR_NON;
  if (ret == STR_NON)
    return ASM_BAD_STR_TOKEN;
  *reg = ret;
  return ASM_OK;
}

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

int asm_cmd_in(FILE *strin, double *codes, int *cur_code) {
  if (strin == NULL)
    return ASM_STRIN_BAD;
  if (codes == NULL)
    return ASM_BAD_CODES_POINTER;
  if (cur_code == NULL)
    return ASM_BAD_CUR_CODE_POINTER;

  char in_word[CMD_MAXLEN] = {};
  int cond = fscanf_s(strin, "%s", in_word, CMD_MAXLEN);
  if (cond <= 0)
    return ASM_SCAN_FAILED;

  double reg = 0;
  int ret = asm_str_convert(_strlwr(in_word), &reg);
  if (ret != ASM_OK)
    return ASM_BAD_IN_STR_TOKEN;

  SEC_RUN_(asm_push_code(codes, cur_code, reg));
  return ASM_OK;
}

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

int asm_cmd_pop(FILE *strin, double *codes, int *cur_code) {
  if (strin == NULL)
    return ASM_STRIN_BAD;
  if (codes == NULL)
    return ASM_BAD_CODES_POINTER;
  if (cur_code == NULL)
    return ASM_BAD_CUR_CODE_POINTER;

  char pop_word[CMD_MAXLEN] = {};

  int cond = fscanf_s(strin, "%s", pop_word, CMD_MAXLEN);
  if (cond <= 0)
    return ASM_SCAN_FAILED;

  double reg = 0;
  int ret = asm_str_convert(_strlwr(pop_word), &reg);
  if (ret != ASM_OK)
    return ASM_BAD_POP_STR_TOKEN;

  SEC_RUN_(asm_push_code(codes, cur_code, reg));
  return ASM_OK;
}

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

int asm_cmd_out(FILE *strin, double *codes, int *cur_code) {
  if (strin == NULL)
    return ASM_STRIN_BAD;
  if (codes == NULL)
    return ASM_BAD_CODES_POINTER;
  if (cur_code == NULL)
    return ASM_BAD_CUR_CODE_POINTER;

  char out_word[CMD_MAXLEN] = {};
  int cond = fscanf_s(strin, "%s", out_word, CMD_MAXLEN);
  if (cond <= 0)
    return ASM_SCAN_FAILED;

  double reg = 0;
  int ret = asm_str_convert(_strlwr(out_word), &reg);

  if (ret != ASM_OK)
    return ASM_BAD_OUT_STR_TOKEN;

  if (reg == STR_ch) {
    int out_char = -1;
    cond = fscanf_s(strin, "%d", &out_char);
    if (cond <= 0)
      return ASM_OUT_BAD_CHAR_ARGUMENT;

    SEC_RUN_(asm_push_code(codes, cur_code, reg));
    SEC_RUN_(asm_push_code(codes, cur_code, out_char));
  } else {
    SEC_RUN_(asm_push_code(codes, cur_code, reg));
    SEC_RUN_(asm_push_code(codes, cur_code, 0));
  }
  return ASM_OK;
}

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

int asm_cmd_mov(FILE *strin, double *codes, int *cur_code) {
  if (strin == NULL)
    return ASM_STRIN_BAD;
  if (codes == NULL)
    return ASM_BAD_CODES_POINTER;
  if (cur_code == NULL)
    return ASM_BAD_CUR_CODE_POINTER;

  char mov_word1[CMD_MAXLEN] = {};
  char mov_word2[CMD_MAXLEN] = {};

  int cond = fscanf_s(strin, "%s", mov_word1, CMD_MAXLEN);
  if (cond <= 0)
    return ASM_SCAN_FAILED;

  cond = fscanf_s(strin, "%s", mov_word2, CMD_MAXLEN);
  if (cond <= 0)
    return ASM_SCAN_FAILED;

  double mov_arg1 = 0;

  int ret = asm_str_convert(mov_word1, &mov_arg1);
  if (ret != ASM_OK)
    return ASM_BAD_MOV_TOKEN_1;

  double mov_value = -1;

  cond = sscanf(mov_word2, "%lg", &mov_value);
  double mov_arg2 = 0;

  if (cond != 0)
    mov_arg2 = STR_value;
  else {
    mov_arg2 = 0;
    ret = asm_str_convert(mov_word2, &mov_arg2);
    if (ret != ASM_OK)
      return ASM_BAD_MOV_TOKEN_2;
  }

  SEC_RUN_(asm_push_code(codes, cur_code, mov_arg1));
  SEC_RUN_(asm_push_code(codes, cur_code, mov_arg2));
  SEC_RUN_(asm_push_code(codes, cur_code, mov_value));

  return ASM_OK;
}

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

int asm_cmd_jump_like(FILE *strin, double *codes, int *cur_code, const int arg,
                      pointer *pts) {
  if (strin == NULL)
    return ASM_STRIN_BAD;
  if (codes == NULL)
    return ASM_BAD_CODES_POINTER;
  if (cur_code == NULL)
    return ASM_BAD_CUR_CODE_POINTER;
  VERIFY(pts);

  char jump_mark[CMD_MAXLEN] = {};
  int cond = fscanf_s(strin, "%s", jump_mark, CMD_MAXLEN);

  if (cond <= 0)
    return ASM_SCAN_FAILED;
  if (jump_mark[0] != ':')
    return ASM_JUMP_NOT_MARK;

  int i = 0;
  while ((strcmp(pts[i].name, &(jump_mark[1])) != 0) && (i < NUM_OF_POINTERS))
    i++;
  if (i != NUM_OF_POINTERS) {
    if (arg == CMD_FUNC)
      cur_code--;
    SEC_RUN_(asm_push_code(codes, cur_code, pts[i].mark));
    return ASM_OK;
  }
  i = 0;
  while ((pts[i].name[0] != 0) && (i < NUM_OF_POINTERS))
    i++;
  if (i == NUM_OF_POINTERS)
    return ASM_NO_FREE_MARKS;

  strcpy(pts[i].name, &(jump_mark[1]));
  if (arg == CMD_FUNC)
    cur_code--;
  SEC_RUN_(asm_push_code(codes, cur_code, pts[i].mark));
  return ASM_OK;
}

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

int asm_error_catcher(FILE *strerr, int cond) {
  VERIFY(strerr);
  if ((cond < ASM_OK) || (cond > ASM_STRIN_BAD)) {
    fprintf(strerr, "\nUNKNOWN ERROR\n");
    return ASM_ERROR_CATCHER_UNKNOWN;
  }
  if (cond != ASM_OK) {
    fprintf(strerr, asm_msgs[cond - ASM_OK]);
    return ASM_ERROR_CATCHER_BAD;
  }
  return ASM_ERROR_CATCHER_OK;
}

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

int asm_is_mrk(FILE *strin, FILE *strerr, char *word, int *cur_code,
               pointer *pts, int (*error_catcher)(FILE *strerr, int cond)) {
  VERIFY(strin);
  VERIFY(strerr);
  VERIFY(word);
  VERIFY(cur_code);
  VERIFY(pts);
  VERIFY((*error_catcher));

  bool is_func = false;

  if (strcmp(_strlwr(word), "func") == 0)
    is_func = true;

  if (is_func == true) {
    int cond = fscanf_s(strin, "%s", word, CMD_MAXLEN);
    if (cond <= 0)
      return (*error_catcher)(strerr, ASM_SCAN_FAILED);
  }
  if ((word[0] != ':') && (is_func == true))
    return (*error_catcher)(strerr, ASM_FUNC_BAD_MARK);
  if (word[0] != ':')
    return ASM_NOT_MARK;

  int ret = (*error_catcher)(strerr, asm_mark(word, *cur_code, pts));
  return ret;
}