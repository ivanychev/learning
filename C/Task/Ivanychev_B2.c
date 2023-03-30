/**
    @file           Ivanychev_B2.c
    @mainpage
    @date           09-29-2013
    @author         Sergey Ivanychev <sergeyivanychev@gmail.com>, 376 group,
DCAM MIPT
    @version        1.01

    @par            Changelog V 1.01
                    - Some names and codestyle has been corrected
                    - Used tolower() function
                    - Deleted ungetc(), turned filter() to char function


    @par            This is a proble from 2007 test, variant 4, problem C
                    Filters the input text according to these rules
                    - avoid special signs
                    - replase the sequence of ' ', ',', '\t' with SPACE
                    - replaces capital letters with lower
                    - replaces digits with #
**/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define VERIFY(cond)                                                           \
  if (!(cond)) {                                                               \
    printf("All gone to hell, file = %s, line = %d, expression = %s",          \
           __FILE__, __LINE__, #cond);                                         \
    abort();                                                                   \
  }
// #define _EJC

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
    filter      function which actually filters the input
    @param  c   input char, filter actions are configured whith that char
    @return     character, if it hasn't been analysed, otherwise 0
**/
char filter(char c);

/**
    main        function which gets character and verifys if it is EOF.
                uses filter() to process the input
    return      0, there's always input stream, even one character
**/
int main() {
  OUT printf("# Hello, I'm the program, which solves the problem which's "
             "written below\n"
             "# I've been developed by Ivanychev Sergey, my source code is "
             "located in %s\n"
             "# I've been compiled and built in %s\n# I'm 1.01 version\n"
             "# I filter your text according to 4 rules\n"
             "# - avoid special signs\n"
             "# - replase the sequence of ' ', ',', '\t' with SPACE\n"
             "# - replaces capital letters with lower\n"
             "# - replaces digits with #\n"
             "# Don\'t forget to press ENTER and Ctrl-Z, when finished!\n"
             "# Have fun!\n",
             __FILE__, __TIME__);
  char c = getchar();
  while (c != EOF) {
    c = filter(c);
    if (!(c))
      c = getchar();
  }
  return 0;
}

#define IS_SPECIAL_(c) (((c) == ',') || ((c) == ' ') || ((c) == '\t'))
char filter(char c) {
  if (isupper(c)) {
    putchar(tolower(c));
    return 0;
  }
  if (ispunct(c) && (!(IS_SPECIAL_(c))))
    return 0;
  if (IS_SPECIAL_(c)) {
    putchar(' ');
    while (IS_SPECIAL_(c))
      c = getchar();
    return c;
  }
  if (isdigit(c)) {
    putchar('#');
    return 0;
  }
  putchar(c);
  return 0;
}
#undef IS_SPECIAL_
