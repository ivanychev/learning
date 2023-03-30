/**
                @file			Code.cpp


                @par			The defenitions of all CODE object
methods are located here.

**/

#include "Code.h"
#include "command.h"
#include "exception.h"

typedef void (Code::*tr_func)(unsigned number);
extern tr_func translation_funcs[];

const int LENGTH_OF_JUMP_PROCEDURE = 5;

//--------------------------------------------USABLE
//FUNCTIONS--------------------------------------------------------

/**
                        change_endian				function turns
order of bytes in UNSIGNED to the opposite. Yeah, pointers. That function is not
used in build (V 1.1)

                        @todo						Use
standard function
**/

unsigned int change_endian(unsigned arg) {
  unsigned changed = 0x00000000;

  *(unsigned char *)((unsigned)(&changed) + 3) =
      *(unsigned char *)((unsigned)(&arg) + 0);
  *(unsigned char *)((unsigned)(&changed) + 2) =
      *(unsigned char *)((unsigned)(&arg) + 1);
  *(unsigned char *)((unsigned)(&changed) + 1) =
      *(unsigned char *)((unsigned)(&arg) + 2);
  *(unsigned char *)((unsigned)(&changed) + 0) =
      *(unsigned char *)((unsigned)(&arg) + 3);

  return changed;
}

//----------------------------------------------------------------------------------------------------------------------

/**
                @par			Some of usable function, that are called
in translate library are located here. Thay are aimed to count jump offsets,
differences of addresses, calculating variables addresses, and patching into
Code object


**/

unsigned int count_jump(unsigned from, unsigned to) {
  return /*change_endian*/ (to - from - LENGTH_OF_JUMP_PROCEDURE);
}

void patch_jmp_offset(unsigned unreversed_from, unsigned unreversed_to,
                      char *dest) {
  CHECK_PTR(dest);

  unsigned offset = count_jump(unreversed_from, unreversed_to);

  char *copy_destination = (char *)((unsigned)dest /* + 1*/);

  CALL(patch_dword(offset, copy_destination), "JMPLIKE patching code failed");
}

void patch_dword(unsigned unreversed_value, char *dest) {
  CHECK_PTR(dest);
  *(unsigned *)(dest) = unreversed_value;
}

//----------------------------------------------------------------------------------------------------------------------

unsigned get_jmp_address(Code *code, double jmp_arg);

void patch_to_gan(Code *code, char *dest, double gan_num, unsigned from) {
  LG_ASSERT((gan_num >= 0) && (IS_ZERO(gan_num - abs(gan_num))),
            "Wrong gan number format");
  CHECK_PTR(code);
  unsigned addr = get_jmp_address(code, gan_num);
  unsigned offset = count_jump(from, addr);

  patch_dword(offset, dest);
}

unsigned get_jmp_address(Code *code, double jmp_arg) {
  int jmp_num = (unsigned)jmp_arg;
  int counter = 0;
  while (jmp_num > 0) {
    LG_ASSERT(counter < code->size, "Out of array bounds");
    jmp_num -= code->command_array[counter++]->gan_length;
  }
  assert(jmp_num == 0);
  return code->command_array[counter]->x86_address;
}

unsigned var_address(double number) {
  LG_ASSERT((number >= 0) && (IS_ZERO(number - abs(number))),
            "Invalid variable number");
  unsigned var_num = (unsigned)number;
  return VARIABLES_BEGIN + (var_num)*LEN64;
}

//---------------------------------FILE--------------------------------------------------

unsigned int file_offset(unsigned int address) {
  return address - (MAINCODEBEGIN_ADDR - MAINCODEBEGIN_EXE);
}

unsigned int address_get(unsigned int offset) {
  return offset - (MAINCODEBEGIN_EXE - MAINCODEBEGIN_ADDR);
}

//----------------------------------------------------------------------------------------------------------------------

/**
                Code::console_print_gan_code
debug print of Code object to console

**/
void Code::console_print_gan_code() const {
  cout << "============= CODE CONSOLE BEGIN =============";
  for (unsigned int i = 0; i < size; ++i) {
    cout << "\t\t\t" << i << "'th Command" << endl;
    command_array[i]->console_print_ganymede_command();
  }
  cout << "=============  CODE CONSOLE END  =============";
}

