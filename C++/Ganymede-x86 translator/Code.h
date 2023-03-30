#include "Ganymede-x86.h"

struct Command;

#define DEF_INSERT(name) void name##_translate(unsigned int number);

struct Code {
  Command **command_array;
  unsigned int size;
  unsigned int buffer_size;
  const int block_size = 30;
  ifstream &source;
  ofstream &compiled;
  ofstream &log_stream;
  unsigned int variables_ammount = 0;

  Code(ifstream &code_source, ofstream &log, ofstream &to_compile);
  ~Code();

  bool increase_buffer();
  bool add_command(Command *new_command);
  bool get_code();
  bool prepare_code();
  bool check() const;

  bool revive_code();
  unsigned char *first_jump_patch() const;

  void deal_with_out_ch();
  void deal_with_push_val();
  void deal_with_mov_val();
  void deal_with_in_st();
  void deal_with_out_st();

  void calculate_addresses();
  void calc_commands();

  void patch_exe(ofstream &exe) const;
  void print_code(ostream &stream) const;

  void conditional_jumps_common(unsigned number);

  void console_print_gan_code() const;

//------------------------Translating functions----------------------
#define _I(name) DEF_INSERT(name)
#include "Ganymede_instructions.h"
};
#undef _I

const unsigned MAINCODEBEGIN_EXE = 0x00000400;
const unsigned MAINCODEBEGIN_ADDR = 0x00401000;
const unsigned FIRST_JUMP_ADDR = MAINCODEBEGIN_ADDR;
const unsigned VARIABLES_BEGIN = 0x004051BE;
const unsigned TEMPLATE_EXE_SIZE = 0x00003000;
const unsigned CODE_BEGIN = 0x00401088;

const unsigned PRINTF = 0x0040371E;
const unsigned GETCHAR = 0x00403724;
const unsigned SCANF = 0x0040372A;
const unsigned MEMCPY = 0x00403730;
const unsigned POW = 0x00403736;
const unsigned PUTCHAR = 0x0040373c;
const unsigned EXITPROCESS = 0x00403718;
const unsigned LEN64 = 0x00000008;
const unsigned FLOAT_ERROR = 0x00405046;

const unsigned AX = 0x00405000;
const unsigned BX = 0x00405008;
const unsigned CX = 0x00405010;
const unsigned DX = 0x00405018;
const unsigned DI = 0x00405020;
const unsigned SI = 0x00405028;
const unsigned BUFFER = 0x00405030;
const unsigned FIO = 0x00405031;
const unsigned ENTER = 0x00405035;
const unsigned SPACE = 0x00405038;
const unsigned TAB = 0x0040503A;
const unsigned ABOVE = 0x0040503C;
const unsigned BELOW = 0x0040503e;
const unsigned EQUALL = 0x00405040;
const unsigned UNEQU = 0x00405042;
const unsigned FERROR = 0x00405044;

unsigned var_address(double number);
void patch_jmp_offset(unsigned unreversed_from, unsigned unreversed_to,
                      char *dest);
unsigned int file_offset(unsigned int address);
unsigned int count_jump(unsigned from, unsigned to);
// unsigned int	change_endian(unsigned arg);
void patch_dword(unsigned unreversed_value, char *dest);
void patch_to_gan(Code *code, char *dest, double gan_num, unsigned from);
