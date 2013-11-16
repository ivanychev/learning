/**
    @file           Ivanychev_B1.c
    @mainpage
    @date           09-29-2013
    @author         Sergey Ivanychev <sergeyivanychev@gmail.com>, 376 group, DCAM MIPT
    @version        1.01
    @par            Changelog: V 1.01
                    - Tiny changes in codestyle
                    - is_square_divisor() redescribed

    @par            This is a problem from 2007 test, variant 1, problem b
                    Merges, whether there's a dividor, which's equals to n^2, where n > 1, n - natural

    @par            This program contains #define _EJC and DEBUG
                    _EJC is turned off by default, switching on makes program print addition information
                    DEBUG, which has been defined, switches on ASSERTs

**/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define IS_DIVISOR(div, n) ((n) % (div)) == 0
#define IS_LESSER(a, b) ((a) < (b) + DBL_EPSILON)

//#define _EJC

#ifdef _EJC
    #define OUT
#else
    #define OUT if(0)
#endif

#define DEBUG

#ifdef DEBUG
#define ASSERT(cond)                                                                                        \
    if (!(cond)) {                                                                                          \
        printf("All gone to hell, file = %s, line = %d, expression = %s", __FILE__, __LINE__, #cond);       \
        abort();                                                                                            \
        }
//------------------------------------------------------
#define OUT_DEBUG
//------------------------------------------------------
#else
#define ASSERT(cond)
#define OUT_DEBUG if(0)
#endif

#define VERIFY(cond)                                                                                        \
        if (!(cond)) {                                                                                      \
        printf("All gone to hell, file = %s, line = %d, expression = %s", __FILE__, __LINE__, #cond);       \
        abort();                                                                                            \
        }
/**
    is_square_divisor       guesses if there's an argument divisor which's n^2, where n - integer, n > 1
    @param n                the number, which's being analysed

    @par                    This function searches for a divisor from 2 to sqrt(argument). If found, but the square of it isn't
                            a divisor, function divides argument by that divisor and calculates the sqrt of it again. It decreases
                            the quantity of itterations and doesn't affect on result.

    @return                 D, if n % (D * D) == 0 and D - int, D > 1, otherwise 0
**/
int is_square_divisor(long n);

/**
    main                    functions scans input for the argument and prints whether it possible to divide by square or no
    @return                 0 if argument's correct, otherwise 1
**/
int main()
{
    OUT printf( "# Hello, I'm the program, which solves the problem which's written below\n"
                "# I've been developed by Ivanychev Sergey, my source code is located in %s\n"
                "# I've been compiled and built in %s\n# I'm 1.01 version\n"
                "# My duty's to guess, is there any divisors of the argument which is a squre of a natural number\n"
                "# If there is, I'll print YES, otherwise I'll print NO\n"
                "# Have a good guessing!\n", __FILE__, __TIME__);
    long n = 0;
    int ret = scanf("%ld", &n);
    if (!(ret))
    {
        printf("Bad argument, program terminated");
        return 1;
    }
    long guess = is_square_divisor(n);
    printf("%s", guess ? "YES\n" : "NO\n");
    if (guess) OUT printf ("%ld / (%ld * %ld) = %ld", n, guess, guess, n / (guess * guess));

    return 0;
}

int is_square_divisor(long n)
{
    long div = 2;
    double sqn = sqrt(n);
    while (IS_LESSER(div, sqn))
        if (IS_DIVISOR(div, n))
            if (IS_DIVISOR(div * div, n))
            {
                return div;
            }
            else
            {
                n /= div;
                div++;
                sqn = sqrt(n);
            }
        else div++;
    return 0;
}

