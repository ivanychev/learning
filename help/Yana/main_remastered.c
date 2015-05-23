#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BITSPERBYTE 8
#define RATIO 0.7

typedef struct 
{
    int           size;
    int           elems;
    char**        array;    
} Htable;

Htable* __hash_create(int size);

int hash_add(Htable* this, char* str);

int hash_search(Htable* this, char* str);



const int HASH_BASIC_SIZE = 10;

Htable* hash_create() 
{
    return __hash_create(HASH_BASIC_SIZE);
}

Htable* __hash_create(int size)
{
    char** new_arr = NULL;
    Htable*      new_hash = (Htable*)      calloc(1, sizeof(Htable));
    if (new_hash == NULL)
        return NULL;
    new_arr  = (char**) calloc(size, sizeof(char*));
    if (new_arr == NULL)
        return NULL;

    new_hash->array = new_arr;
    new_hash->elems = 0;
    new_hash->size  = size;
    return new_hash;
}

int hash_destroy(Htable* this)
{
    int i = 0;
    if (this == NULL)
        return 0;
    for (i = 0; i < this->size; ++i)
        if (this->array[i] != NULL) {
            free(this->array[i]);
            this->array[i] = NULL;
        }
    free(this->array);
    this->array = NULL;
    this->elems = 0;
    this->size = 0;
    free(this);
    return 0;
}

unsigned int hash_get(char * str, unsigned base){
    int i = 0;
    unsigned ret = 0;
    if (str == NULL)
        return 0;
    while (str[i] != 0) {
        ret = ((ret << (sizeof(ret)* BITSPERBYTE - 1) | (ret >> 1)) ^ ((unsigned) str[i]));
        i++;
    }
    return ret % base;
}

int hash_full(Htable* this)
{
    if (this->size == this->elems)
        return 1;
    return 0;
}

void hash_strings_free(char** strs, int count)
{
    int i = 0;
    for (i = 0; i < count; ++i)
        if (strs[i] != NULL) {
            free(strs[i]);
            strs[i] = NULL;
        }
}

int hash_increase(Htable* this)
{
    int i = 0, ret = 0;
    if (this == NULL)
        return -1;
    
    Htable* new_this = __hash_create(this->size * 2);
    if (new_this == NULL) {
        printf("Failed to get new table :(\n");
        return -1;
    }

    for (i = 0; i < this->size; ++i)
        if (this->array[i]) {
            ret = hash_add(new_this, this->array[i]);
            if (ret == -1) {
                printf("Failed to push in new hash");
                return -1;
            }
        }

    hash_strings_free(this->array, this->size);
    free(this->array);
    *this = *new_this;
    free(new_this);
    return 0;
}

int hash_getpos(Htable* this, int hash)
{
    int i = 0;

    for (i = hash; i < this->size; ++i) 
        if (this->array[i] == NULL) 
            return i;
    
    for (i = 0; i < hash; ++i) 
        if (this->array[i] == NULL) 
            return i;
    return -1;
}


int hash_add(Htable* this, char* str) {
    unsigned hash = 0;
    int pos = 0;
    char* save_str = NULL;
    if (str == NULL || this == NULL)
        return -1;
    if (hash_search(this, str) != -1)
        return 0;

    if ((double)this->elems/this->size >= RATIO)
        hash_increase(this);

    hash = hash_get(str, this->size);
    pos =  hash_getpos(this, hash);
    if (pos == -1) {
        printf("Hash is invalid. No free space\n");
        return -1;
    }

    save_str = (char*) calloc(1, strlen(str) + 1);
    if (save_str == NULL) {
        printf("Failed to allocate memory\n");
        return -1;
    }
    
    strcpy(save_str, str);
    this->array[pos] = save_str;
    this->elems++;
    return 0;
}


int hash_search(Htable* this, char* str)
{
    int hash = 0, i = 0, iters = 0;
    if (this == NULL || str == NULL)
        return -1;

    hash = hash_get(str, this->size);
    i = hash;

    while (iters < this->size) {
        if (this->array[i] != NULL && strcmp(str, this->array[i]) == 0)
            return i;
        // printf("%d\n", i);
        iters++;
        i++;
        i = i % this->size;
    }

    return -1;
}

void hash_dump(Htable* this) {
    int i = 0;
    printf( "Hash table [%p]\n"
            "Size  = %d\n"
            "Elems = %d\n", this, this->size, this->elems);
    for (i = 0; i < this->size; ++i)
        printf("[%d:%d] - %s\n", i, hash_get(this->array[i], this->size),
                                     (this->array[i] == NULL)?"<EMPTY>":this->array[i]);
    printf("End of hash table dump\n\n");
}



void get_ui(Htable* table)
{
    char str[1024] = {};
    int ret = 0;
    printf( "Print \"add <word>\" to save it in table\n"
            "Print \"search <word>\" to search for it in table\n"
            "Print \"dump\" to print hash table info\n"
            "Print \"exit\" to stop program\n");
    while (1) {
        scanf("%s", str);
        if (strcmp(str, "exit") == 0)
            return;
        if (strcmp(str, "dump") == 0) {
            hash_dump(table);
            continue;
        }
        if (strcmp(str, "search") == 0) {
            scanf("%s", str);
            printf("%s\n", (hash_search(table, str) != -1)? "FOUND": "NOT FOUND");
            continue;
        }
        if (strcmp(str, "add") == 0) {
            scanf("%s", str);
            ret = hash_add(table, str);
            printf("Added %s\n", (ret == 0)? "sucessfully": "BADLY");
            continue;
        }
        printf("Invalid command inserted\n");
    }
}


int main() 
{
    Htable* table = hash_create();
    int ret = 0;
    if (table == NULL) {
        printf("Failed to create table\n");
    }

    if (ret != 0)
        printf("Found string\n");
    else
        printf("Didn't found");

    get_ui(table);

    hash_destroy(table);
    return 0;
}
