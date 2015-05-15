#include <stdio.h>
#include "dict.h"
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>


/*
    my_malloc function is aimed at assuming that memory allocation 
    function might fail. That case can't be easily reproduced on current 
    machine.
*/

const char* error_msgs[] = {
        "",
        "OK",
        "Memory allocation failed",
        "Invalid argument passed",
        "The string is too long",
        "The string is already in dictionary",
        "No such string in dictionary",
        ""
};

//      Last error structure contains information about the last error
//      Addition information might be printed via print_error()


error LAST_ERROR = {
    .errno = OK
};

void set_error(int errno_)
{
    if (ERRORS_START < errno_ && errno_ < ERRORS_FINISH)
        LAST_ERROR.errno = errno_;
}

void print_error()
{
    if (ERRORS_START < LAST_ERROR.errno && LAST_ERROR.errno < ERRORS_FINISH) {
        printf("%s\n", error_msgs[LAST_ERROR.errno - ERRORS_START]);
        return;
    }
    printf("No such error number\n");
}



void* my_malloc(size_t size)
{
    int temp = rand()%10;
    if (temp == 0)
        return NULL;
    return malloc(size);
}


dict* create () {
        dict *mydict = (dict *)my_malloc(sizeof(dict));
        if (mydict == NULL) {
                set_error(ALLOC_FAIL);
                fprintf(stderr, "Not enough memory\n");
                return NULL;
        }
        mydict->size=0;
        mydict->root=NULL;
        return mydict;
}

void add(dict *mydict, char *str1, char *str2) {
        if (mydict == NULL) {
                set_error(INVAL_ARG);
                fprintf(stderr, "Invalid pointer\n");
                return;
        }
        node* tmp = (node *)my_malloc(sizeof(node));
        if (tmp == NULL) {
                set_error(ALLOC_FAIL);
                fprintf(stderr, "Not enough memory\n");
                return;
        }
        if (strlen(str1) >= MAXLEN ||
            strlen(str2) >= MAXLEN) {
                free(tmp);
                set_error(LONG_STRING);
                fprintf(stderr, "Some of strings might be too long\n");
                return;
        }

        tmp->left=NULL;
        tmp->right=NULL;
        // tmp->word=str1;
        // tmp->meaning=str2;

        strcpy(tmp->word,    str1);
        strcpy(tmp->meaning, str2);
        node* ch;
        node* pr;

        if (mydict->size == 0) {
                mydict->root=tmp;
        } else {
                ch=mydict->root;
                while (ch != NULL) {
                        pr=ch;
                        if (strcmp(str1, pr->word) < 0) {
                                ch=pr->left;
                        } else if (strcmp(str1, pr->word) > 0) {
                                ch=pr->right;
                        } else {
                                set_error(IN_DICT);
                                printf ("Can't add the word '%s'. It is in dictionary\n", str1);
                                free(tmp);
                                return;
                        }
                }
                if (strcmp(str1, pr->word) < 0) pr->left=tmp;
                else pr->right=tmp;
        }
        mydict->size++;
}

void show_node (node *tmp) {
        if (tmp == NULL) return;
        show_node (tmp->left);
        printf ("%s -> %s\n", tmp->word, tmp->meaning);
        show_node (tmp->right);
}

void show (dict *mydict) {
        if (mydict == NULL) {
                set_error(INVAL_ARG);
                fprintf(stderr, "Invalid pointer\n");
                return;
        }
        show_node(mydict->root);
}

int size (dict *mydict) {
        if (mydict == NULL) {
                set_error(INVAL_ARG);
                fprintf(stderr, "Invalid pointer\n");
                return INT_MAX;
        }
        return mydict->size;
}

node *search (dict *mydict, char *str) {
        if (mydict == NULL) {
                set_error(INVAL_ARG);
                fprintf(stderr, "Invalid pointer\n");
                return NULL;
        }

        if (str == NULL) {
            set_error(INVAL_ARG);
            fprintf(stderr, "Invalid pointer to the string\n");
            return NULL;
        }
        node *tmp;

        tmp=mydict->root;
        while (tmp!=NULL) {
                if (strcmp(str, tmp->word) == 0) {
                        return tmp;
                } else if (strcmp(str, tmp->word) < 0) {
                        tmp=tmp->left;
                } else if (strcmp(str, tmp->word) > 0) {
                        tmp=tmp->right;
                }
        }
        return tmp;
}

