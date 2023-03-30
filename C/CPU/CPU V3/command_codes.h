
enum commands {
  CMD_NONE = 1000,
  CMD_PUSH = 1001,
  CMD_POP = 1002,
  CMD_ADD = 1003,
  CMD_SUB = 1004,
  CMD_MUL = 1005,
  CMD_DIV = 1006,
  CMD_SIN = 1007,
  CMD_COS = 1008,
  CMD_TAN = 1009,
  CMD_SQRT = 1010,
  CMD_POW = 1011,
  CMD_END = 1012,
  CMD_DUMP = 1013,
  CMD_SPACE = 1014,
  CMD_ENTER = 1015,
  CMD_TAB = 1016,
  CMD_OUT = 1017,
  CMD_MOV = 1018,
  CMD_SWAP = 1019,
  CMD_DUB = 1020,
  CMD_JMP = 1021,
  CMD_JBE = 1022,
  CMD_JB = 1023,
  CMD_JAE = 1024,
  CMD_JA = 1025,
  CMD_JE = 1026,
  CMD_JNE = 1027,
  CMD_ERROR = 1028,
  CMD_FUNC = 1029,
  CMD_CALL = 1030,
  CMD_RET = 1031,
  CMD_IN = 1032,
};

enum streams {
  STR_NON = 900,
  STR_ax = 901,
  STR_bx = 902,
  STR_cx = 903,
  STR_dx = 904,
  STR_out = 905,
  STR_st = 906, // stack
  STR_ch = 907, // char
  STR_value = 908,
  STR_sys_reg = 909,
};

enum cpu_errors {
  // CPU_ERROR_NULL					= 1100,
  CPU_CHECK_NULL = 1101,
  CPU_CHECK_OK = 1102,
  CPU_CHECK_INV_STACK = 1103,
  CPU_ERROR_STACK_FULL = 1104,
  CPU_ERROR_STACK_EMPTY = 1105,
  CPU_OK = 1106,
  CPU_PUSH_INV_TOKEN = 1107,
  CPU_BROKEN_START = 1108,
  CPU_BROKEN_FINISH = 1109,
  CPU_NOT_ENOUGH_ARGS = 1110,
  CPU_POP_VALUE_NULL = 1111,
  CPU_ERROR_DIV_BY_ZERO = 1112,
  CPU_ERROR_NEGATIVE_BASE = 1113,
  CPU_ERROR_SQRT_NEGATIVE = 1114,
  CPU_ERROR_CATCHER_OK = 1115,
  CPU_ERROR_CATCHER_BAD = 1116,
  CPU_ERROR_PUSH_BAD_TOKEN = 1117,
  CPU_OUT_STREAM_IN_NULL = 1118,
  CPU_OUT_STREAM_OUT_NULL = 1119,
  CPU_OUT_BAD_TOKEN = 1120,
  CPU_OUT_STREAM_ERROR_NULL = 1121,
  CPU_MOV_BAD_TOKEN = 1122,
  LOAD_ERROR_UNEXPECTED_END_OF_FILE = 1123,
  CPU_POINTER_OUT_OF_RANGE = 1124,
  CPU_IN_BAD_TOKEN = 1125,
  CPU_IN_READING_FAILURE = 1126,
};

enum asm_func_errors {
  ASM_OK = 1500,
  ASM_TOO_BIG_MARK = 1501,
  ASM_OVERUSED_MARK = 1502,
  ASM_NO_FREE_MARKS = 1503,
  ASM_BAD_COMMAND_TOKEN = 1504,
  ASM_BAD_CODES_POINTER = 1505,
  ASM_BAD_CUR_CODE_POINTER = 1506,
  ASM_CUR_CODE_NUM_OUT_OF_RANGE = 1507,
  ASM_BAD_STR_TOKEN = 1508,
  ASM_BAD_IN_STR_TOKEN = 1509,
  ASM_BAD_PUSH_STR_TOKEN = 1510,
  ASM_BAD_POP_STR_TOKEN = 1511,
  ASM_SCAN_FAILED = 1512,
  ASM_BAD_OUT_STR_TOKEN = 1513,
  ASM_OUT_BAD_CHAR_ARGUMENT = 1514,
  ASM_JUMP_NOT_MARK = 1515,
  ASM_MARK_NOT_MARK = 1516,
  ASM_BAD_MOV_TOKEN_1 = 1517,
  ASM_BAD_MOV_TOKEN_2 = 1518,
  ASM_FUNC_BAD_MARK = 1519,
  ASM_STRIN_BAD = 1520,

};

const char *const asm_msgs[] = {
    "\nOK\n",
    "\nToo long name of mark\n",
    "\nMark has been used more than once\n",
    "\nMarks buffer overload\n",
    "\nBad token, unknown command\n",
    "\nCommands array pointer is broken\n",
    "\nCur_code pointer broken\n",
    "\nCur_code is out of range\n",
    "\nASM_STR_CONVERT: unknown token!\n",
    "\nASM_CMD_IN: unknown argument token!\n",
    "\nASM_CMD_PUSH: unknown argument token!\n",
    "\nASM_CMD_POP: unknown argument token!\n",
    "\nUnexpectible end of file!\n",
    "\nASM_CMD_OUT: unknown argument token!\n",
    "\nASM_CMD_OUT: bad CH argument, should be integer (0<= arg <=255)\n",
    "\nASM_CMD_JUMP_LIKE: mark broken\n",
    "\nASM_CMD_MARK: mark broken\n",
    "\nASM_CMD_MOV: unknown first argument token!\n",
    "\nASM_CMD_MOV: unknown second argument token!\n",
    "\nBad function name\n",

    "\nInput stream is NULL\n",

};

enum draw_conditions {
  DRAW_BAD = 1301,
  DRAW_OK = 1302,
};

enum calc_errors {
  CALC_BAD = 1201,
  CALC_OK = 1202,
};

enum exe_errors {
  EXE_BAD = 1301,
  EXE_OK = 1302,
};

enum asm_errors {
  ASM_FAIL = 1401,
  ASM_ERROR_CATCHER_OK = 1402,
  ASM_ERROR_CATCHER_BAD = 1403,
  ASM_ERROR_CATCHER_UNKNOWN = 1404,
  ASM_NOT_MARK = 1405,
};

enum stack_errors {
  OK = 2000,
  ERR_INIT = 2001,
  ERR_NULL = 2002,
  ERR_WRONG_SZ = 2003,
  ERR_PRINT = 2004
};

const double EPSILON = 0.00000000001;

const int CPU_STACK_SIZE = 1000;

const int POISON = 666;

const int POISON_MARK = -228;

const int CMD_MAXLEN = 30;

const int NUM_OF_POINTERS = 11;

const int SIZE_OF_FUNC_STACK = 100;