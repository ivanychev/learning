#include "stdio.h"
#include "stdlib.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


enum CASE_TYPES {
        TAKEOFF = 1,
        LANDING = 2
};

typedef struct {
        unsigned day;
        unsigned hour;
        unsigned min;
        unsigned type;  
} Case;

typedef struct {
        long type;
        Case task;
} task;


int get_case(FILE* fd, Case* to_save)
{
        char type = 0, temp = 0;
        int ret = 0;
        unsigned day = 0, hour = 0, min = 0;

        ret = fscanf(fd, "%c%c %u %u:%u", &temp, &type, &day, &hour, &min);
        if (ret != 5) {
                printf("Failed to read current case, scanf returned %d\n", ret);
                return -1;
        }

        switch (type) {
        case 't':
                to_save->type = TAKEOFF;
                break;
        case 'l':
                to_save->type = LANDING;
                break;
        default:
                printf("Got wrong character of type, expected \"t\" or \"l\"\n");
                return -1;
        }

        to_save->day = day;
        to_save->min = min;
        to_save->hour= hour;
        return 0;
}

Case* get_cases(FILE* fd, int* num_tosave) {
        unsigned num = 0, i = 0;
        int ret = 0;
        Case* arr = 0;

        ret = fscanf(fd, "%u", &num);
        if (ret != 1) {
                printf("Failed to get number of cases\n");
                return NULL;
        }
        printf("Expecting %u cases\n", num);

        arr = (Case*)calloc(num, sizeof(Case));
        if (arr == NULL) {
                printf("Failed to allocate memory\n");
                return NULL;
        }

        for (i = 0; i < num; ++i) {
                ret = get_case(fd, &(arr[i]));
                arr[i].index = (unsigned)i;
                if (ret == -1) {
                        printf("Failed to read %d'th case\n", i);
                        free(arr);
                        return NULL;
                }
        }

        *num_tosave = num;
        return arr;
}

Case* get_args(int argc, char const *argv[], int* num_tosave)
{
        const char* path = NULL;
        if (argc != 2) {
                printf("Wrong number of arguments\n"
                       "One argument is path to the file with cases\n");
                return NULL;
        }
        path = argv[1];
        FILE* fd = fopen(path, "r");
        if (fd == NULL) {
                printf("Failed to open file\n");
                return NULL;
        }

        Case* cases = get_cases(fd, num_tosave);
        return cases;
}

void print_case(Case* cur_case)
{
        printf("%s on day %u, time %u:%u\n", 
                        (cur_case->type == LANDING)? "Landing":"Takeoff", 
                         cur_case->day,
                         cur_case->hour,
                         cur_case->min);
}

void print_cases(Case* arr, int size)
{
        int i = 0;
        for (i = 0; i < size; ++i) 
                print_case(&(arr[i]));
}

int get_ips_msgqueue(int ips) {
     int msgqueue = 0;
    if ((msgqueue = msgget(0, IPC_PRIVATE | 0660)) == -1) {
        printf("Failed to get message queue\n");
        return -1;
    }
    return msgqueue;
}



int fill_tasks(int msgid, Case* arr, int num) 
{
    int i = 0;
    int cond = 0;
    task temp = {.type = 1};
    for (i = 0; i < num; ++i) {
        temp.task = arr[i];
        cond = msgsnd(msgid, &temp, sizeof(temp.task), IPC_NOWAIT);
        if (cond == -1)
            return -1;
    }
    return 0;
}

int case_compare(const void* arg1, const void* arg2)
{
        Case* case1 = (Case*)arg1;
        Case* case2 = (Case*)arg2;

        if (case1->day - case2->day != 0)
                return case1->day - case2->day;
        if (case1->hour - case2->hour != 0)
                return case1->day - case2->day;
        if (case1->min  - case2->min  != 0)
                return case1->min - case2->min;
        return 0;
}

void sort_tasks(Case* arr, int num)
{
        qsort(arr, num, sizeof(Case), case_compare);
}


int main(int argc, char const *argv[])
{
        Case* cases = NULL;
        int num = 0;

        cases = get_args(argc, argv, &num);
        if (cases != NULL) 
                print_cases(cases, num);
        else
                printf("Failed to get args, terminating...\n");
        sort_tasks(cases, num);

        if (cases != NULL) 
                print_cases(cases, num);
        else
                printf("Failed to get args, terminating...\n");
        return 0;
}