void print_meaning (dict *mydict, char *str) {
        node *tmp;
        tmp=search(mydict, str);
        if (tmp == NULL) {
                set_error(NOT_IN_DICT);
                printf ("There is no the word '%s' in the dictionary.\n", str);
        } else printf ("Meaning of the word '%s' is '%s'\n", str, tmp->meaning);

}

node *parent (dict *mydict, node *child) {
        if (mydict == NULL) {
                set_error(INVAL_ARG);
                fprintf(stderr, "Invalid first pointer\n");
                return NULL;
        }
        if (child == NULL) {
                set_error(INVAL_ARG);
                fprintf(stderr, "Invalid second pointer\n");
                return NULL;
        }
        node *tmp;
        tmp=mydict->root;
        if (search(mydict, child->word) == NULL) 
                return NULL;
        if (child == tmp) {
                return NULL;
        }
        while (tmp->left != child && tmp->right != child) {
                if (strcmp(tmp->word, child->word) < 0) {
                        tmp=tmp->right;
                } else if (strcmp(tmp->word, child->word) > 0) {
                        tmp=tmp->left;
                }
        }
        return tmp;
}


node *next (dict *mydict, node *tmp) {
        if (search(mydict, tmp->word) == NULL) 
                return NULL;
        node *min = tmp;

        if (tmp->right != NULL) {
                min=tmp->right;
                while (min->left != NULL) {
                   min=min->left;
                }
        } else 
                min = parent(mydict, tmp);
        return min;
}

void remove_word (dict *mydict, char *str) {
        if (mydict == NULL) {
                set_error(INVAL_ARG);
                fprintf(stderr, "Invalid pointer\n");
                return;
        }
        if (str == NULL) {
                set_error(INVAL_ARG);
                fprintf(stderr, "NULL pointer to the string\n");
                return;
        }
        node *tmp, *pr;
        tmp=search (mydict, str);
        if (tmp == NULL) {
                set_error(IN_DICT);
                fprintf (stderr, "There is no the word '%s' in the dictionary.\n", str);
                return;
        }
        pr=parent(mydict, tmp);
        if (tmp->left == NULL && tmp->right == NULL) {
                if (pr != NULL) {
                        if (pr->left == tmp) pr->left=NULL;
                        else pr->right=NULL;
                } else mydict->root = NULL;
                free(tmp);
                mydict->size--;
        } else  if (tmp->left == NULL && tmp->right != NULL) {
                if (pr != NULL) {
                        if (pr->left == tmp) pr->left=tmp->right;
                        else pr->right=tmp->right;
                } else  {
                        mydict->root=tmp->right;
                }
                free(tmp);
                mydict->size--;
        } else  if (tmp->left != NULL && tmp->right == NULL) {
                if (pr != NULL) {
                        if (pr->left == tmp) pr->left=tmp->left;
                        else pr->right=tmp->left;
                } else {
                        mydict->root=tmp->left;
                }
                free(tmp);
                mydict->size--;
        } else if (tmp->left != NULL && tmp->right != NULL) {
                node *ch;
                ch=next(mydict, tmp);
                char *str1, *str2;

                char word_buf[MAXLEN];
                char mean_buf[MAXLEN];

                strcpy(word_buf, ch->word);
                strcpy(mean_buf, ch->meaning);

                remove_word(mydict, ch->word);
                
                strcpy(tmp->word,    word_buf);
                strcpy(tmp->meaning, mean_buf);
        }
}

void remove_subtree (dict *mydict, node *root) {
        if (root == NULL) 
                return;
        remove_subtree(mydict, root->right);
        remove_subtree (mydict, root->left);
        free(root);
        mydict->size--;
}

void remove_tree (dict *mydict) {
        if (mydict == NULL) {
                set_error(INVAL_ARG);
                fprintf(stderr, "Invalid pointer\n");
                return ;
        }
        remove_subtree(mydict, mydict->root);
        free(mydict);
}


