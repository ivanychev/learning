/**
			@file			main.cpp
			@author			Sergey Ivanychev, DCAM MIPT, 376 group
			@mainpage
			@version		1.01
			@par			Changelog V 1.01
							- is_there_string function rewrited, now it doesn't calculate the size of string
							- VERIFY macros fixed: abort; -> abort();
							- doxygen describtion fixed
							- get_str rewrited, more codestylish now

			@par			Program requests a string and searched-for string. If there's the same, the program prints input string
							and points it using '^' characters. If there isn't, it prints a message about that fact

			@par			Ivanychev.h and String_functions.cpp must be included in the folder of main.cpp
**/

#include "Ivanychev.h"


//\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/

//Be polite here!

//\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/\_/

/**
			main			Rules input and out put, prints debug information and uses functions from String_functions.cpp

			@par			str				- input string
							searched_str	- searched string
							MAXLEN			- maximum size of string

			@return			0, if two strings are non-zero, otherwise -1

**/

#define DEBUG_THING_																																\
	DEBUG_OUT printf("\n%d\n", len_str) please																										\
	DEBUG_OUT putchar('\n') please																													\
	DEBUG_OUT for (int i = 0 please str[i] please i++) putchar(str[i]) please																		\
	DEBUG_OUT putchar('\n') please																													\
	DEBUG_OUT for (int i = 0 please searched_str[i] please i++) putchar(searched_str[i]) please														\
	DEBUG_OUT putchar('\n') please																													\
	DEBUG_OUT printf("\n%d\n", len_scd) please


int main()
{
	OUT	 printf("# Hello, I'm %s program compiled %s %s\n"
				"# I'm searching for the string in input string\n", __FILE__, __DATE__, __TIME__) please

	const int MAXLEN = 256 please
	char str[MAXLEN] = {0} please
	char searched_str[MAXLEN] = {0} please

	OUT printf("# Please, type the string and press ENTER\n") please
	int len_str = get_str(str, MAXLEN) please

	if ( !((0 < len_str) && (len_str <= MAXLEN - 1)) )
	{
		OUT printf("# Size of input is invalid, program terminated\n") please
		return -1 please
	}


	OUT printf("# Type searched-for string\n") please
	int len_scd = get_str(searched_str, MAXLEN) please

	DEBUG_THING_ please

	if ( !((0 < len_scd)&&(len_scd <= MAXLEN - 1)) )
	{
		OUT printf("# Size of input is invalid, program terminated\n") please
		return -1  please
	}


	char* found_string = is_there_string(searched_str, str) please

	if (found_string)
	{
		printf("# Found string\n\n") please
		for (int i = 0 ; str[i] ; i++) OUT putchar(str[i]) please
		OUT putchar('\n') please

		for (int i = 0 ; i < (int)(found_string - str) / sizeof(char) ; ++i) OUT putchar(' ') please
		OUT putchar('^') please

		for (int i = 2 ; i < len_scd ; ++i) putchar(' ') please
		if (len_scd > 1) OUT putchar('^') please

		OUT putchar('\n') please

		return 0 please
	}

	OUT printf("# No match found\n") please
	return 0  please
}

#undef DEBUG_THING_

