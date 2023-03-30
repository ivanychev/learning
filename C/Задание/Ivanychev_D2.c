/**
   @file Ivanychev_D2.c
   @mainpage
   @date 09-28-2013
   @author Sergey Ivanychev <sergeyivanychev@gmail.com>, 376 group, DCAM MIPT
   @version 1.01
   @par         Changelog 1.01:
                - corrected #defines (codestyle, type of __LINE__, CHECK_FIELD
turned to CHECK_FIELD_ (local define)
                - corrected doxygen support
                - fixed counters
                - better formatting


   @par         This is a problem from 2007 test, 3rd variant, problem D
                Finds the maximum white square on field of black and white
squares. # symbol represents BLACK, . symbol represents WHITE. If I find a
square, It'll print his right-bottom coordinates. If there are many of them,
It'll print the coordinates, which has minimum x. There are some coordinates
with the same x, and that x is minimum, It'll print the coordinate with Y
minimum.

   @par         This program contains #define _EJC and DEBUG
                _EJC is turned off by default, switching on makes program print
addition information DEBUG, which has been defined, switches on addition debug
printing and ASSERTs

**/

#include <stdio.h>
#include <stdlib.h>

#define FIELD_VALUE(x, y, size) (*(field + size * (x) + (y)))

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

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
   max_square - calculates the verge size of the biggest white square, whose
left-top square is x, y
   @param       x               - x coordinate
   @param       y               - y coordinate
   @param[OUT]  field           - the field of white and black squares
   @param       size_field      - the verge size of the field

   @par                 Calculates the values "across the angles"
                        If x, y square is black - its value = 0
                        x, y square is white - its value equals to the minimum
                        of values of right, lower and right-lower squares
increased by one That's why the calculation completes across the corners. If
size_field = L, it calculates values of [L - 1, L - 1] to [L - 1, 0] and from [L
- 2, L - 1] to [0, L - 1] and decreases L by one.
    @par                If the square is on the edge of the field, it's max
white suare equales the value of the square (1 - white, 0 - black)
    @return             max_square: the edge of the biggest white square, based
on that square


**/
int max_square(int x, int y, char *field, int size_field);

/**
   get_field            scans the field of black and white squares. Converts '#'
into 0, '.' into 1
   @param[out]          field - the field of white and black squares
   @param   size_field  the verge size of the field
   @return              1 if succesful read, 0 if unsuccessful (Argument fail)

**/

int get_field(char *field, int size_field);
/**
    create_maxes        Transfers the field of 1 and 0 into the field of values.
                        Each value represent the biggest white square, which's
based on that square.
    @param[out]         field - the field of white and black squares
    @param              size_field    - the verge size of the field
    @param[out]         x_max - X coordinate of lefmost-top square of biggest
white square
    @param[out]         y_max - Y coordinate of lefmost-top square of biggest
white square

    @param              Pay attention to CHECK_FIELD, which's been defined.
                        CHECK_FIELD is a check for maximum value, the leftmost
and the toppest square.
    @return             create_maxes: returns the biggest size of white square

**/

int create_maxes(char *field, int size_field, int *x_max, int *y_max);

/**
    main - prints the answer, configures the whole program and interacts with
othe functions
    @return 0 if the arguments are correct, otherwise -1
**/

int main() {
  OUT printf(
      "# Hello, I'm the program, which solves the problem which's written "
      "below\n"
      "# I've been developed by Ivanychev Sergey, my source code is located in "
      "%s\n"
      "# I've been compiled and built in %s\n# I'm 1.0 version\n"
      "# My duty is to find the maximum white square on field of black and "
      "white squares.\n"
      "#  # symbol represents BLACK, . symbol represents WHITE.\n"
      "# If I find a square, I'll print his right-bottom coordinates.\n"
      "# If there are many of them, I'll print the coordinates, which has "
      "minimum x.\n"
      "# There are some coordinates with the same x, and that x is minimum, "
      "I'll print\n"
      "# the coordinate with Y minimum."
      "\n# Type the size of the square edge and press ENTER, then sequentally "
      "type the colors\n"
      "# of the squares using #,. and ENTERs\n\n"
      "# Example:\n# 5\n# #..#.\n# .....\n# ##...\n# #....\n# #.###\n\n# I'll "
      "print:\n\n# 3\n# 4 3\n# Have a nice calculation!\n\n",
      __FILE__, __TIME__);

  int n = 0;
  scanf("%d", &n);
  getchar();
  char field[n][n]; // ={}
  int ret = get_field(&field[0][0], n);
  if (!(ret)) {
    OUT printf("Bad argument, program terminated");
    return -1;
  }

  int x_max = 0, y_max = 0;

  int max_square = create_maxes(&field[0][0], n, &x_max, &y_max);

  printf("%d\n%d %d", max_square, x_max + max_square - 1,
         y_max + max_square - 1);

  return 0;
}

