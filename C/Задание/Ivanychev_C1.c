/**
   @file        Ivanychev_C1.c
   @mainpage
   @date        09-28-2013
   @author      Sergey Ivanychev <sergeyivanychev@gmail.com>, 376 group, DCAM
MIPT
   @version 1.01
   @par         Changelog 1.01:
                - corrected #defines (codestyle, type of __LINE__, CHECK_FIELD
turned to CHECK_FIELD_ (local define)
                - corrected doxygen support


   @par         This is a problem from 2007 test, 1st variant, problem C
                Finds out is it possible to weigh a mass using combination of
                single weights equals to 4^n, n - natural

    @par        This program contains #define _EJC and DEBUG
                _EJC is turned off by default, switching on makes program print
addition information DEBUG, which has been defined, switches on addition ASSERTs
**/

#include <stdio.h>
#include <stdlib.h>

#define _EJC

#ifdef _EJC
#define OUT
#else
#define OUT if (0)
#endif

// #define DEBUG

#ifdef DEBUG
#define ASSERT(cond)                                                           \
  if (!(cond)) {                                                               \
    printf("All gone to hell, file = %s, line = %d, expression = %s",          \
           __FILE__, __LINE__, #cond);                                         \
    abort();                                                                   \
  }
#define OUT_DEBUG

#else
#define ASSERT(cond)
#define OUT_DEBUG if (0)
#endif

/**
    does_weigh4     recursive function which calculates, whether it possible to
weigh a mass using combination of single weights equals to 4^n, n - natural.
    @par            Let doew_weigh4(x) be f(x). We know, that if x > 4, then
                    - f(4*n), f(4*n + 1), 4(4*n - 1) = f(n)
                    We know some basics f(1) = f(3) = 1 and f(0) = f(2) = 0
                    To sum up, we use recursion to reduse the size of argument.
    @param  mass    Input mass
    @return         1 - possible, 2 - unpossible
**/
int does_weigh4(long mass);

/**
    main        function which rules the input and output
    @return     0, otherwise returns -1
**/
int main() {
  OUT printf(
      "# Hello, I'm the program, which solves the problem which's written "
      "below\n"
      "# I've been developed by Ivanychev Sergey, my source code is located in "
      "%s\n"
      "# I've been compiled and built in %s\n# I'm 1.0 version\n"
      "# I'm figuring out whether we can weigh the mass using single weights\n"
      "# equal to 4^n, where n - is positive integer"
      "# You're supposed to type the mass. If it's possible to be weighed, "
      "I'll write \"YES\"\n"
      "# I'll write NO in another case."
      "# Examples: 59 -> YES, 58 -> NO"
      "# Have a good weighing!\n",
      __FILE__, __TIME__);
  long n;

  int ret = scanf("%ld", &n);
  if ((!(ret)) || (n < 0)) {
    OUT printf("Invalid argument, program terminated\n");
    return -1;
  }
  long does_weigh = does_weigh4(n);
  printf("%s", (does_weigh == 1) ? "YES" : "NO");
  return 0;
}

int does_weigh4(long mass) {
  if (mass >= 4)
    switch (mass % 4) {
    case 0:
      return does_weigh4(mass / 4);
      break;
    case 1:
      return does_weigh4((mass - 1) / 4);
    case 2:
      return 0;
      break;
    case 3:
      return does_weigh4((mass + 1) / 4);
      break;
    default:
      break;
    }
  return ((mass == 1) || (mass == 3)) ? 1 : 0;
}
