/**
    @file           Ivanychev_A2.c
    @mainpage
    @date           09-28-2013
    @author         Sergey Ivanychev <sergeyivanychev@gmail.com>, 376 group, DCAM MIPT
    @version        1.01

    @par            Changelog V 1.01
                    - changed some names
                    - corrected some codestyle things


    @par            This problem's from 2007 test, variant 5, problem A

    @par            This program contains #define _EJC and DEBUG
                    _EJC is turned off by default, switching on makes program print addition information
                    DEBUG, which has been defined, switches on ASSERTs

**/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>


#define IS_ZERO(x) (fabs(x) < DBL_EPSILON)
#define IS_BELOW_ACCURACY(x) ((x) < prec_summand)

//#define _EJC
//#undef _EJC
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

    #define OUT_DEBUG

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
    sum_of_series           function which actually calculates the sum of seies
    @par                    The sum is obvious to be very slow-calculating, if we didn't use some verifications
                            There's a #define called IS_BELOW_ACCURACY. If the summand is hardly below precision, the cycle will break.
    @param      n           Expected quantity of itterations
    @param      x           Component of series  S(n,x) = sum (0, n, x^k / k!)
    @param      precision   The precision of calculation
    @return                 Value of calculation

**/
double sum_of_series(long n, double x, const int precision);

/**
    main                    function which rules input and output and sets the precision
    @return                 0 if the input is correct, otherwise -1
**/

#define CORRECT_INPUT_ ((ret != 2)|| (!((1 <= n)&&(n <= 100000))) || (!((0 <= x)&&(x <= 10))))
int main()
{
    OUT printf( "# Hello, I'm the program, which solves the problem which's written below\n"
                "# I've been developed by Ivanychev Sergey, my source code is located in %s\n"
                "# I've been compiled and built in %s\n# I'm 1.01 version\n"
                "# I'm calculating the sum of exponental series\n"
                "# You're expected to write integer(N, N > 0, N <= 100000) number and real number (X, X > 0, X <= 10)\n"
                "# I'll calculate S(N,X) = sum (K from 0 to N, X^K / K!) with the precision of 6 by default\n"
                "# _ELC #define is turned on and you can see me, you're expected to write your own precison\n"
                "# Example: 100000 0.346, I'll write 1.413403\n"
                "# Have a good calculation!\n\n", __FILE__, __TIME__);



    long n = 0;
    double x = 0;
    const int PRECISION_DEFAULT = 6;
    int precision = PRECISION_DEFAULT;
    int ret = 0;

    OUT {
            printf("# Would you like to set your own precision (6 by default) (y/n)?\n");
            char prec_cond = getchar();
            if (prec_cond == 'y')
            {
                printf("# Type it here\n");
                ret = scanf("%d", &precision);
                if ((ret != 1)||(precision < 0))
                    {
                        printf("Bad argument, program terminated");
                        return 1;
                    }
                printf("# OK, here we go!\n");
            }
            else printf("# OK, Here we go!\n");
        }
    ret = scanf("%ld %lg", &n, &x);

    if (CORRECT_INPUT_)
    {
        OUT printf("Bad argument, program terminated");
        return 1;
    }
    printf("%.*lf",precision,  sum_of_series(n, x, precision));
    return 0;
}

double sum_of_series(long n, double x, const int PRECISION)
{
    double summand = 0, sum = 0;
    double prec_summand = pow(10, - PRECISION - 3);
    long i = 0;
    for (i = 0; i <= n; ++i)
    {
        summand = pow(x, i);
        if (!(IS_ZERO(i)))
            for (int j = 1; j <= i; ++j) summand /= j;
        if (IS_BELOW_ACCURACY(summand)) break;
        sum += summand;
    }
    return sum;
}

