//{=================================================================================
//! @file square_equation.c
//! @date 2013-09-26
//! @author Sergey Ivanychev <sergeyivanychev@gmail.com>, 376 group, DCAM MIPT
//! @version 1.03
//! @note V1.01:
//!    - added function squaresolve()
//!    - main() has been changed
//!    - added multiple equations support
//!    - calculates and returns the sum of the roots
//!
//! @note V.1.02:
//!  - added "square_eq" structure where factors and number of roots are
//!  contained //!
//!  - fixed squaresolve():
//!  -- there's no -0.0 anymore!
//!  - fixed main():
//!  -- the roots aren't stored in memory anymore
//!  - added check if number of equations is positive
//!  - removed the array of roots, structure square_eq is created
//! @par V.1.03
//!  - added preprocessor support
//!  -- from now, float numbers are compared using IS_ZERO, IS_ABOVE_ZERO,
//!  IS_BELOW_ZERO
//!  -- my ASSERT added, if #define DEBUG is commented out, ASSERT would be
//!  replaced with space
//!  -- added #define OUT, which cancels friendly output if #define _EJC (Judge
//!  System Support)
//!  -  doxygen comments added
//!
//! @note TODO: - Figure out how to use the dynamic memory
//}==============================================================================================
//----------------------------------------------------------------------------------------

#include <float.h>
#include <math.h>
#include <stdio.h>

#define IS_ZERO(x) (fabs(x) < DBL_EPSILON)
#define IS_ABOVE_ZERO(x) (x > DBL_EPSILON)
#define IS_BELOW_ZERO(x) (x < -DBL_EPSILON)

//--------------------------------------------------------------------------
// #define _EJC
//--------------------------------------------------------------------------
#ifdef _EJC
#define OUT if (0)
#else
#define OUT
#endif // _EJC
//--------------------------------------------------------------------------
#define DEBUG
//--------------------------------------------------------------------------
#ifdef DEBUG
#define ASSERT(cond)                                                           \
  if (!(cond)) {                                                               \
    printf("All gone bad: %s, file: %s, line: %d\n", #cond, __FILE__,          \
           __LINE__);                                                          \
    abort();                                                                   \
  }
#else
#define ASSERT(cond)
#endif // DEBUG

int squaresolve(double a, double b, double c, double *x1, double *x2);
//----------------------------------------------------------------------------------------
struct square_eq {
  double a;
  double b;
  double c;
  char num_rts;
};

/**
main - Requests the quantity of equations, scans for factors, prints answers and
sum of roots
    @param  a       x^2 factor
    @param  b       x^1 factor
    @param  c       x^0 factor
    @param  x1      first root
    @param  x2      second root
    @param  n       the quantity of input equations
    @param ret      variable, which contain the information about input
condition (whether it is successful)
    @param i        counter

    @note square_eq structure is created, contains factors and quantity of roots

    @param eqs      the array of struct square_eq, contains input equations and
their numbers of roots

    @return main: Solves multiple equations with every a,b,c. If it is not
possible - returns -1 (for example: n < 0) if successful, returns 0
**/

int main() {
  OUT printf("#Hi, bro! How many equations do you want me to solve?\n");

  int n = 0;
  int ret = scanf("%d", &n);
  ASSERT(ret == 1);
  if (n < 0) {
    OUT printf("#Bad number of equations. Program terminated");
    return -1;
  }
  double x1 = 0, x2 = 0;
  OUT printf("#%d time(s) type A B C and press ENTER\n", n);
  struct square_eq eqs[n];
  int i = 0;

  for (i = 0; i < n; ++i) {
    ret = scanf("%lg %lg %lg", &eqs[i].a, &eqs[i].b, &eqs[i].c);
    ASSERT(ret == 3);
  }
  double sum = 0;
  for (i = 0; i < n; ++i) {
    eqs[i].num_rts = squaresolve(eqs[i].a, eqs[i].b, eqs[i].c, &x1, &x2);

    switch (eqs[i].num_rts) {
    case 0:
      printf("%d: no roots\n", i + 1);
      break;

    case 1:
      sum += x1;
      OUT printf("%d: x = ", i + 1);
      printf("%lg\n", x1);
      break;

    case 2:
      sum += x1 + x2;
      OUT printf("%d: x1 = ", i + 1);
      printf("%lg ", x1);
      OUT printf("x2 = ");
      printf("%lg\n", x2);
      break;

    case 3:
      printf("%d: all reals are roots\n", i + 1);
      break;

    default:
      printf("ERROR: wrong quantity of roots\n");
      return 1;
      break;
    }
  }
  OUT printf("#sum of roots = ");
  printf("%lg", sum);
  OUT printf("\n#Have a nice day, bro!\n");
  return 0;
}

//----------------------------------------------------------------------------------------

//

/**

    squaresolve - solves ax*x+bx+c=0 equation with every a, b, c possible

    @param[out]     x1  first root
    @param[out]     x2  seconf root
    @param          a   a factor
    @param          b   b factor
    @param          c   c factor
    @param          d   discriminant, which turns at the square root of
discriminant of ax*x+bx+c=0

    @return         squaresolve: The number of roots: 0, 1 или 2.
                    If the number is infinite - returns 3.
                    The roots are stored in *x1 and *x2 if they exist

**/

int squaresolve(double a, double b, double c, double *x1, double *x2) {
  ASSERT(x1 != x2);
  ASSERT(x1 != NULL);
  ASSERT(x2 != NULL);
  if (!IS_ZERO(a)) {
    double d = b * b - 4 * a * c;
    if IS_BELOW_ZERO (d) {
      return 0;
    }
    if IS_ZERO (d) {
      *x1 = -b / (2 * a);
      return 1;
    }
    d = sqrt(d);
    *x1 = (-b + d) / (2 * a);
    *x2 = (-b - d) / (2 * a);
    if (!*x1)
      *x1 = 0;
    if (!*x2)
      *x2 = 0;
    return 2;
  } else {
    if IS_ZERO (b)
      if IS_ZERO (c) {
        return 3;
      } else {
        return 0;
      }
    else {
      *x1 = -c / b;
      if (!*x1)
        *x1 = 0;
      return 1;
    }
  }
}
