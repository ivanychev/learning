/**
        @file				main.cpp
        @author				Sergey Ivanychev, group 376, DCAM MIPT
        @mainpage
        @version			1.1 Beta 1

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

**/

#include "cpu.h"

/**
        main				rules io, initializes and deletes CPU
        @return				0;
**/

int main() {
  /*
  fprintf(stdout, "I'm the origin of the processor unit\n"
                                  "Developed by Ivanychev Sergey\n"
                                  "I'm 1.0 version\n"
                                  "I've been compiled in %s %s\n\n", __DATE__,
  __TIME__); fprintf(stdout,	"# This is prototype of processor unit which
  calculates expressions\n"
                                  "# written in inverted Polish way (or
  something like that)\n"
                                  "# There are commands available:\n"
                                  "\n push {number}\n"
                                  " pop\n"
                                  " add\n"
                                  " sub\n"
                                  " mul\n"
                                  " div\n"
                                  " sin\n"
                                  " cos\n"
                                  " tan\n"
                                  " sqrt\n"
                                  " pow\n"
                                  " end\n"
                                  "\nPLEASE, USE [.] TO DIVIDE FLOAT PART\n"
                                  "Here you go\n");
  */

  cpu *my_cpu = cpu_construct(CPU_STACK_SIZE);
  FILE *fo = fopen("values.txt", "w");
  FILE *strerr = fopen("log.txt", "w");
  double x = -5;
  double y = 0;
  int ret = 0;
  while (x <= 5) {
    FILE *fi = fopen("code.txt", "r");
    cpu_mov_ax(my_cpu, x);
    ret = calculator(fi, fo, strerr, my_cpu, &y);
    if (ret != CALC_OK) {
      fprintf(strerr, "\nMISTAKE\n");
    }
    // fprintf(fo, "x = %lg, y = %lg\n", x, y);
    x += 1;
    fclose(fi);
  }
  fprintf(strerr, "\nEnd of log");
  fprintf(fo, "\nEnd of values table");
  cpu_destruct(my_cpu);
  fclose(fo);
  fclose(strerr);

  return 0;
}
