/**
    /**
    @file           Ivanychev_A1.c
    @mainpage
    @date           09-29-2013
    @author         Sergey Ivanychev <sergeyivanychev@gmail.com>, 376 group, DCAM MIPT
    @version        1.01

    @par            Changelog V 1.01
                    - temporary variable instead sqrt(x) added

    @par            This is a problem from 2007 test, variant 1, problem A
                    It outputs prime numbers from input stream

    @par            This program contains #define _EJC and DEBUG
                    _EJC is turned off by default, switching on makes program print addition information
                    DEBUG, which has been defined, switches on ASSERTs
**/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

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
    is_prime        function guesses, whether the argument is prime or not
    @param          merging number
    @par            Cycle continues from i = 2 to sqrt(x) + DBL_EPSILON to avoid double mathematics mistakes

    @return         1, if the number is prime, otherwise 0
**/
int is_prime(long x);

/**
    main            drives input and output, uses is_prime
    @return         0 if arguments are correct, otherwise -1
**/
int main()
{
    OUT printf( "# Hello, I'm the program, which solves the problem which's written below\n"
                "# I've been developed by Ivanychev Sergey, my source code is located in %s\n"
                "# I've been compiled and built in %s\n# I'm 1.01 version\n"
                "# I analyse the input stream of numbers to find pride ones\n"
                "# You're supposed to write the number of input numbers and then write them\n"
                "# I'll print pride ones\n"
                "# Example:\n# 4\n# 3 9 11 3\n# I'll print:\n# 3 11 3\n# Enjoy!\n", __FILE__, __TIME__);


    int in = 0, n = 0;
    scanf("%ld", &n);
    while (n > 0)
    {
        if (!(scanf("%d", &in)))
        {
            OUT printf("\nBad argument, program terminated");
            return -1;
        }

        if (is_prime(in)) printf("%d ", in);
        n--;
    }
    return 0;
}

int is_prime(long x)
{
    if (x == 1) return 0;
    if (x == 2) return 1;

    long i = 0;
    double finish = sqrt(x)+DBL_EPSILON;
    for (i = 2; i <= finish ; ++i) if (!(x % i)) return 0;
    return 1;
}