Code::Code(ifstream &code_source, ofstream &log, ofstream &to_compile)
    : size(0), buffer_size(0), block_size(30), log_stream(log),
      source(code_source), compiled(to_compile) {

  bool incr_check = true;

  CALL(incr_check = increase_buffer(),
       "Buffer increase failed. Terminating...");
  RT_ASSERT(incr_check == true, "Buffer increase failed. Terminating...");
  RT_ASSERT(check(), "Buffer verification failed");

  BUFFER_CHECK;
}

//----------------------------------------------------------------------------------------------------------------------

Code::~Code() {
  if (command_array != NULL) {
    for (unsigned int i = 0; i < size; ++i) {
      delete command_array[i];
      command_array[i] = NULL;
    }
    delete command_array;
    command_array = NULL;
  }
  size = int_poison;
  buffer_size = int_poison;
};

//----------------------------------------------------------------------------------------------------------------------

/**
                        increse_buffer()				The
array increases the buffer of Command pointers on the value of block_size
**/

bool Code::increase_buffer() {
  BUFFER_CHECK;

  Command **new_buffer = NULL;
  TRY_ALLOC(new_buffer, Command * [buffer_size + block_size]);

  if (size != 0)
    memcpy(new_buffer, command_array, sizeof(Command *) * size);
  for (unsigned int i = size; i < buffer_size; ++i)
    new_buffer[i] = NULL;
  if (size != 0)
    for (unsigned int i = 0; i < size; ++i)
      command_array[i] = NULL;

  if (size != 0)
    delete command_array;
  command_array = new_buffer;
  buffer_size += block_size;

  BUFFER_CHECK;
  return true;
}

//----------------------------------------------------------------------------------------------------------------------

#define START_CODE_CHECK_REPORT                                                \
  if (condition == true)                                                       \
    log_stream << "Unsuccessfull Code buffer report started...\n";             \
  is_reported = true;

bool Code::check() const {
  bool condition = true;
  bool is_reported = false;

  if (log_stream.is_open() == false) {
    cout << "WARNING: Logging file of is not opened\n"
         << "Function:\t\t" << __FUNCSIG__ << endl
         << "Line:\t\t" << __LINE__ << endl
         << "File:\t\t" << __FILE__ << endl;
    return false;
  }

  if (source.is_open() == false) {
    START_CODE_CHECK_REPORT;
    condition = false;
    log_stream << "Source file isn't opened" << endl;
  }

  if (command_array == NULL) {
    START_CODE_CHECK_REPORT;
    condition = false;
    log_stream << "Buffer pointer is NULL" << endl;
  }

  if (size > buffer_size) {
    START_CODE_CHECK_REPORT;
    condition = false;
    log_stream << "Size is bigger than buffer size" << endl;
  }

  return condition;
}

//----------------------------------------------------------------------------------------------------------------------

/**
                        add_command					that
function gets input Command pointer and saves it in Command* buffer, increasing
it, if there isn't any free cells
**/
bool Code::add_command(Command *new_command) {
  BUFFER_CHECK;
  if (buffer_size == size) {
    CALL(increase_buffer(), "Buffer increase failed");
  }

  if (new_command->check() != true) {
    LOG_MESSAGE("Argumented new command isn't valid");
    return false;
  }

  command_array[size++] = new_command;

  BUFFER_CHECK;
  return true;
}

//----------------------------------------------------------------------------------------------------------------------

/**
                        get_code					the main
function of scanning the input Ganymede binary file for Ganymede commands and
arguments. Function scans for the next command, creates the Command object for
it and saves it.

**/

bool Code::get_code() {
  BUFFER_CHECK;

  bool end_reached = false;
  Command *getting = NULL;
  while (end_reached == false) {
    CALL(getting = new Command(log_stream),
         "Construction new command object failed");
    RT_ASSERT(getting->get_command(source) == true,
              "Getting next command failed.");
    RT_ASSERT(add_command(getting) == true, "Adding scanned command failed.");

    if (IS_ZERO(getting->gan_codes[0] - CMD_END))
      end_reached = true;
  }

  BUFFER_CHECK;
  return true;
}

//----------------------------------------------------------------------------------------------------------------------

