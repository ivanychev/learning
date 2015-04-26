/**
		@file					main.cpp
		
		@author					Sergey Ivanychev, MIPT DCAM, sergeyivanychev@gmail.com
		@mainpage

		@version				1.1

		@par					Changelog V 1.1
								
								- Lots of new documentation
								- Fixed memory leak, during Command structures destructing
								- Fixed error in MOV operator translation

		@par					This project is logic continuation of last term's Collibri (my language!) compiler. The project called Ganymede-x86
								and it's goal to translate executable files of Ganymede processor into executable of x86 Win32.

								The main idea is generating an template executable with all data fields required for Ganymede translation. That programm
								reads the input .ivz file and translates input Ganymede machine code into x86 machine code, patching template executable
								at the end, which makes translated code autonomous

								The logic core is creating special CODE object, which contain the array of COMMAND objects in it. Each COMMAND object - 
								is a single Ganymede command with it's arguments and its translation in x86, including all methods for working with it

		@par					Project files:
								
								- Code.h				contain CODE class definition and addresses and offsets of prepared template executable
								
								- command.h			contain COMMAND and COMMAND_TEMPLATE defenitions and the ammount of translation template strings
													Each command x86_translation initializes with COMMAND_TEMPLATE object of such Ganymede command.
													That template sends to COMMAND template string of translation, where there wouldn't be any offsets
													and addresses. So, when all code is loaded and all command objects exist, the translation isn't ready
													yet. The next step is calling the CODE::revive_code() function that counts and pastes all things code needs
								
								- Ganymede_instructions.h	
													
													A small header that was created to easily initialise function pointers arrays and other things

								- exception.h		The header contain the definitions of my exception classes, that inherited from STD::EXCEPTION.
													Those exception are used in all my code

								- command_codes.h	Necessary information about Ganymede streams and commands



		@par					The directory also contain the source code of template.exe

		@todo					- Deal with CopyFile function and Unicode string in it
**/

#include "exception.h"
#include "command.h"
#include "Code.h"
#include "windows.h"
#include <tchar.h>


ofstream strlog;

int tmain(unsigned int argc, char* argv[]);

int main(unsigned int argc, char* argv[])
{
	int ret = 0;
	try {ret = tmain(argc, argv);}
	catch (ivException& exc) 
	{
		exc.listed_report(cout);
		exc.listed_delete();
	}
	catch (ivLogic_error& exc) 
	{
		exc.listed_report(cout);
		exc.listed_delete();
	}
	catch (ivRuntime_error& exc) 
	{
		exc.listed_report(cout);
		exc.listed_delete();
	}
	return ret;
}

int tmain(unsigned int argc, char* argv[])
{
	strlog.open("log.txt");
	ifstream ganymede_exe("executable.ivz");
	ofstream template_exe("template.exe", std::ios::in | std::ios::binary);

	RT_ASSERT(ganymede_exe.is_open() == true, "Failed to open Ganymede executable");
	RT_ASSERT(template_exe.is_open() == true, "Faield to open Win32 executable template");
	
	//ifstream template_exe("template.exe");

	//LPCWSTR source_copy = L"C:\\Users\Иванычев\Google Диск\Работа\Программирование\Visual Studio\Ganymede-x86\Ganymede-x86\template.exe";
	//LPCWSTR dest_copy   = L"C:\\Users\Иванычев\Google Диск\Работа\Программирование\Visual Studio\Ganymede-x86\Ganymede-x86\compiled.exe";
	//bool check_copy = CopyFileW(source_copy, dest_copy, true);
	//assert(check_copy);
	
	//ofstream compiled_exe("compiled.exe");
	
	unsigned count_until_template_size = 0;

	Code magic(ganymede_exe, strlog, template_exe);
	bool check_get_code = magic.get_code();
	printf("Code is scanned %s", (check_get_code)? "successfully\n": "unsuccessfully\n");

	magic.console_print_gan_code();
	magic.revive_code();
	magic.console_print_gan_code();
	magic.patch_exe(template_exe);

	strlog.close();
	ganymede_exe.close();
	template_exe.close();

	printf("GOOD");
	return 0;
	
}






