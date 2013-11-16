#include "cpu.h"


//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|


enum commands
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
	CMD_MOV = 1018,
	CMD_SWAP = 1019,
	CMD_DUB = 1020,
	CMD_ERROR = 1021,

};

#define CHECK_COMMAND(str, name) (strcmp(str, #name) == 0)? CMD_##name : 

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

#define CONVERT_REG_(word, reg) (strcmp(word, #reg) == 0)? STR_##reg:

int calculator(FILE* strin, FILE* strout, FILE* strerr, cpu* my_cpu, double* value, int (*error_catcher) (FILE* strerr, cpu* my_cpu, int error_code))
{
	VERIFY(my_cpu != NULL);
	VERIFY(strin  != NULL);
	VERIFY(strout != NULL);
	VERIFY(strerr != NULL);

	const char MAXLINE = 50;
	char word[MAXLINE] = {};
	int c = 0;

	double out = 0;
	//bool popped_value = false;
	int cond = 0;
	int reg = 0;
	int is_value = 0;
	double push_value = 0;
	char push_word[MAXLINE] = {};
	char pop_word[MAXLINE] = {};
	char out_word[MAXLINE] = {};
	char mov_word1 [MAXLINE] = {};
	char mov_word2 [MAXLINE] = {};
	double mov_value = 0;
	int mov_arg1 = 0;
	int mov_arg2 = 0;


	while (true)
	{
		cond = cpu_check(my_cpu);
		VERIFY(cond == CPU_CHECK_OK);
		
		cond = fscanf(strin,"%s", &word);
		if (cond == 0) 
		{
			fprintf(strerr, "\nUnexpected end of input\n");
			return CALC_BAD;
		}
		_strupr(word);
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
			CHECK_COMMAND(word, MOV)
			CHECK_COMMAND(word, SWAP)
			CHECK_COMMAND(word, DUB)
			CMD_NONE;

		switch (c)
		{
		case CMD_PUSH:

			cond = fscanf(strin, "%s", push_word);
			if (cond == 0) return CALC_BAD;
			push_value = 0;
			is_value = sscanf(push_word, "%lg", &push_value);
			if (is_value)
				cond = cpu_catch_error(strerr, my_cpu, cpu_push(my_cpu, STR_value, push_value));
			else
			{
				_strlwr(push_word);
				reg =		CONVERT_REG_(push_word, ax)
							CONVERT_REG_(push_word, bx)
							CONVERT_REG_(push_word, cx)
							CONVERT_REG_(push_word, dx)
							STR_NON;
				cond = cpu_catch_error(strerr, my_cpu, cpu_push(my_cpu, reg));
			}

			if (cond == CPU_ERROR_CATCHER_BAD) return CALC_BAD;
			break;

		case CMD_POP:
			
			cond = fscanf(strin, "%s", pop_word);
			if (cond == 0) return CALC_BAD;
			_strlwr(pop_word);
			reg =		CONVERT_REG_(pop_word, ax)
							CONVERT_REG_(pop_word, bx)
							CONVERT_REG_(pop_word, cx)
							CONVERT_REG_(pop_word, dx)
							CONVERT_REG_(pop_word, out)
							STR_NON;
			cond = cpu_catch_error(strerr, my_cpu, cpu_pop(my_cpu, reg, value));
			if (cond == CPU_ERROR_CATCHER_BAD) return CALC_BAD;
			break;

		case CMD_OUT:
			
			cond = fscanf(strin, "%s", out_word);
			if (cond == 0) return CALC_BAD;
			_strlwr(out_word);
			reg =			CONVERT_REG_(out_word, ax)
							CONVERT_REG_(out_word, bx)
							CONVERT_REG_(out_word, cx)
							CONVERT_REG_(out_word, dx)
							CONVERT_REG_(out_word, st)
							CONVERT_REG_(out_word, ch)
							STR_NON;
			if (reg == STR_ch) 
			{
				int out_char = -1;
				cond = fscanf(strin, "%d", &out_char);
				if (cond == 0)
				{
					fprintf(strerr, "\nBad argument of OUT CH\n");
					return CALC_BAD;
				}
				cond = cpu_catch_error(strerr, my_cpu, cpu_out(strout, strerr, my_cpu, reg, out_char));
			}
			else cond = cpu_catch_error(strerr, my_cpu, cpu_out(strout, strerr, my_cpu, reg));
			if (cond == CPU_ERROR_CATCHER_BAD) return CALC_BAD;
			break;

		case CMD_MOV:
			

			cond = fscanf(strin, "%s", mov_word1);
			if (cond == 0) return CALC_BAD;

			cond = fscanf(strin, "%s", mov_word2);
			if (cond == 0) return CALC_BAD;

			mov_arg1 =		CONVERT_REG_(mov_word1, ax)
							CONVERT_REG_(mov_word1, bx)
							CONVERT_REG_(mov_word1, cx)
							CONVERT_REG_(mov_word1, dx)
							STR_NON;
			mov_value = 0;

			cond = sscanf(mov_word2, "%lg", &mov_value);
			if (cond != 0)	
				mov_arg2 = STR_value;
			else
				mov_arg2 =	CONVERT_REG_(mov_word2, ax)
							CONVERT_REG_(mov_word2, bx)
							CONVERT_REG_(mov_word2, cx)
							CONVERT_REG_(mov_word2, dx)
							STR_NON;
			cond = cpu_catch_error(strerr, my_cpu, cpu_mov(my_cpu, mov_arg1, mov_arg2, mov_value));
			if (cond == CPU_ERROR_CATCHER_BAD) return CALC_BAD;
			break;
			
		CASE_COMMAND(CMD_SWAP,	swap(my_cpu));
		CASE_COMMAND(CMD_DUB,	dub(my_cpu));
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
			//cond = cpu_catch_error(strerr, my_cpu, cpu_pop(strout, my_cpu, &out));
			//if (cond == CPU_ERROR_CATCHER_BAD) return CALC_BAD;
/*
		case CMD_SUB:
			cond = cpu_catch_error(strerr, my_cpu, cpu_sub(my_cpu));
			if (cond == CPU_ERROR_CATCHER_BAD) return CALC_BAD;
			break;
		case CMD_MUL:
			cond = cpu_catch_error(strerr, my_cpu, cpu_mul(my_cpu));
			if (cond == CPU_ERROR_CATCHER_BAD) return CALC_BAD;
			break;
		case CMD_DIV:
			cond = cpu_catch_error(strerr, my_cpu, cpu_div(my_cpu));
			if (cond == CPU_ERROR_CATCHER_BAD) return CALC_BAD;
			break;
		case CMD_SIN:
			cond = cpu_catch_error(strerr, my_cpu, cpu_sin(my_cpu));
			if (cond == CPU_ERROR_CATCHER_BAD) return CALC_BAD;
			break;
		case CMD_COS:
			cond = cpu_catch_error(strerr, my_cpu, cpu_cos(my_cpu));
			if (cond == CPU_ERROR_CATCHER_BAD) return CALC_BAD;
			break;
		case CMD_TAN:
			cond = cpu_catch_error(strerr, my_cpu, cpu_tan(my_cpu));
			if (cond == CPU_ERROR_CATCHER_BAD) return CALC_BAD;
			break;
		case CMD_SQRT:
			cond = cpu_catch_error(strerr, my_cpu, cpu_sqrt(my_cpu));
			if (cond == CPU_ERROR_CATCHER_BAD) return CALC_BAD;
			break;
		case CMD_POW:
			cond = cpu_catch_error(strerr, my_cpu, cpu_pow(my_cpu));
			if (cond == CPU_ERROR_CATCHER_BAD) return CALC_BAD;
			break;
			
		case CMD_DUMP:
			cond = cpu_catch_error(strerr, my_cpu, cpu_dump(strerr, my_cpu));
			if (cond == CPU_ERROR_CATCHER_BAD) return CALC_BAD;
			break;
			

		case CMD_SPACE:
			cond = cpu_catch_error(strerr, my_cpu, cpu_space(strout, my_cpu));
			if (cond == CPU_ERROR_CATCHER_BAD) return CALC_BAD;
			break;
		case CMD_ENTER:
			cond = cpu_catch_error(strerr, my_cpu, cpu_enter(strout, my_cpu));
			if (cond == CPU_ERROR_CATCHER_BAD) return CALC_BAD;
			break;
		case CMD_TAB:
			cond = cpu_catch_error(strerr, my_cpu, cpu_tab(strout, my_cpu));
			if (cond == CPU_ERROR_CATCHER_BAD) return CALC_BAD;
			break;
			*/

			//case CMD_ADD:
			//cond = cpu_catch_error(strerr, my_cpu, cpu_add(my_cpu));
			//if (cond == CPU_ERROR_CATCHER_BAD) return CALC_BAD;
			//break;


