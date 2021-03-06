#include <stdio.h>

typedef struct dict dict;
typedef struct node node;
typedef struct {
        int errno;
} error;

enum ERRORS {
        ERRORS_START,
        OK,
        ALLOC_FAIL,
        INVAL_ARG,
        LONG_STRING,
        IN_DICT,
        NOT_IN_DICT,
        ERRORS_FINISH
};

#define MAXLEN 100

struct node {
        char word[MAXLEN];
        char meaning[MAXLEN];
        node *left;
        node *right;
};

struct dict {
        int size;
        node *root;
};

dict *create ();

void add(dict *mydict, char *str1, char *str2);

void show (dict *mydict);

node *search (dict *mydict, char *str);

node *next (dict *mydict, node *node);

void print_meaning (dict *mydict, char *str);

int size (dict *mydict);

void remove_word (dict *mydict, char *str);

node *parent (dict *mydict, node *child);

void remove_tree (dict *mydict);

void set_error(int errno_);

void print_error();