int max_square(int x, int y, char *field, int size_field) {
  if (!(FIELD_VALUE(x, y, size_field)))
    return 0; // if the color is black - nothing to do here
  int below = 0, right = 0, right_below = 0;

  right = (x == size_field - 1)
              ? 0
              : FIELD_VALUE(x + 1, y,
                            size_field); // is the right square out of field?

  below = (y == size_field - 1)
              ? 0
              : FIELD_VALUE(x, y + 1,
                            size_field); // is the lower square out of field?

  right_below =
      ((x == size_field - 1) || (y == size_field - 1))
          ? 0
          : FIELD_VALUE(x + 1, y + 1,
                        size_field); // is right-lower square out of field?

  int out = MIN(MIN(right, below), right_below) +
            FIELD_VALUE(
                x, y, size_field); // maximum square size equals to the minimum
                                   // of maxes of right, lower and right_lower
  OUT_DEBUG printf("right = %d, below = %d, right-below = %d, max = %d\n",
                   right, below, right_below, out); // squares increased by one

  return out;
}

int get_field(char *field, int size_field) {
  ASSERT(field != NULL);
  int field_x = 0, field_y = 0; //!< Counters
  char c;
  for (field_y = 0; field_y < size_field; ++field_y) {
    for (field_x = 0; field_x < size_field; ++field_x) {
      c = getchar();
      ASSERT(field_x < size_field);
      ASSERT(field_x >= 0);
      ASSERT(field_y < size_field);
      ASSERT(field_y >= 0);
      switch (c) {
      case '#':
        *(field + size_field * field_x + field_y) = 0;
        break;
      case '.':
        *(field + size_field * field_x + field_y) = 1;
        break;
      default:
        return 0;
        break;
      }
    }
    getchar();
  }
  return 1;
}

#define CHECK_FIELD_                                                           \
  if (maximum < *(field + field_x * size_field + field_y)) {                   \
    maximum = *(field + field_x * size_field + field_y);                       \
    *x_max = field_x;                                                          \
    *y_max = field_y;                                                          \
  }                                                                            \
  if ((maximum == *(field + field_x * size_field + field_y)) &&                \
      (field_x < *x_max)) {                                                    \
    *x_max = field_x;                                                          \
    *y_max = field_y;                                                          \
  }                                                                            \
  if ((maximum == *(field + field_x * size_field + field_y)) &&                \
      (field_x == *x_max) && (field_y < *y_max)) {                             \
    *y_max = field_y;                                                          \
  }
int create_maxes(char *field, int size_field, int *x_max, int *y_max) {
  ASSERT(field);
  ASSERT(x_max);
  ASSERT(y_max);
  ASSERT(x_max != y_max);

  int field_x = 0, field_y = 0, maximum = 0;
  int debug_y = 0, debug_x = 0;
  OUT_DEBUG for (debug_y = 0; debug_y < size_field; ++debug_y) {
    for (debug_x = 0; debug_x < size_field; ++debug_x)
      OUT_DEBUG printf("%d ", *(field + debug_x * size_field + debug_y));
    OUT putchar('\n');
  }

  for (field_x = size_field - 1; field_x >= 0; --field_x) {
    for (field_y = field_x; field_y >= 0; --field_y) {
      ASSERT(field_x < size_field);
      ASSERT(field_x >= 0);
      ASSERT(field_y < size_field);
      ASSERT(field_y >= 0);
      *(field + field_x * size_field + field_y) =
          max_square(field_x, field_y, field, size_field);

      CHECK_FIELD_;

      // debugging print below

      OUT_DEBUG printf("x = %d, y = %d, max = %d\n\n", field_x, field_y,
                       *(field + field_x * size_field + field_y));

      OUT_DEBUG for (debug_y = 0; debug_y < size_field; ++debug_y) {
        for (debug_x = 0; debug_x < size_field; ++debug_x)
          OUT_DEBUG printf("%d ", *(field + debug_x * size_field + debug_y));
        OUT_DEBUG putchar('\n');
      }
    }
    for (field_y = field_x - 1; field_y >= 0; --field_y) {
      ASSERT(field_x < size_field);
      ASSERT(field_x >= 0);
      ASSERT(field_y < size_field);
      ASSERT(field_y >= 0);

      *(field + field_y * size_field + field_x) =
          max_square(field_y, field_x, field, size_field);

      CHECK_FIELD_;

      // debugging print below

      OUT_DEBUG printf("x = %d, y = %d, max = %d\n\n", field_x, field_y,
                       *(field + field_x * size_field + field_y));

      OUT_DEBUG for (debug_y = 0; debug_y < size_field; ++debug_y) {
        for (debug_x = 0; debug_x < size_field; ++debug_x)
          OUT_DEBUG printf("%d ", *(field + debug_x * size_field + debug_y));
        OUT_DEBUG putchar('\n');
      }
    }
  }

  OUT_DEBUG for (field_y = 0; field_y < size_field; ++field_y) {
    for (field_x = 0; field_x < size_field; ++field_x)
      OUT_DEBUG printf("%d ", *(field + field_x * size_field + field_y));
    OUT_DEBUG putchar('\n');
  }

  return maximum;
}
#undef CHECK_FIELD_
