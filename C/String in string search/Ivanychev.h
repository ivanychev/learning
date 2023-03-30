#include <stdio.h>
#include <stdlib.h>

//\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/

#define _EJC

#ifdef _EJC
#define OUT
#else
#define OUT if (0)
#endif

#define VERIFY(cond)                                                           \
  if (!(cond)) {                                                               \
    printf("Program %s died in battle on line %d with the mistake of (%s)",    \
           __FILE__, __LINE__, #cond);                                         \
    abort();                                                                   \
  }

//\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/

#define DEBUG 0

#if (DEBUG == 1)
#define DEBUG_OUT
#define ASSERT(cond)

#else
#define DEBUG_OUT if (0)
#define ASSERT(cond) VERIFY(cond)
#endif

//\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/

#define ARR_ASSERT(i, left, right)                                             \
  if (!(((left) <= (i)) && ((i) <= (right)))) {                                \
    printf("Program %s crashed, Array index is out of range, Line %d",         \
           __FILE__, __LINE__);                                                \
    abort();                                                                   \
  }

//\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/

#define POLITE_MOD 1

#if (POLITE_MOD == 1)
#define please ;
#endif

//\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/

int get_str(char *string, const int max);
char *is_there_string(char *searched, char *string);
