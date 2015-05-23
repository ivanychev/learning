#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"

#define MB (1024*1024)

// SIZE constant is observed via experiment
// After 8000 allocations the OS killed my program
#define SIZE 7800

int main(int argc, char const *argv[])
{
        void** array = (void**) calloc(SIZE, sizeof(void*));
        int index = 0;
        void* ptr = NULL;
        while (index < SIZE && (ptr = calloc(1, MB))) {
                array[index] = ptr;
                memset(ptr, 0, MB);
                index++;
                fprintf(stderr, "Index = %d\n", index);
        }
        
        index = 0;
        while (index < SIZE && array[index] != NULL) {
                free(array[index]);
                array[index] = NULL;
                index += 2;
        }                                       // deleting every second

        // attempting to allocate big piece of memory
        // supposed to fail if kernel don't defrag memory 
        ptr = malloc(300 * MB);
        printf("ptr = %p\n", ptr);
        sleep(3);
        if (ptr)
                free(ptr);


        for (index = 0; index < SIZE; index++) 
                if (array[index] != NULL){
                        free(array[index]);
                        array[index] = NULL;
                }
        free(array);
        return 0;
}
