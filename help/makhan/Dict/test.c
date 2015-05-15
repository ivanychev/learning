#include "dict.h"
#include <stdio.h>

#define VERYLONGSTRING "12345678901234567890123456789012345678901234567890\
                        12345678901234567890123456789012345678901234567890\
                        12345678901234567890123456789012345678901234567890"

void filling (dict *a) {
        add (a, "dog", "собака");
        add (a, "cat", "кошка");
        add (a, "elephant", "слон");
        add (a, "eagle", "орЄл");
        add (a, "hen", "курица");
        add (a, "crocodile", "крокодил");
}

void delete (dict *a, char *str1, char *str2) {
        remove_word (a, str1);
        add (a, str1, str2);
}

void test();

int main () 
{
        int i = 0;
        for (i = 0; i < 100; ++i)
                test();
        return 0;
}


void test()
{
        dict *a;
        a=create ();
        add (NULL, "cat", "dog");
        add (a, "dog", "собака");
        add (a, "dog", "собака");
        add (a, "dog", VERYLONGSTRING);
        remove_word (a, "dog");
        remove_word (a, "hen");
        remove_word (a, NULL);
        search (a, "cat");
        show (NULL);
        print_meaning (a, "hen");
        filling(a);
        node *nd;
        nd=next (a, search(a, "dog"));
        show (a);
        printf ("%d\n", size(NULL));
        printf ("%d\n", size(a));
        search (NULL, "cat");
        search (a, "cat");
        search (a, "elephant");
        print_meaning (a, "cat");
        print_meaning (a, "elephant");
        remove_word (NULL, "cat");
        parent (NULL, NULL);
        parent (a, NULL);
        remove_word (a, "crocodile");
        nd=next (a, search (a, "cat"));
        add (a, "crocodile", "крокодил");
        delete (a, "cat", "кошка");
        delete (a, "hen", "курица");
        delete (a, "cat", "кошка");
        delete (a, "elephant", "слон");
        delete (a, "crocodile", "крокодил");
        add (a, "lion", "лев");
        remove_word (a, "elephant");
        remove_word (a, "eagle");
        remove_word (a, "hen");
        remove_word (a, "dog");
        remove_tree (NULL);
        remove_tree (a);
}
