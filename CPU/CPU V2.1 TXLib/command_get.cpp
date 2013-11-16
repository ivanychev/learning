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
	CMD_SPACE = 1014,
	CMD_ENTER = 1015,
	CMD_TAB = 1016,
	CMD_OUT = 1017,
	CMD_ERROR = 1019,
};

#define CHECK_COMMAND(str, name) (strcmp((_strupr(str)), #name) == 0)? CMD_##name : 

#define CASE_COMMAND(cmd, func)																	\
		case (cmd):																				\
		cond = (*error_catcher)(strerr, my_cpu, cpu_##func);									\
			if (cond == CPU_ERROR_CATCHER_BAD) return CALC_BAD;									\
			break;

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|


/**
		calculator					the first thing my cpu has to do is to solve Reverse Polish notation expressions.
									This functions scans the input file stream for basic set of commands and arguments
									and proceeds operations with numbers using th cpu
		@param[out]		strin		input file stream
		@param[out]		strerr		output file stream
		@param[out]		my_cpu		pointer if initialized cpu

		@return						0
**/


int calculator(FILE* strin, FILE* strout, FILE* strerr, cpu* my_cpu, double* value, int (*error_catcher) (FILE* strerr, cpu* my_cpu, int error_code))
{
	VERIFY(my_cpu != NULL);
	const char MAXLINE = 10;
	char word[MAXLINE] = {};
	const char PUSH_MAXLINE = 50;
	char push_word[PUSH_MAXLINE] = {};
	int c = 0;

	double out = 0;
	//bool popped_value = false;
	int cond = 0;

	while (true)
	{
		cond = cpu_check(my_cpu);
		VERIFY(cond == CPU_CHECK_OK);
		
		cond = fscanf(strin,"%s", &word);
		if (cond == 0) return CALC_BAD;

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
			CHECK_COMMAND(word, ENTER)
			CHECK_COMMAND(word, TAB)
			CHECK_COMMAND(word, SPACE)
			CHECK_COMMAND(word, OUT)
			CMD_NONE;

		switch (c)
		{
		case CMD_PUSH:
			cond = fscanf(strin, "%s", push_word);
			if (cond == 0) return CALC_BAD;
			cond = (*error_catcher)(strerr, my_cpu, cpu_push(my_cpu, push_word));
			if (cond == CPU_ERROR_PUSH_BAD_TOKEN) 
			{
				fprintf(strerr, "\nPUSH BAD TOKEN [%s]\n", push_word);
				break;
			}
			if (cond == CPU_ERROR_CATCHER_BAD) return CALC_BAD;

			break;

		CASE_COMMAND(CMD_POP,	pop(my_cpu, value));/* *value = (out*/
		CASE_COMMAND(CMD_ADD,	add(my_cpu));
		CASE_COMMAND(CMD_SUB,	sub(my_cpu));
		CASE_COMMAND(CMD_MUL,	mul(my_cpu));
		CASE_COMMAND(CMD_DIV,	div(my_cpu));
		CASE_COMMAND(CMD_SIN,	sin(my_cpu));
		CASE_COMMAND(CMD_COS,	cos(my_cpu));
		CASE_COMMAND(CMD_TAN,	tan(my_cpu));
		CASE_COMMAND(CMD_SQRT,	sqrt(my_cpu));
		CASE_COMMAND(CMD_POW,	pow(my_cpu));
		CASE_COMMAND(CMD_DUMP,	dump(strerr, my_cpu));
		CASE_COMMAND(CMD_ENTER,	enter(strout, my_cpu));
		CASE_COMMAND(CMD_SPACE,	space(strout, my_cpu));
		CASE_COMMAND(CMD_TAB,	tab(strout, my_cpu));
		CASE_COMMAND(CMD_OUT,	out(strin, strout, strerr, my_cpu));
		case CMD_END:
			return CALC_OK;
			break;
		default:
			fprintf(strerr, "WRONG TOKEN [%s]\n", word);
			break;
		}
		cond = cpu_check(my_cpu);
		VERIFY(cond == CPU_CHECK_OK);
	}
}




		//case CMD_POP:
			//cond = (*error_catcher)(strerr, my_cpu, cpu_pop(strout, my_cpu, &out));
			//if (cond == CPU_ERROR_CATCHER_BAD) return CALC_BAD;
/*
		case CMD_SUB:
			cond = (*error_catcher)(strerr, my_cpu, cpu_sub(my_cpu));
			if (cond == CPU_ERROR_CATCHER_BAD) return CALC_BAD;
			break;
		case CMD_MUL:
			cond = (*error_catcher)(strerr, my_cpu, cpu_mul(my_cpu));
			if (cond == CPU_ERROR_CATCHER_BAD) return CALC_BAD;
			break;
		case CMD_DIV:
			cond = (*error_catcher)(strerr, my_cpu, cpu_div(my_cpu));
			if (cond == CPU_ERROR_CATCHER_BAD) return CALC_BAD;
			break;
		case CMD_SIN:
			cond = (*error_catcher)(strerr, my_cpu, cpu_sin(my_cpu));
			if (cond == CPU_ERROR_CATCHER_BAD) return CALC_BAD;
			break;
		case CMD_COS:
			cond = (*error_catcher)(strerr, my_cpu, cpu_cos(my_cpu));
			if (cond == CPU_ERROR_CATCHER_BAD) return CALC_BAD;
			break;
		case CMD_TAN:
			cond = (*error_catcher)(strerr, my_cpu, cpu_tan(my_cpu));
			if (cond == CPU_ERROR_CATCHER_BAD) return CALC_BAD;
			break;
		case CMD_SQRT:
			cond = (*error_catcher)(strerr, my_cpu, cpu_sqrt(my_cpu));
			if (cond == CPU_ERROR_CATCHER_BAD) return CALC_BAD;
			break;
		case CMD_POW:
			cond = (*error_catcher)(strerr, my_cpu, cpu_pow(my_cpu));
			if (cond == CPU_ERROR_CATCHER_BAD) return CALC_BAD;
			break;
			
		case CMD_DUMP:
			cond = (*error_catcher)(strerr, my_cpu, cpu_dump(strerr, my_cpu));
			if (cond == CPU_ERROR_CATCHER_BAD) return CALC_BAD;
			break;
			

		case CMD_SPACE:
			cond = (*error_catcher)(strerr, my_cpu, cpu_space(strout, my_cpu));
			if (cond == CPU_ERROR_CATCHER_BAD) return CALC_BAD;
			break;
		case CMD_ENTER:
			cond = (*error_catcher)(strerr, my_cpu, cpu_enter(strout, my_cpu));
			if (cond == CPU_ERROR_CATCHER_BAD) return CALC_BAD;
			break;
		case CMD_TAB:
			cond = (*error_catcher)(strerr, my_cpu, cpu_tab(strout, my_cpu));
			if (cond == CPU_ERROR_CATCHER_BAD) return CALC_BAD;
			break;
			*/

			//case CMD_ADD:
			//cond = (*error_catcher)(strerr, my_cpu, cpu_add(my_cpu));
			//if (cond == CPU_ERROR_CATCHER_BAD) return CALC_BAD;
			//break;


