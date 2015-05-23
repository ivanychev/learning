#include "stdio.h"
#include "stdlib.h"
#include "errno.h"
#include "limits.h"

#define ONEXIT
#define RETURN(val) do {ONEXIT return val;} while (0);
#define BASE 10

enum IV_ERRORCODES
{
        IV_INVALARGS            = -1,
        IV_STATFAIL             = -2,
        IV_OPENFAIL             = -3,
        IV_COPYALLOCFAIL        = -4,
        IV_BUFALLOCFAIL         = -5,
        IV_READFAIL             = -6,
        IV_COPYSIZEFAIL         = -7,
        IV_NONUMBER             = -8
};

int iv_getlong(long* save, const char* str)
{
        if (save == NULL || str == NULL)
                RETURN(IV_INVALARGS);

        int base = BASE;
        char* endptr = NULL;

        long val = strtol(str, &endptr, base);

        if     ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
               || (errno != 0 && val == 0)
               || (void*)endptr == (void*)str
               || *endptr != '\0') {
                RETURN(IV_NONUMBER);
        }

        *save = val;
        return 0; 
}


int main(int argc, char const *argv[])
{
        long sum = 0;
        long val = 0;
        int i = 0;
        int ret = 0;

        for (i = 1; i < argc; ++i) {
                ret = iv_getlong(&val, argv[i]);
                if (ret != 0)
                        continue;
                sum += val;
        }

        // fprintf(stdout, "%d\n", (int)sum);
        return (int)sum;
}
