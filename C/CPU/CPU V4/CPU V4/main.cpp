/**
        @file				main.cpp
        @author				Sergey Ivanychev, group 376, DCAM MIPT
        @mainpage
        @version			1.3

        @par				Available commands (1.2 Beta 1) :
                                                - push {float number} or {ax,
bx, cx, dx}	- pushes number to stack
                                                - pop  {out} - to the pointer or
{ax, bx, cx, dx}
                                                - add
                                                - sub
                                                - mul
                                                - div
                                                - sqrt
                                                - pow
                                                - sin
                                                - cos
                                                - tan
                                                - out:
                                                -- out {name of register: ax,
bx, cx, dx}
                                                -- out st    -  from stack
                                                -- out ch {number of ascii
character}

                                                - mov {to register} {from:
register or value}
                                                - swap
                                                - dub
                                                - jmp {mark}
                                                - jbe
                                                - jb
                                                - jae
                                                - ja
                                                - je
                                                - jne
                                                - func {mark}
                                                - call {func}
                                                - ret

        @par				Chengelog V1.1 Beta 1

                                                This version has got many new
great features.

                                                -- Now the commands are being
read from the file code.txt.
                                                -- New processor functions added
                                                        --	cpu_enter,
cpu_cpace, cpu_tab for the cute output
                                                        --	cpu_mov_ax which
saves the number to processor register
                                                -- All the output is located in
values.txt
                                                -- All mistake messages are
located in log.txt
                                                --	If some mistakes happend
during the instructions execution, calculator terminates, but the whole program
doesn't. All mistakes messages and dump information you can find in log.txt

                                                Again,	code	- your commands
                                                                values	- output
                                                                log - mistakes


        @par				Changelog V1.1 Beta 2

                                                This version has a lot of new
features and updates
                                                -- TXLib fixes: dealing with
broken calculator return (like 1/0 or sqrt(-4)). Now that points are being
ignored and the plot is ok
                                                -- cpu_pop has been changed: now
it doesn't print anything to any file stream.
                                                -- cpu_out created: it can print
in any file stream the value of stack, any register or character of input ascii
number
                                                -- Error catcher updated: in
calculator() function now the error function pointer is called, not the
function. It makes possible to replace the standard cpu_catch_error() function
easily
                                                -- New plot() function: removed
the code of drawing from main(), created new function

        @par				Changelog V1.1 Beta 3 RC

                                                -- CPU_CONSTRUCT and
CPU_DESTRUCT fixed
                                                -- changes in CPU_OUT(). Now
command sounds like "out ax" not "out rg ax"
                                                -- removed plot and "TXLib"
support because its features have been shown in Beta 2. Compilation speed++
                                                -- CPU_MOV_AX() turned to
CPU_MOV, now it deals with all registers (mov ax bx == ax = bx, mov ax 15 == ax
= 15)
                                                -- CPU_POP enchanced: now you
can pop from stack (pop st) and pop from any register (pop ax, pop bx)
                                                -- CPU_PUSH enchanced: now you
can push your own value to the stack (push {number}) or push the value of any
register (push ax)
                                                -- CPU_DUB() and CPU_SWAP()
added support
                                                -- Code style changes - many
local defines used
                                                -- Small fixes

        @par				Changelog V 1.2 Beta 1
                                                -- Now there're asm_main.cpp and
asm.cpp which are scanning code.txt and build the binary file with instructions
codes and arguments
                                                --- It's been added from other
program called asm.exe and could be easily divided into parts
                                                -- Now there're functions and
marks support (added instructions call, ret and func)
                                                -- There're lots of new
instructions added like jmp, jbe, jb, jae, ja, je, jne
                                                -- Added function cpu_core that
configures the work of the whole processor
                                                -- CPU has been enchanced
                                                --- Added functions calling
stack, which allows ret and call to work
                                                -- Lots of other fixes and
improvements

        @par				Changelog V 1.2 Beta 2
                                                -- Function CPU_IN() and
instruction IN added, now you're allowed to print your own values
                                                -- STACK_OK() fixed: now, if
there's error, it prints the dump in stdout
                                                -- Some documentation fixed
                                                -- Some fixes across the whole
code

                                                Changelog V 1.2 RC
                                                -Security update
                                                -- Added fscanf_s() and
fopen_s() support
                                                -- Added a lot of extra
verifications

                                                Changelog V 1.2 Beta 3
                                                -- Assembler has been fully
rewritten.
                                                --- Added asm_functions library
with different token-analysing functions and error catcher
                                                --- Reduced size of assembler(),
now it's (hopefully) stunning and clear

                                                Changelog V 1.2
                                                -- Changed writing and reading
binaries, added support for fread() and fwrite()

                                                Changelog V 1.3
                                                -- Added variables support
                                                --- Assembler now has it's own
namespace
                                                --- New instruction "def". Legal
expressions are like "def x", "def my_variable"
                                                --- Changed "push" and "pop"
instructions to support varibles. If you want to manipulate with variable
("value" for example), use "push var value", "pop var value". Don't forget to
declare them!
                                                --- CPU structure now has it's
own RAM, to contain variables' values
                                                --- "pop" machine code changed.
Now there're three numbers to support variables
                                                -- Added console argumented
input file support



**/

#include "command_codes.h"
#include "cpu.h"

/**
        main				rules io, calls asm, initializes and
deletes CPU
        @return				0;
**/
#define RELOAD_FILE_(file, stream, param)                                      \
  fclose(stream);                                                              \
  stream = fopen(file, param);

#define CHECK_PTR_HEALTH(ptr, msg, ret)                                        \
  if (ptr == NULL) {                                                           \
    fprintf_s(strerr, msg);                                                    \
    fclose(strerr);                                                            \
    return ret;                                                                \
  }

#undef VERIFY

#define VERIFY(cond, msg, ret, addition_close)                                 \
  if (!(cond)) {                                                               \
    fprintf_s(strerr, msg);                                                    \
    fclose(strerr);                                                            \
    addition_close;                                                            \
    return ret;                                                                \
  }
int main(int argc, char *argv[]) {
  FILE *strerr = NULL;
  fopen_s(&strerr, "exe_log.txt", "w");
  assert(strerr != NULL);
  cpu *my_cpu = cpu_construct(CPU_STACK_SIZE);

  CHECK_PTR_HEALTH(my_cpu, "\nStack hasn't been constructed\n", 0);
  int ret = asm_main("code.txt"); // argv[1]

  if (ret != ASM_OK) {
    fprintf(strerr, "\nAssemble failed\n");
    fclose(strerr);
    return 0;
  }
  FILE *strbin = NULL;
  fopen_s(&strbin, "executable.ivz", "rb");
  CHECK_PTR_HEALTH(strbin, "\nBinary file openning error\n", 0);

  FILE *strout = NULL;
  fopen_s(&strout, "output.txt", "w");
  CHECK_PTR_HEALTH(strout, "\nBinary file openning error\n", 0);

  ret = cpu_load(my_cpu, strbin);
  if (ret != CPU_OK) {
    fprintf(strerr, "\nCPU memory hasn't been loaded\n");
    goto break_p;
  }

  double value = 0;
  ret = cpu_core(strout, strerr, my_cpu, &value, cpu_catch_error);

  if (ret == EXE_BAD)
    fprintf(strout, "\n There were execution errors\n");

break_p:;
  cpu_destruct(my_cpu);
  fclose(strbin);
  fclose(strout);
  fclose(strerr);

  // system("PAUSE");

  return 0;
}

#undef RELOAD_FILE_
