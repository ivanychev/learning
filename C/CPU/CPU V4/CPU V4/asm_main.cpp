
#include "command_codes.h"
#include "cpu.h"

/**
                        main
Function builds executable.txt and executable.ivz (my own format:) files and
uses asm() executable.txt contains all instructions and arguments printed in
.txt file using '\n' executable.ivz is kind of the same file, but the data has
been saved in binary format
                        @return						0
**/

#define CHECK_PTR_HEALTH(ptr, msg, ret)                                        \
  if (ptr == NULL) {                                                           \
    fprintf_s(strerr, msg);                                                    \
    fclose(strerr);                                                            \
    return ret;                                                                \
  }

int asm_main(char *filename) {
  FILE *strerr = NULL;
  fopen_s(&strerr, "asm_log.txt", "w");
  VERIFY(strerr != NULL);

  FILE *strin = NULL;
  fopen_s(&strin, filename, "r");
  CHECK_PTR_HEALTH(strin, "\nCode.txt opening error\n", ASM_FAIL);

  FILE *strout_bin = NULL;
  fopen_s(&strout_bin, "executable.ivz", "wb");
  CHECK_PTR_HEALTH(strout_bin, "\nexecutable.ivz opening error\n", ASM_FAIL);

  FILE *strout_txt = NULL;
  fopen_s(&strout_txt, "executable.txt", "w");
  CHECK_PTR_HEALTH(strout_txt, "\nexecutable.ivz openning error\n", ASM_FAIL);

  pointer pts[NUM_OF_POINTERS] = {};
  for (int i = 0; i < NUM_OF_POINTERS; ++i) {
    (pts[i]).mark = POISON_MARK;
    for (int j = 0; j < NAME_LEN; ++j)
      (pts[i]).name[j] = 0;
  }

  var vars[NUM_OF_VARS] = {};

  for (int i = 0; i < NUM_OF_VARS; ++i)
    for (int j = 0; j < MAX_VAR_NAME; ++j)
      (vars[i]).name[j] = 0;

  double *code = assemble(strin, strerr, pts, vars, asm_error_catcher);

  if (code == NULL) {
    fprintf_s(strerr, "\nAssemble failed\n");

    fclose(strin);
    fclose(strout_txt);
    fclose(strout_bin);

    fopen_s(&strout_bin, "executable.ivz", "wb");
    CHECK_PTR_HEALTH(strout_bin, "\nexecutable.ivz opening error\n", ASM_FAIL);
    fopen_s(&strout_txt, "executable.txt", "w");
    CHECK_PTR_HEALTH(strout_txt, "\nexecutable.ivz openning error\n", ASM_FAIL);

    fclose(strout_txt);
    fclose(strout_bin);

    fclose(strerr);
    return ASM_FAIL;
  }

  fclose(strin);

  fopen_s(&strin, "code.txt", "r");
  CHECK_PTR_HEALTH(strin, "\nCode.txt opening error\n", ASM_FAIL);

  code = assemble(strin, strerr, pts, vars, asm_error_catcher);
  CHECK_PTR_HEALTH(code, "\nAssemblation failed!\n", ASM_FAIL);

  size_t fwrite_ret = fwrite(code, sizeof(double), MAXCODES, strout_bin);

  int i = 0;
  while (code[i++] != CMD_END)
    fprintf(strout_txt, "%lg\n", code[i - 1]);
  fprintf_s(strout_txt, "%lg\n", code[i - 1]);

  fclose(strin);
  fclose(strout_txt);
  fclose(strout_bin);
  fclose(strerr);

  free(code);
  code = NULL;
  return ASM_OK;
}
