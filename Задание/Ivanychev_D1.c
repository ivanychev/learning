 /**
    @file       Ivanychev_D1.c
    @mainpage
    @date       09-28-2013
    @author     Sergey Ivanychev <sergeyivanychev@gmail.com>, 376 group, DCAM MIPT
    @version 1.01
    @par         Changelog 1.01:
                - corrected #defines (codestyle, type of __LINE__, CHECK_FIELD turned to CHECK_FIELD_ (local define)
                - corrected doxygen support
                - corrected names of counters and variables


    @par        This is a problem from 2007 test, 1st variant, problem D
                Prints a table of b(N, K) values (0 <= N, K <= N), where b(N, K) - the quantity
                of binary words of N characters, if there are K ones and there are no two next ones
                User is expected to type the integer positive number\n# The program will calculate and print
                N + 1 strings.

    @par        This program contains #define _EJC and DEBUG
                _EJC is turned off by default, switching on makes program print addition information
                DEBUG, which has been defined, switches on ASSERTs
 **/


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


//#define _EJC

//#undef _EJC
#ifdef _EJC
    #define OUT
#else
    #define OUT if(0)
#endif

//#define DEBUG

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


/**
    word_amount     a recursive function which finds the amount of combinations of binary words, which satisfy the objective
    @param len      - the length of the binary word
    @param ones     - the quantity of ones in the binary word

    @par            Firstly, all of simple cases (len == 0, 1, 2) has been written using conditional operators.
                    Basically, all cases are possible to be represented as a combination of simple ones.
                    That's why we use recursion. The idea is that if there's a word (len > 2), then there are three basical variants
                    -the first char is one
                    -the second is one
                    -both of the first and the second characters are zeros
                    The value of such word_amount(len, ones) = words_amount(len - 2, ones - 1) + words_amount(len - 3, ones - 1) + words_amount(len - 2, ones).
                    The function is obvious to be lead to the combination of simple ones.

    @return         - the quantity of such words
**/

long words_amount(long len, long ones);

/**
    main        - prints the answer, configures the work of words_amount()
    @return     main : returns 0, if the argumen is correct, in other cases returns -1
**/

int main()
{
    OUT printf("# Hello, I'm the program, which solves the problem which's written below\n"
    "# I've been developed by Ivanychev Sergey, my source code is located in %s\n"
    "# I've been compiled and built in %s\n# I'm 1.0 version\n"
    "# My duty is to print a table of b(N, K) values (0 <= N, K <= N), where b(N, K) - the quantity\n"
    "# of binary words of N characters, if there are K ones and there are no two next ones"
    "\n\n# You are requested to type the integer positive number\n# The program will calculate and print"
    "N + 1 strings\n"
    "# The n-th string contain b(n, 0) .. (b(n, k) where b(n, k) > 0 and b(n, k + 1) = 0\n"
    "\n# Example:\nYou type: 4 and press ENTER\n\n# 1\n# 1 1\n# 1 2\n# 1 3 1\n# 1 4 3\n\n# Have a nice computing!\n\n", __FILE__, __DATE__);

    int n = 0;
    int ret = scanf("%d", &n);  //!< Checking, if the input was successful
    if (!(ret))
    {
        OUT printf("Bad argument, program terminated\n");
        return -1;
    }
    int nN = 0, nK = 0;           //!< Counters of N and K
    long n_words_out = 0;               //!< The output of words_amount()
    for (nK = 0; nK <= n; ++nK)
    {
        nN = 0;
        while (n_words_out = words_amount (nK, nN))
        {
            printf("%ld ", n_words_out);
            ++nN;
        }
        putchar('\n');
    }
    return 0;
}



long words_amount(long len, long ones)
{
    if (len == 0)
        if (ones == 0) return 1;
        else return 0;
    if (len == 1)
        if (ones <= 1) return 1;
        else return 0;
    if (len == 2)
        switch (ones)
        {
            case 0:
                return 1;
                break;
            case 1:
                return 2;
                break;
            default:
                return 0;
                break;
        };
    /*if (len == 3)
        switch (ones)
        {
            case 0:
                return 1;
                break;
            case 1:
                return 3;
                break;
            case 2:
                return 1;
                break;
            default:
                return 0;
                break;
        }   */
    if (ones == 0) return 1;
    long out = 0;
    out += words_amount(len - 2, ones - 1);
    out += words_amount(len - 3, ones - 1);
    out += words_amount(len - 2, ones);

    return out;
}

