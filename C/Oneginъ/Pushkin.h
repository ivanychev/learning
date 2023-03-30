#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

/**
                text_s						Contains the
information about text memory area. The object is generated after the text is
already scanned and area is done
                @param[out]	str_pointers	Pointer to the beginning of
string pointers
                @param		str_amount		The length of string
pointers array
                @param[out]	buffer			The pointer to the
beginning of text
**/

struct text_s {
  char **str_pointers;
  int str_amount;
  int char_amount;
  char *buffer;
};

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

typedef text_s text;

void input_analyse(FILE *stream, int *char_counter, int *str_counter);

void input_scan(FILE *stream, char *buffer, char **links);

void string_heapsort(char **pointers, int size,
                     int (*comp)(const char *first, const char *second));

void swap(char **first, char **second);

int get_text(FILE *stream, text *save_text);
