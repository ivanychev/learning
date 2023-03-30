/**
    @file           Ivanychev_C2.c
    @mainpage
    @date           09-28-2013
    @author         Sergey Ivanychev <sergeyivanychev@gmail.com>, 376 group,
DCAM MIPT
    @version 1.01
    @par         Changelog 1.01:
                - corrected #defines (codestyle, type of __LINE__, CHECK_FIELD
turned to CHECK_FIELD_ (local define)
                - corrected doxygen support
                - deleted IS_LETTER, replaced with isalpha()
                - added #define LENGTH
                - added #define VERIFY, the same as ASSERT but exist in release
                - small changes of code

    @par            This is a problem from 2007 test, variant 4, problem C
                    Rewrites the input text with inverting of all the words.

    @par            This program contains #define _EJC and DEBUG
                    _EJC is turned off by default, switching on makes program
print addition information DEBUG, which has been defined, switches on ASSERTs


**/

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define LENGTH(x) (sizeof(x) / sizeof(x[0]))

// #define _EJC

#ifdef _EJC
#define OUT
#else
#define OUT if (0)
#endif

#define DEBUG

#ifdef DEBUG
#define ASSERT(cond)                                                           \
  if (!(cond)) {                                                               \
    printf("All gone to hell, file = %s, line = %d, expression = %s",          \
           __FILE__, __LINE__, #cond);                                         \
    abort();                                                                   \
  }
//------------------------------------------------------
#define OUT_DEBUG
//------------------------------------------------------
#else
#define ASSERT(cond)
#define OUT_DEBUG if (0)
#endif

#define VERIFY(cond)                                                           \
  if (!(cond)) {                                                               \
    printf("All gone to hell, file = %s, line = %d, expression = %s",          \
           __FILE__, __LINE__, #cond);                                         \
    abort();                                                                   \
  }
/**
    swap_chars      swaps two chars.
    @par            Checking of pointers is working. If x = y, there's nothing
to swap. If (x == NULL) or (y == NULL) - everything's bad
    @param[out] x   first char
    @param[out] y   second char
    @return         nothing, it's void function
**/
void swap_chars(char *x, char *y);

/**
    invert_word         inverts a piece of char array
    @param[OUT] word    the char array
    @param      from    the beginging of inverting piece
    @param      to      the ending of inverting piece

    @par                uses swap_chars() to swap chars.
    @return             nothing, it's void function
**/
void invert_word(char *word, int from, int to, int length);

/**
    get_word:               scans the input for the word, saves it into char
array, counts its length
    @param[OUT] word        the array of chars, where the word would contain
    @param      len         the length of "word" array


    @return                 The size of scanned word
**/

int get_word(char *word, int len);

/**
    print_word              function that prints the piece of char array
    @param[OUT] word        the array of chars
    @param      start       the beginning of piece that being printed
    @param      finish      the ending of piece that being printed

    @return                 1 if the piece has been printed. If ASSERT is
switched, the program wold be terminated
**/
int print_word(char *word, int start, int finish);

/**
    main -          functions, which filters input into output recognizing the
words. It uses other functions to invert them and to print.
    @return         0, it's hard to cheat her
**/

int main() {
  OUT printf("# Hello, I'm the program, which solves the problem which's "
             "written below\n"
             "# I've been developed by Ivanychev Sergey, my source code is "
             "located in %s\n"
             "# I've been compiled and built in %s\n# I'm 1.0 version\n"
             "# I'm filtering and printing your input in the way of inverting "
             "all of your words"
             "# For example, if you write \"Tear down the wall!\" it'll print "
             "\"raeT nwod eht llaw!\"\n"
             "# Don't forget to type the character of the end of the file "
             "after the last ENTER! It's Ctrl-Z on Windows machines\n"
             "# Have fun!\n",
             __FILE__, __TIME__);

  char c = 0;
  char word[100] = {0};
  int success_read = 0, success_write = 0;
  while ((c = getchar()) != EOF) {
    if (isalpha(c)) {
      ungetc(c, stdin);
      success_read = get_word(word, LENGTH(word)); //!< the length of the word!
      VERIFY(success_read);
      invert_word(word, 0, success_read - 1, success_read);
      success_write = print_word(word, 0, success_read - 1);
      VERIFY(success_write);
      continue;
    }
    putchar(c);
  }
  return 0;
}

void swap_chars(char *x, char *y) {
  ASSERT(x);
  ASSERT(y);
  if (x != y) {
    char temp = *x;
    *x = *y;
    *y = temp;
  }
}

void invert_word(char *word, int from, int to, int siz) {
  ASSERT(word);
  ASSERT(0 <= from);
  ASSERT(from <= to);
  ASSERT(to < siz);

  int i = from;
  int length = to - from;
  for (i = 0; i <= length / 2; ++i)
    swap_chars(word + i, word + (length - i));
}

int get_word(char *word, int len) {
  ASSERT(word);
  char c = 0;
  int len_word = 0;
  c = getchar();
  if (!(isalpha(c))) {
    ungetc(c, stdin);
    return 0;
  }

  while (isalpha(c)) {
    ASSERT(len_word < len);
    word[len_word++] = c;
    c = getchar();
  }
  ungetc(c, stdin);
  return len_word;
}

int print_word(char *word, int start, int finish) {
  ASSERT(word);
  ASSERT(finish >= start);
  int i = 0;

  for (i = start; i <= finish; ++i)
    putchar(word[i]);
  return 1;
}
