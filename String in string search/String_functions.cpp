#include "Ivanychev.h"

/**
		get_str					function that scans for a string

		@param[out]	string		string to be filled with data
		@param		MAXLINE		The maximum size of input string

		@return					The length of input string
**/
int get_str(char * string, const int max);

/**
		is_there_string				searches for string in string

		@param[out]		searched	a string to search for
		@param[out]		string		source string

		return						pointer to the found fragment, if it's found, otherwise NULL
**/

char* is_there_string(char* searched, const int size_scd, char* string, const int size_str);

/**		string_size				counts the size of string
		@param[out]	string		analysing string
		@return					the size of string
**/

int string_size(char * string);


int get_str(char * string, const int MAXLINE)
{
	ASSERT(string);
	VERIFY(MAXLINE > 0);
	const int alive = 1;
	int len = 0;

	while (alive)
	{
		string[len] = getchar();
		if (string[len] == EOF)		break;
		if (string[len] == '\n')	break;
		if (len == MAXLINE - 1)			break;
		len++;

	}
	string[len] = 0;
	return len;
}

//\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/


char* is_there_string(char* searched, char* string)
{
	ASSERT(searched);
	ASSERT(string);

	char scd_start = searched[0];
	char* position = string;
	int cond = 0;
	for ( ; *(position); position++)
		if (position[0] == scd_start)
		{
			cond = 0;
			for (int i = 0; searched[i]; i++ )
				if (( searched[i] ) != ( position[i] ))
				{
					cond = 1;
					break;
				}

			if ( !(cond) ) return position;
		}

	return NULL;

}

//\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/



/*
int string_size(char * string)
{
	ASSERT(string);
	int size = 0;
	while (*(string++)) size++;
	return size;
}
*/

/*
int compare_strings(char* str1, char* str2)
{
	while (*str1++ == *str2++)	if(!(*(str1 - 1))) return 0;
	return *(str1 - 1) - *(str2 - 1);
}
*/

