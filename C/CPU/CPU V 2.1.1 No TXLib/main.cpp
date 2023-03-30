/**
        @file				main.cpp
        @author				Sergey Ivanychev, group 376, DCAM MIPT
        @mainpage
        @version			1.1 Beta 2

        @par				Available commands (1.1 Beta 2) :
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

        @todo				CPU Begin.exe process doesn't finish
after stopping the program. It is still in memory. FIX OR ASK
**/

#include "cpu.h"

const double X1 = -60;
const double X2 = 60;
const double DX = (X2 - X1) / 100;

/**
        main				rules io, initializes and deletes CPU
        @return				0;
**/
#define RELOAD_FILE_(file, stream, param)                                      \
  fclose(stream);                                                              \
  stream = fopen(file, param);

int main() {

  cpu *my_cpu = cpu_construct(CPU_STACK_SIZE);
  FILE *fi = fopen("code.txt", "r");
  FILE *fo = fopen("values.txt", "w");
  FILE *strerr = fopen("log.txt", "w");

  int ret = 0;
  double y = 0;
  double x = X1;

  while (x <= X2) {
    RELOAD_FILE_("code.txt", fi, "r");
    cpu_mov(my_cpu, STR_ax, STR_value, x);
    ret = calculator(fi, fo, strerr, my_cpu, &y, cpu_catch_error);
    if (ret == CALC_BAD) {
      fprintf(fo, "\n\n THERE WERE ERRORS\n");
      break;
    }
    x += DX;
  }
  fprintf(strerr, "\nEnd of log");
  fprintf(fo, "\nEnd of values table");
  cpu_destruct(my_cpu);
  fclose(fi);
  fclose(fo);
  fclose(strerr);

  return 0;
}
