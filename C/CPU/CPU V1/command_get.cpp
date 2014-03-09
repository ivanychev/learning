#include "cpu.h"


//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|


enum
{
	CMD_NONE = 1000,
	CMD_PUSH = 1001,
	CMD_POP = 1002,
	CMD_ADD = 1003,
	CMD_SUB = 1004,
	CMD_MUL = 1005,
	CMD_DIV = 1006,
	CMD_SIN = 1007,
	CMD_COS = 1008,
	CMD_TAN = 1009,
	CMD_SQRT = 1010,
	CMD_POW = 1011,
	CMD_END = 1012,
	CMD_DUMP = 1013,
	CMD_ERROR = 1014,
};

#define CHECK_COMMAND(str, name) (strcmp((_strupr(str)), #name) == 0)? CMD_##name : 


//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|


/**
		calculator					the first thing my cpu has to do is to solve Reverse Polish notation expressions.
									This functions scans the input file stream for basic set of commands and arguments
									and proceeds operations with numbers using th cpu
		@param[out]		strin		input file stream
		@param[out]		strout		output file stream
		@param[out]		my_cpu		pointer if initialized cpu

		@return						0
**/


int calculator(FILE* strin, FILE* strout, cpu* my_cpu)
{
	VERIFY(my_cpu != NULL);
	const char MAXLINE = 10;
	char word[MAXLINE] = {};
	const char PUSH_MAXLINE = 50;
	char push_word[PUSH_MAXLINE] = {};
	int c = 0;

	double temp = 0;
	int cond = 0;
	
	fprintf(stdout,	"# This is prototype of processor unit which calculates expressions\n"
				"# written in inverted Polish way (or something like that)\n"
				"# There are commands available:\n"
				"\n push {number}\n"
				" pop\n"
				" add\n"
				" sub\n"
				" mul\n"
				" div\n"
				" sin\n"
				" cos\n"
				" tan\n"
				" sqrt\n"
				" pow\n"
				" end\n"
				"PLEASE, USE [.] TO DIVIDE FLOAT PART\n"
				"Here you go\n");

	while (true)
	{
		cond = cpu_check(my_cpu);
		VERIFY(cond == CPU_CHECK_OK);
		
		fscanf(strin,"%s", &word);

		c = CHECK_COMMAND(word, PUSH)
			CHECK_COMMAND(word, POP)
			CHECK_COMMAND(word, ADD)
			CHECK_COMMAND(word, SUB)
			CHECK_COMMAND(word, MUL)
			CHECK_COMMAND(word, DIV)
			CHECK_COMMAND(word, SIN)
			CHECK_COMMAND(word, COS)
			CHECK_COMMAND(word, TAN)
			CHECK_COMMAND(word, SQRT)
			CHECK_COMMAND(word, POW)
			CHECK_COMMAND(word, END)
			CHECK_COMMAND(word, DUMP)
			CMD_NONE;

		switch (c)
		{
		case CMD_PUSH:
			cond = fscanf(strin, "%s", push_word);
			VERIFY(cond);
			cond = cpu_catch_error(strout, my_cpu, cpu_push(my_cpu, push_word));
			//if (cond == CPU_ERROR_CATCHER_BAD) VERIFY(!"ERROR HAS BEEN CAUGHT");
			if (cond == CPU_ERROR_PUSH_BAD_TOKEN) 
			{
				fprintf(strout, "\nPUSH BAD TOKEN [%s]\n", push_word);
				break;
			}

			break;
		case CMD_POP:
			cond = cpu_catch_error(strout, my_cpu, cpu_pop(strout, my_cpu, &temp));
			//if (cond == CPU_ERROR_CATCHER_BAD) VERIFY(!"ERROR HAS BEEN CAUGHT");
			break;
		case CMD_ADD:
			cond = cpu_catch_error(strout, my_cpu, cpu_add(my_cpu));
			//if (cond == CPU_ERROR_CATCHER_BAD) VERIFY(!"ERROR HAS BEEN CAUGHT");
			break;
		case CMD_SUB:
			cond = cpu_catch_error(strout, my_cpu, cpu_sub(my_cpu));
			//if (cond == CPU_ERROR_CATCHER_BAD) VERIFY(!"ERROR HAS BEEN CAUGHT");
			break;
		case CMD_MUL:
			cond = cpu_catch_error(strout, my_cpu, cpu_mul(my_cpu));
			//if (cond == CPU_ERROR_CATCHER_BAD) VERIFY(!"ERROR HAS BEEN CAUGHT");
			break;
		case CMD_DIV:
			cond = cpu_catch_error(strout, my_cpu, cpu_div(my_cpu));
			//if (cond == CPU_ERROR_CATCHER_BAD) VERIFY(!"ERROR HAS BEEN CAUGHT");
			break;
		case CMD_SIN:
			cond = cpu_catch_error(strout, my_cpu, cpu_sin(my_cpu));
			//if (cond == CPU_ERROR_CATCHER_BAD) VERIFY(!"ERROR HAS BEEN CAUGHT");
			break;
		case CMD_COS:
			cond = cpu_catch_error(strout, my_cpu, cpu_cos(my_cpu));
			//if (cond == CPU_ERROR_CATCHER_BAD) VERIFY(!"ERROR HAS BEEN CAUGHT");
			break;
		case CMD_TAN:
			cond = cpu_catch_error(strout, my_cpu, cpu_tan(my_cpu));
			//if (cond == CPU_ERROR_CATCHER_BAD) VERIFY(!"ERROR HAS BEEN CAUGHT");
			break;
		case CMD_SQRT:
			cond = cpu_catch_error(strout, my_cpu, cpu_sqrt(my_cpu));
			//if (cond == CPU_ERROR_CATCHER_BAD) VERIFY(!"ERROR HAS BEEN CAUGHT");
			break;
		case CMD_POW:
			cond = cpu_catch_error(strout, my_cpu, cpu_pow(my_cpu));
			//if (cond == CPU_ERROR_CATCHER_BAD) VERIFY(!"ERROR HAS BEEN CAUGHT");
			break;
		case CMD_DUMP:
			cond = cpu_catch_error(strout, my_cpu, cpu_dump(strout, my_cpu));
			//if (cond == CPU_ERROR_CATCHER_BAD) VERIFY(!"ERROR HAS BEEN CAUGHT");
			break;
		case CMD_END:
			return 0;
		default:
			fprintf(strout, "WRONG TOKEN [%s]\n", word);
			break;
		}
		cond = cpu_check(my_cpu);
		VERIFY(cond == CPU_CHECK_OK);
	}
}


