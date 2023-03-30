/**
        @file				main.cpp
        @author				Sergey Ivanychev, group 376, DCAM MIPT
        @mainpage
        @version			1.1 Beta 2

        @par				Available commands (1.1 Beta 2) :
                                                - push {float number} or {ax}
- pushes number to stack
                                                - pop
- pops number and saves it to the argument pointer of that functions
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
                                                -- out rg {name of register: ax,
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


        @todo				CPU Begin.exe process doesn't finish
after stopping the program. It is still in memory. FIX OR ASK
        @todo				Enchance cpu_pop() to read pop ax, pop
out constructions
        @todo				Add cpu_swap(), cpu_dub()
        @todo				Extend push to make push bx, push cx,
push dx possible
**/

#include "cpu.h"

//--------------DRAWING CONSTANTS--------------------------------

const int DISPLAY_WIDTH = 1000;
const int DISPLAY_HEIGHT = 1000;
const double X1 = -60;
const double X2 = 60;
const double DX = (X2 - X1) / DISPLAY_WIDTH;

//----------------------------------------------------------------

/*
const double X1 = -1.5;
const double X2 = 1.5;
const double DX = (X2 - X1)/10000;
const int DISPLAY_WIDTH = 1200;
const int DISPLAY_HEIGHT = 900;
*/

/**
        main				rules io, initializes and deletes CPU
        @return				0;
**/

int main() {

  cpu *my_cpu = cpu_construct(CPU_STACK_SIZE);
  FILE *fi = fopen("code.txt", "r");
  FILE *fo = fopen("values.txt", "w");
  FILE *strerr = fopen("log.txt", "w");

  double y = 0;
  double x = X1;
  int ret = 0;
  double ymax = 0;
  double ymin = 0;

  cpu_mov_ax(my_cpu, x);

  calculator(fi, fo, strerr, my_cpu, &ymin, cpu_catch_error);

  ymax = ymin;

  double xmin = X1;
  double xmax = X1;

  fclose(fi);

  fprintf(fo, "----------------------------------------------------------------"
              "--------------\n");

  while (x <= X2) {
    FILE *fi = fopen("code.txt", "r");
    cpu_mov_ax(my_cpu, x);
    // fprintf(fo, "%lg ", x);
    ret = calculator(fi, fo, strerr, my_cpu, &y, cpu_catch_error);

    if (ymax < y) {
      ymax = y;
      xmax = x;
    }
    if (ymin > y) {
      ymin = y;
      xmin = x;
    }
    x += DX;
    fclose(fi);
  }

  fprintf(strerr, "xmax = %lg ymax = %lg xmin = %lg ymin = %lg\n\n", xmax, ymax,
          xmin, ymin);

  ret = plot("code.txt", "values.txt", "log.txt", my_cpu, X1, X2, DX, ymin,
             ymax, DISPLAY_WIDTH, DISPLAY_HEIGHT);

  fprintf(strerr, "\nEnd of log");
  fprintf(fo, "\nEnd of values table");
  cpu_destruct(my_cpu);
  fclose(fi);
  fclose(fo);
  fclose(strerr);

  return 0;
}