/**
                        revive_code				The code, that
is scanned and got its x86 template is not executable yet due to the lack of
addresses and offsets there. Reviving is calculating and pasting everything in
Code object to get ready to patch it in the output file

**/
bool Code::revive_code() {
  BUFFER_CHECK;

  unsigned count_vars = 0;

  for (unsigned i = 0; i < size; ++i)
    if (IS_ZERO(command_array[i]->gan_codes[0] - (double)CMD_DEF))
      count_vars++;

  variables_ammount = count_vars;

  CALL(first_jump_patch(), "First jump patching failed");
  CALL(deal_with_out_ch(), "Failed to remake OUT CH ganymede commands");
  CALL(deal_with_push_val(), "Failed to remake PUSH OUT ganymede commands");
  CALL(deal_with_out_st(), "Failed to remake OUT ST ganymede commands");
  CALL(deal_with_in_st(), "Failed to remake IN ST ganymede commands");

  CALL(calculate_addresses(),
       "Failed to insert x86 adresses in Code structure");
  CALL(calc_commands(), "Failed to calculate offsets and addresses");

  print_code(cout);
  return true;
}

void Code::calculate_addresses() {
  command_array[0]->x86_address = CODE_BEGIN;

  for (unsigned i = 1; i < size; ++i)
    command_array[i]->x86_address =
        command_array[i - 1]->x86_address + command_array[i - 1]->x86_length;
}

//----------------------------------------------------------------------------------------------------------------------

/**
                        Some of particulars here
**/

