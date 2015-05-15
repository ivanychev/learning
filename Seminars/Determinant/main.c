#include "ivmatrix.h"
#include "iv_standard.h"

int proceed_arguments(int argc, char const* argv[], char* name, long* nthreads);

void print_diff(struct timeval begin, struct timeval end, char*);



int main(int argc, char const *argv[]) 
{
        struct timeval begin;
        struct timeval end;


        char filename[MAX_FILENAME + 1] = {};
        long nthreads = 0;
        int cond = proceed_arguments(argc, argv, filename, &nthreads);

#undef  F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE return -1;

        CHECK(cond == 0, "Failed to get arguments");
        matrix current = {
                .size = 0,
                .data = NULL
        };
        cond = get_matrix(filename, &current);

        gettimeofday(&begin, NULL);

#undef  F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE matrix_kill(&current); return -1;

        CHECK(cond != -1, "Failed to read matrix from file\n");
        double determinant = 0;
        cond = get_matrix_determinant(&current, nthreads, &determinant);
        CHECK(cond == 0, "Failed to calculate matrix determinant");
        printf("Determinant is %lg\n", determinant);

        
        matrix_kill(&current);
        gettimeofday(&end, NULL);

        print_diff(begin, end, "Program execution time: ");
        return 0;
}

#undef  F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE return -1;



int proceed_arguments(int argc, char const* argv[], char* name, long* nthreads)
{
        CHECK(argc == 3, "Invalid number of arguments. Need name of a file AND number of threads\n");
        
        const char* filename    = argv[1];

        *nthreads = 0;
        int cond = iv_getlong(nthreads, argv[2]);

        CHECK(cond == 0, "Failed to get number from second argument");
        CHECK(*nthreads > 0 
                && 
              *nthreads < SHRT_MAX, "Invalid number of expecting threads to be created");       

        int   filenamelen = strlen(filename);
        CHECK(filenamelen <= MAX_FILENAME, "Too long filename");
        strcpy(name, argv[1]);
        return 0;
}


void print_diff(struct timeval begin, struct timeval end, char* begin_str)
{
        long long seconds = (long long)end.tv_sec  - (long long)begin.tv_sec;
        long long micros  = (long long)end.tv_usec - (long long)begin.tv_usec;
        if (micros < 0)
        {
                micros += 1000000;
                seconds -= 1;
        }
        fprintf(stderr, "%s %lld.%06lld\n", begin_str, seconds, micros);
}

