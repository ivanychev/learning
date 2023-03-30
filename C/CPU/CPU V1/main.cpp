/**
        @file				main.cpp
        @author				Sergey Ivanychev, group 376, DCAM MIPT
        @mainpage
        @version			1.0

        @par				This is the origin of the processor unit
                                                Program understands basic
commands and proceeds operations with numbers. The main principle of program is
Reverse Polish notation.

**/

#include "cpu.h"

/**
        main				rules io, initializes and deletes CPU
        @return				0;
**/

int main() {
  printf("I'm the origin of the processor unit\n"
         "Developed by Ivanychev Sergey\n"
         "I'm 1.0 version\n"
         "I've been compiled in %s %s\n\n",
         __DATE__, __TIME__);
  cpu *my_cpu = cpu_construct(CPU_STACK_SIZE);
  int ret = calculator(stdin, stdout, my_cpu);
  cpu_destruct(my_cpu);
  return 0;
}
