#define _ISOC11_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES    5000 /* максимальное число строк */
#define MAXLEN      1000
char*   lineptr[MAXLINES]; /* указатели на строки текста */

int  readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines, int reverse);
// void quicksort(void *lineptr[], int left, int right,
//      int (*comp)(void *, void *));
int numcmp(const void *, const void *);

int cmpstrings(const void* p1, const void* p2)
{
    return strcmp(*(char**)p1, *(char**)p2);
}

 int readlines(char *lineptr[], int maxlines)
{
	int len = 0; 
    	int nlines = 0;
	char *p = NULL;
    	char line[MAXLEN];

	nlines = 0;

	while ((len = strlen(fgets(line, MAXLEN, stdin))) > 1)
    {
        line[ len - 1] = '\0';       // line contain last '\n' symbol, which must be removed
        len = len - 1;
        p = malloc(len);
        if (nlines >= maxlines || p == NULL)
			return -1;
		else {
			strcpy(p, line);
			lineptr[nlines] = p;
            nlines++;
        }
	}
	return nlines;
}
int numcmp(const void *s1, const void *s2)
{
	double v1 = 0, v2 = 0;

	v1 = atof(*(char**)s1);
	v2 = atof(*(char**)s2);

	if (v1 < v2)
		return -1;
	else if (v1 > v2)                                     
		return 1;      
	else
		return 0;
}


	
 int main(int argc, char *argv[])
 {
    int nlines  = 0;   /* количество прочитанных строк */
    int numeric = 0;   /* 1, если сорт. по числ. знач. */
    int reverse = 0;   /* 1, если выводить по убыванию */
    int c = 0;
    int i = 0;
    for (i = 1; i < argc; ++i)
    {
        if (argv[i][0] == '-')
        {
            switch (argv[i][1]) {
            case 'n':
                numeric = 1;
                break;
            case 'r':
                reverse = 1;
                break;
            default:
                printf("sort: неверный параметр %c\n", c);
                return -1;
            break;
           }
       }
    }

    int (*needed_func)(const void*, const void*) = NULL;

    if (numeric)
        needed_func = numcmp;
    else
        needed_func = cmpstrings;

    nlines = readlines(lineptr, MAXLINES);
    
    if (nlines >= 0) {
        qsort(  lineptr, 
                nlines, 
                sizeof(*lineptr),
                needed_func);

        printf("SORTED:\n");
        writelines(lineptr, nlines, reverse);
        return 0;
     } 
     else {
         printf("Bведено слишком много строк\n");
         return -1;
     }
 }

 /* writelines: печать строк */
 void writelines(char *lineptr[], int nlines, int reverse)
 {
    int i = 0;
    if (reverse)
        for (i = 0; i < nlines; i++)
            printf("%s\n", lineptr[nlines - 1 - i]);
    else
        for (i = 0; i < nlines; i++)
            printf("%s\n", lineptr[i]);
 }