#define RELOAD_CMD(name, gan_command, gan_len, template_)                      \
                                                                               \
  try {                                                                        \
    double temp_buffer[MAXGANCOMMAND] = {0, 0, 0, 0};                          \
    int temp_size = 0;                                                         \
    temp_size = command_array[i]->gan_length;                                  \
    assert(command_array[i]->gan_length <= MAXGANCOMMAND);                     \
    for (int j = 0; j < temp_size; ++j)                                        \
      temp_buffer[j] =                                                         \
          command_array[i]                                                     \
              ->gan_codes[j]; /* copying gan_codes to temp buffer*/            \
    delete command_array[i];                                                   \
    command_array[i] = new Command(log_stream);                                \
    (*(command_array[i]))                                                      \
        .load_template(Template_command(gan_command, gan_len,                  \
                                        (char *)template_, sizeof(template_),  \
                                        log_stream));                          \
    for (int j = 0; j < temp_size; ++j)                                        \
      command_array[i]->gan_codes[j] = temp_buffer[j];                         \
  }                                                                            \
  CATCH_IV("Failed to deal with " #name);

void Code::deal_with_out_ch() {
  for (unsigned i = 0; i < size; ++i) {
    cout << command_array[i]->gan_codes[0] << " "
         << command_array[i]->gan_codes[1] << endl;
    if (IS_ZERO(command_array[i]->gan_codes[0] - CMD_OUT) &&
        IS_ZERO(command_array[i]->gan_codes[1] - STR_ch)) {
      command_array[i]->console_print_ganymede_command();
      RELOAD_CMD("OUT CH", CMD_OUT, 3, TR_OUT_CH);
      command_array[i]->console_print_ganymede_command();
    }
  }
  BUFFER_CHECK;
}

//----------------------------------------------------------------------------------------------------------------------

void Code::deal_with_push_val() {
  for (unsigned i = 0; i < size; ++i)
    if (IS_ZERO(command_array[i]->gan_codes[0] - CMD_PUSH) &&
        IS_ZERO(command_array[i]->gan_codes[1] - STR_value)) {
      command_array[i]->console_print_ganymede_command();
      RELOAD_CMD("PUSH VAL", CMD_PUSH, 3, TR_PUSH_VAL);
      command_array[i]->console_print_ganymede_command();
    }
  BUFFER_CHECK;
}

//----------------------------------------------------------------------------------------------------------------------

void Code::deal_with_out_st() {
  for (unsigned i = 0; i < size; ++i)
    if (IS_ZERO(command_array[i]->gan_codes[0] - CMD_OUT) &&
        IS_ZERO(command_array[i]->gan_codes[1] - STR_st)) {
      command_array[i]->console_print_ganymede_command();
      RELOAD_CMD("OUT CH", CMD_OUT, 3, TR_OUT_ST);
      command_array[i]->console_print_ganymede_command();
    }
  BUFFER_CHECK;
}

//----------------------------------------------------------------------------------------------------------------------

void Code::deal_with_mov_val() {
  for (unsigned i = 0; i < size; ++i)
    if (IS_ZERO(command_array[i]->gan_codes[0] - CMD_MOV) &&
        IS_ZERO(command_array[i]->gan_codes[1] - STR_value)) {
      command_array[i]->console_print_ganymede_command();
      RELOAD_CMD("MOV VALUE", CMD_MOV, 4, TR_MOV_VAL);
      command_array[i]->console_print_ganymede_command();
    }
  BUFFER_CHECK;
}

//----------------------------------------------------------------------------------------------------------------------

void Code::deal_with_in_st() {
  for (unsigned i = 0; i < size; ++i)
    if (IS_ZERO(command_array[i]->gan_codes[0] - CMD_IN) &&
        IS_ZERO(command_array[i]->gan_codes[1] - STR_st)) {
      command_array[i]->console_print_ganymede_command();
      RELOAD_CMD("IN ST", CMD_IN, 2, TR_IN_ST);
      command_array[i]->console_print_ganymede_command();
    }
  BUFFER_CHECK;
}

//----------------------------------------------------------------------------------------------------------------------

void Code::calc_commands() {
  for (unsigned int i = 0; i < size; ++i) {
    command_array[i]->console_print_ganymede_command();
    unsigned number = (unsigned)(command_array[i]->gan_codes[0]) - CMD_NONE;
    CALL((this->*translation_funcs[number])(i), "Failed to translate command");
  }
  BUFFER_CHECK;
}

//----------------------------------------------------------------------------------------------------------------------

/**
                        print_code				debug print of
x86 translation, contained in Code object
**/

void Code::print_code(ostream &str) const {
  BUFFER_CHECK;

  str << "========== X86 CODE BEGIN ==========" << endl;
  str.unsetf(ios::dec);
  str.setf(ios::hex);

  for (unsigned i = 0; i < size; ++i) {
    command_array[i]->print_x86(str);
    str << endl;
  }
  str.unsetf(ios::hex);
  str.setf(ios::dec);
  str << "==========  X86 CODE END  ==========" << endl;
}

//----------------------------------------------------------------------------------------------------------------------

#define _DEBUG_PATCH(ptr, count)                                               \
  printf("\nWriting: %u: ", (unsigned)(exe.tellp()));                          \
  for (int j = 0; j < count; ++j)                                              \
    printf("%02hhx ", ptr[j]);                                                 \
  printf("\n");

#define WRITE(ptr, count)                                                      \
  exe.write(ptr, count);                                                       \
  _DEBUG_PATCH(ptr, count)

#define BIN_OUT(ptr, count)                                                    \
  for (int i = 0; i < count; ++i)                                              \
    printf("%02hhx ", ptr[i]);                                                 \
  putchar('\n');

/**
                patch_exe				function is responsible
for patching output file, which is template.exe (in v 1.1). Contains lots of
debug print

**/

static const int LENGTH_OF_JMP = 5;
void Code::patch_exe(ofstream &exe) const {
  BUFFER_CHECK;

  unsigned char *first_jump = NULL;

  CALL(first_jump = first_jump_patch(),
       "Failed to allocate memory for ganymede variables");

  BIN_OUT(first_jump, LENGTH_OF_JMP);
  // printf("%08x\n", file_offset(FIRST_JUMP_ADDR));
  exe.seekp(file_offset(FIRST_JUMP_ADDR));
  printf("%08x\n", (unsigned)(exe.tellp()));

  WRITE((char *)first_jump, LENGTH_OF_JMP);
  cout << "\n\n\n\n\n PATCHING BEGIN........\n\n\n\n";

  printf("\n%u\n", VARIABLES_BEGIN);
  printf("%u\n", CODE_BEGIN);

  printf("\n%u\n", file_offset(VARIABLES_BEGIN));
  printf("%u\n", file_offset(CODE_BEGIN));
  exe.seekp(file_offset(CODE_BEGIN));

  for (unsigned i = 0; i < size; ++i) {
    RT_ASSERT((exe.fail() == false) && (exe.bad() == false),
              "File reading error");
    command_array[i]->console_print_ganymede_command();
    WRITE(command_array[i]->x86_codes, command_array[i]->x86_length);
  }
  printf("%u", CODE_BEGIN);
  if (first_jump != NULL)
    delete first_jump;
}

//----------------------------------------------------------------------------------------------------------------------