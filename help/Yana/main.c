#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct _hn {
    char*       name;
    int         hkey;
    int         val;
} Htable;

int size_hash = 0;
int elements = 0;
Htable** ht = NULL;

Htable**    hash_create     ();
void        hash_push       (char* name, int value);
void        hash_destroy    ();
int         hash_pop        (char* name);
unsigned    hash_func     (char* name);


Htable** hash_create() {
    size_hash = 2;
    int i;
    elements  = 0;
    Htable** res = (Htable**) calloc(sizeof(Htable*), size_hash);

    return res;
}

int htable_resize() {
    // unsigned new_hash;
    // size_t new_size;
    // int i;
    // ht = (Htable**) realloc(ht, size_hash * 2 * sizeof(Htable*));
    // new_size = size_hash * 2;

    // for (i = 0; i < size_hash; i++) {
    //     if (ht[i] != NULL) {
    //         new_hash = hash_func(ht[i]->name) %  new_size;
    //         if (new_hash & i != i) {
    //             ht[new_hash] = ht[i];
    //             ht[i] = NULL;
    //         }
    //     }
    // }
    // size_hash = new_size;
    // return 1;


}

void hash_push (char* name, int value) {
    int hf = get_hash(name, size_hash);
    printf ("%d;\n", hf);
    while ( ht[hf] && strcmp(ht[hf]->name, name)) hf = (hf + 1) % size_hash;
    printf ("%d\n", hf);
    if ( ht[hf]  == NULL ){
        ht[hf] = (Htable*) malloc(sizeof(Htable));
        ht[hf]->name = name;
        ht[hf]->hkey = get_hash(name, size_hash);
        ht[hf]->val  = value;
        elements++;
        printf ("%s\n", ht[hf]->name);
              if(elements * 10 > 7* size_hash){
            fprintf(stderr, "rehashing!\n");
            htable_resize();

            }
        }


    else if (!strcmp(ht[hf]->name, name))
        ht[hf]->val = value;

}


/*void hash_destroy () {
    int i;
    for ( i = 0; i < size_hash; i++)
        if (ht[i]) {free(ht[i]); ht[i] = NULL;}
    free(ht);
    ht = NULL;
}*/

int hash_pop (char* name) {
    unsigned int hf = get_hash(name, size_hash);
    while ( (hf <=  size_hash) && ((ht[hf] && strcmp(ht[hf]->name, name)) || !ht[hf] ) ) {
            hf = (hf + 1) % size_hash;
            //printf ("%d\n", hf);
    }
    if ( ht[hf] && !strcmp(ht[hf]->name, name) )
        return ht[hf]->val;
    printf("\nERROR program has not have variable %s\n", name);
    return 0;
}

 unsigned int hash_func(char * str){
    unsigned int hash = 0;
    for (; *str; str++){
        hash += (unsigned char)(*str);
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;

}

unsigned get_hash(char* str, int base) 
{
    if (base <= 0) {
        printf("Bad base given\n");
        return 0;
    }
    return hash_func(str) % base;
}

int main() {
    char *key1, *key2, *key3,*key4;
    int x = 10;
    int y = 20;
    int z = 30;
    int d = 90;
    ht     = hash_create();

    key1 = malloc(5 *  sizeof(char));
    sprintf(key1, "yana");
    key2 = malloc(5 *  sizeof(char));
    sprintf(key2, "doma");
    key3 = malloc(5 *  sizeof(char));
    sprintf(key3, "runo");
    hash_push(key1, x);
    hash_push(key2, y);
    hash_push(key3, z);
    hash_push(key4, d);
    x = hash_pop(key1);
    y = hash_pop(key2);
    z = hash_pop(key3);
    d = hash_pop(key4);
    printf("%d %d %d %d", x,y,z,d);
    return 0;
}
