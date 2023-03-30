#include "Pushkin.h"

/**
                swap				function replaces each pointer
with another one
                @return				void
**/
void swap(char **first, char **second);

// void string_qsort(char** pointers, int size, int (*comp)(const char*
// first,const char* second));

/**
                string_heapsort			functions that sorts the array
of pointers, comparing strings which are pointed by them. I know that it's
possible to do without function pointer but I wanted to use it for the first
time. Function uses heap algorythm.
                @param[out] pointers	the pointer to the beginning of string
pointers array
                @param		size		the size of array
                @param[out]	comp		function that is used to compare
pointers

                @return					void
**/
void string_heapsort(char **pointers, int size,
                     int (*comp)(const char *first, const char *second));

/**
                input_analyse					function
analyses the input text for the amount of meaning chars and strings
                @param[out]		stream			file stream
                @param[out]		char_counter	variable contains the
amount of meaning chars
                @param[out]		str_counter		variable
contains the amount of meaning strings

                @return							void
**/
void input_analyse(FILE *stream, int *char_counter, int *str_counter);

/**
                input_scan
function scans the text from the stream getting only meaning chars and strings
                @param[out]		stream			file stream
                @param[out]		buffer			pointer to the
memory area where the input text is contained
                @param[out]		links			pointer to the
memory area where the pointers to the strings are contained

                @return							void
**/

void input_scan(FILE *stream, char *buffer, char **links);

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

void input_analyse(FILE *stream, int *char_counter, int *str_counter) {
  assert(stream);
  int c = 0;
  while ((c = fgetc(stream)) != EOF) {
    if (c == '\n')
      continue;
    while (isspace(c))
      c = fgetc(stream);

    if ((c == '\n') || (c == EOF))
      continue;

    while (c != '\n' && c != EOF) {
      if (isspace(c)) {
        while (isspace(c) && c != '\n' && c != EOF)
          c = fgetc(stream);
        if ((c == '\n') || (c == EOF))
          continue;
        (*char_counter)++;
      }
      (*char_counter)++;
      c = fgetc(stream);
    }
    (*char_counter)++;
    (*str_counter)++;
    if (c == EOF) {
      (*char_counter)++;
      return;
    }
  }
  (*char_counter)++;
}

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

void input_scan(FILE *stream, char *buffer, char **links)

{
  assert(stream);
  int c = 0;
  bool string_begun = false;
  while ((c = fgetc(stream)) != EOF) {
    string_begun = false;
    if (c == '\n')
      continue;
    while (isspace(c))
      c = fgetc(stream);

    if ((c == '\n') || (c == EOF))
      continue;

    while (c != '\n' && c != EOF) {
      if (isspace(c)) {
        while (isspace(c) && c != '\n' && c != EOF)
          c = fgetc(stream);
        if ((c == '\n') || (c == EOF))
          continue;
        *(buffer++) = ' ';
      }
      *(buffer++) = c;
      if (!(string_begun)) {
        *(links++) = buffer - 1;
        string_begun = true;
      }
      c = fgetc(stream);
    }
    *(buffer++) = '\0';
  }
  *(buffer++) = '\0';
}

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

/*{
int c = 0;

while ((c = fgetc(stream)) != EOF)
{
        if (c == '\n') continue;
        *(links++) = c;
        while (isspace(c)) c = fgetc(stream);
        while (c != '\n' && c != EOF)
        {
                if (isspace(c))
                {
                        while (isspace(c) && c != '\n' && c != EOF) c =
fgetc(stream); if ((c == '\n') || (c == EOF)) continue;
                        *(buffer++) = c;
                        fputc(c, stream);
                }

                *(buffer++) = '\0';

                fputc(c, stream);
                c = fgetc(stream);
        }
        *(buffer++) = '\0';
        fputc(c, stream);
        *(links++) = buffer;
        if (c == EOF)
                {
                        *(buffer++) = c;
                        return 0;
                }
}
*(buffer++) = '\0';
fputc(c, stream);
return 0;
}
*/

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

int get_text(FILE *stream, text *save_text) {
  assert(stream);
  assert(save_text);
  register int c = 0;
  if ((c = getc(stream)) == EOF)
    return -1;
  ungetc(c, stream);

  int char_counter = 0;
  int str_counter = 0;

  input_analyse(stream, &char_counter, &str_counter);

  int ret = fseek(stream, 0, SEEK_SET);
  assert(!(ret));

  void *inp_text =
      calloc(1, (char_counter) * sizeof(char) + str_counter * sizeof(char *));

  char *text_begin = (char *)((int)inp_text + str_counter * sizeof(char *));
  input_scan(stream, text_begin, (char **)inp_text);
  /*
  char* text_begin = (char*)((int)inp_text + str_counter * sizeof(char*));

  char** pointer_current = (char**)text_begin - 1;
  *(pointer_current--) = text_begin;
  char* char_current = text_begin;


  while ( (c = getc(stream)) != EOF)
  {
          *(char_current) = c;
          if (*(char_current) == '\n')
          {
                  *(char_current) = '\0';
                  *(pointer_current--) = char_current + 1;
          }
          char_current++;
  }
  *char_current = '\0';
  */

  save_text->str_pointers = (char **)inp_text;
  save_text->str_amount = str_counter;
  save_text->buffer = text_begin;
  save_text->char_amount = char_counter;

  return 0;
}

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

void string_heapsort(char **pointers, int size,
                     int (*comp)(const char *first, const char *second)) {
  assert(pointers);
  assert(comp);
  while (size > 1) {
    int last_father = size / 2 - 1;
    int father = last_father;
    while (father >= 0) {
      if (father == last_father) {
        if ((size > father * 2 + 2) &&
            ((*comp)(pointers[father * 2 + 2], pointers[father]) < 0))
          swap(pointers + father * 2 + 2, pointers + father);
        if ((*comp)(pointers[father * 2 + 1], pointers[father]) < 0)
          swap(pointers + father * 2 + 1, pointers + father);
      } else {
        if ((*comp)(pointers[father * 2 + 2], pointers[father]) < 0)
          swap(pointers + father * 2 + 2, pointers + father);
        if ((*comp)(pointers[father * 2 + 1], pointers[father]) < 0)
          swap(pointers + father * 2 + 1, pointers + father);
      }
      father--;
    }
    swap(pointers, pointers + size - 1);
    size--;
  }
}

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

void swap(char **first, char **second) {
  assert(first);
  assert(second);
  char *temp = *first;
  *first = *second;
  *second = temp;
}

/*
void string_qsort(char** pointers, int size, int (*comp)(const char* first,const
char* second))
{

        int l = 0, r = size - 1;
        int i = l, j = r;
        int random = rand()%(size);
        char** temp = pointers + random;
        //printf("\nSize = %d, temp = %d, st[temp] = [%s]\n", size, random,
*(pointers + random)); for (int i = 0; i < size; ++i) printf("%s ", *(pointers +
i));
        //putchar('\n');
        while (i <= j)
        {
                while ((*comp)(*temp, pointers[i]) < 0) ++i;
                while ((*comp)(*temp, pointers[j]) > 0) --j;
                if (i <= j)
                {
                        swap(pointers + i , pointers + j);
                        ++i;
                        --j;
                }
        }
        printf("i = %d, j = %d\n", i, j);
        for (int i = 0; i < size; ++i) printf("%s ", *(pointers + i));
        putchar('\n');
        putchar('\n');
        if (l < j) string_qsort(pointers, j + 1, comp);
        if (i < r) string_qsort(pointers + i, r - i + 1, comp);
}
*/