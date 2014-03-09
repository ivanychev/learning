#include "cpu.h"
#include "command_codes.h"



#define RUN_AND_VERIFY(func)											\
if (error_catcher(strerr, func) != ASM_ERROR_CATCHER_OK)				\
{																		\
	free(codes);														\
	return NULL;														\
}

#define READ_WORD_														\
		int cond = fscanf(strin, "%s", word /*, CMD_MAXLEN*/);				\
		if (cond <= 0) (*error_catcher)(strerr, ASM_SCAN_FAILED);



/**
		assemble					function builds the array of commands and their arguments reading and analysing the input file stream

		param[out]		strin		input file stream
		param[out]		strerr		error file stream
		param[out]		pts			the array of pointers

		return						pointer of commands double array if successfull, otherwise NULL
**/

double* assemble(FILE* strin, FILE* strerr, pointer* pts, var* vars, int (*error_catcher)(FILE* strerr, int cond))
{
	VERIFY(strin  != NULL);
	VERIFY(strerr != NULL);

	double* codes = (double*) calloc(MAXCODES, sizeof(codes[0]));
	int cur_code = 0;
	char word[CMD_MAXLEN] = {};
	int c = 0;
	int ret_mark = 0;

	while (true)
	{
		READ_WORD_;

		if ((word[0] == ':')||(strcmp(_strlwr(word), "func") == 0))
			ret_mark = asm_is_mrk(strin, strerr, word, &cur_code, pts, (*error_catcher));

	switch (ret_mark)
	{
	case ASM_NOT_MARK:
		ret_mark = 0;
		break;
	case ASM_ERROR_CATCHER_OK:
		ret_mark = 0;
		continue;
		break;
	case ASM_ERROR_CATCHER_BAD:
		free(codes);
		return NULL;
		break;
	default:
		break;
	}

		_strupr(word);

		RUN_AND_VERIFY(asm_cmd_convert(word, &c));

		asm_push_code(codes, &cur_code, c);

		switch (c)
		{
		case CMD_DEF:
			RUN_AND_VERIFY(asm_cmd_def(strin, vars, codes, &cur_code));
			break;
		case CMD_PUSH:
			RUN_AND_VERIFY(asm_cmd_push(strin, vars, codes, &cur_code));
			break;
		case CMD_IN:
			RUN_AND_VERIFY(asm_cmd_in(strin, codes, &cur_code));
			break;
		case CMD_OUT:
			RUN_AND_VERIFY(asm_cmd_out(strin, codes, &cur_code));
			break;
		case CMD_MOV:
			RUN_AND_VERIFY(asm_cmd_mov(strin, codes, &cur_code));
			break;
		case CMD_POP:
			RUN_AND_VERIFY(asm_cmd_pop(strin, vars, codes, &cur_code));
			break;
		case CMD_JMP:
		case CMD_JBE:
		case CMD_JB:
		case CMD_JAE:
		case CMD_JA:
		case CMD_JE:
		case CMD_JNE:
		case CMD_CALL:
			RUN_AND_VERIFY(asm_cmd_jump_like(strin, codes, &cur_code, c, pts));
			break;
		case CMD_END:
			RUN_AND_VERIFY(asm_push_code(codes, &cur_code, CMD_END));
			return codes;
			break;
		default:
			break;
		}
	}
	free(codes);
	return NULL;
}

#undef CONVERT_REG_
#undef CHECK_CUR_CODE_
