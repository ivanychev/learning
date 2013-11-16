#define _TX_ALLOW_TRACE

#include "cpu.h"

//#define IS_ZERO(x) (fabs(x) < 0.000000000001) //DBL_EPSILON ������� ��������

/**
		cpu_construct				constructs cpu struct
		@param		stack_size		the size of cpu stack
		@return						the pointer to the constructed cpu
**/
cpu* cpu_construct(int stack_size);

/**
		cpu_destruct				carefully destructs cpu, freeing the dynamic memory and poisoning everything
		@param[out]		my_cpu		destructing cpu
		@return						void
**/

void cpu_destruct(cpu* my_cpu);

/**
		cpu_check					checks whether the cpu is healthy or not
		@param[out]		my_cpu		pointer of cpu
		@return						CPU_CHECK_NULL if the pointer is null
									CPU_CHECK_INV_STACK if the cpu is invalid
									CPU_CHECK_OK if ok									
**/

int cpu_check(cpu* my_cpu);

/**
		cpu_push					pushes the input element to stack, if it is number
									if it is "ax", pushes the value of ax register
									Otherwise returns error code
		@param[out]		my_cpu		pointer of cpu
		
		@return						CPU_ERROR_STACK_FULL if the stack is full
									CPU_PUSH_INV_TOKEN if the token is invalid
									CPU_OK if it's fine									
**/
int cpu_push(cpu* my_cpu, char* input);

/**
		cpu_pop							pops one element from cpu stack, saves it to the input pointer
		@param[out]		stream			file stream
		@param[out]		my_cpu			pointer of cpu
		@param[out]		return_value	where the popped value would be saved

		@return							CPU_BROKEN_START		if the CPU is bad at the beginning
										CPU_BROKEN_FINISH		if the CPU is bad at the end
										CPU_POP_VALUE_NULL		if return_value is null
										CPU_ERROR_STACK_EMPTY	if the stack is empty
										CPU_OK					if it's fine

**/
int cpu_pop(cpu* my_cpu, double* return_value);

/**
		cpu_add							pops op2 and op1, pushes op1 + op2
		@param[out]		my_cpu			pointer of cpu
		@return							CPU_BROKEN_START		if the CPU is bad at the beginning
										CPU_BROKEN_FINISH		if the CPU is bad at the end
										CPU_NOT_ENOUGH_ARGS		if there's not enough arguments in the stack
										CPU_OK if it's fine

**/

int cpu_add(cpu* my_cpu);

/**
		cpu_mul						pops op2 and op1, pushes op1 * op2
		@param[out]		my_cpu			pointer of cpu
		@return							CPU_BROKEN_START		if the CPU is bad at the beginning
										CPU_BROKEN_FINISH		if the CPU is bad at the end
										CPU_NOT_ENOUGH_ARGS		if there's not enough arguments in the stack
										CPU_OK if it's fine

**/

int cpu_mul(cpu* my_cpu);
/**
		cpu_sub							pops op2 and op1, pushes op1 - op2
		@param[out]		my_cpu			pointer of cpu
		@return							CPU_BROKEN_START		if the CPU is bad at the beginning
										CPU_BROKEN_FINISH		if the CPU is bad at the end
										CPU_NOT_ENOUGH_ARGS		if there's not enough arguments in the stack
										CPU_OK if it's fine

**/
int cpu_sub(cpu* my_cpu);

/**
		cpu_div							pops op2 and op1, pushes op1 / op2
		@param[out]		my_cpu			pointer of cpu
		@return							CPU_BROKEN_START		if the CPU is bad at the beginning
										CPU_BROKEN_FINISH		if the CPU is bad at the end
										CPU_NOT_ENOUGH_ARGS		if there's not enough arguments in the stack
										CPU_ERROR_DIV_BY_ZERO	if op2 is zero
										CPU_OK if it's fine

**/
int cpu_div(cpu* my_cpu);

/**
		cpu_sin							pops op, pushes sin(op)
		@param[out]		my_cpu			pointer of cpu
		@return							CPU_BROKEN_START		if the CPU is bad at the beginning
										CPU_BROKEN_FINISH		if the CPU is bad at the end
										CPU_NOT_ENOUGH_ARGS		if there's not enough arguments in the stack
										CPU_OK if it's fine

**/

int cpu_sin(cpu* my_cpu);

/**
		cpu_cos							pops op, pushes cos(op)
		@param[out]		my_cpu			pointer of cpu
		@return							CPU_BROKEN_START		if the CPU is bad at the beginning
										CPU_BROKEN_FINISH		if the CPU is bad at the end
										CPU_NOT_ENOUGH_ARGS		if there's not enough arguments in the stack
										CPU_OK if it's fine

**/
int cpu_cos(cpu* my_cpu);
/**
		cpu_tan							pops op, pushes tan(op)
		@param[out]		my_cpu			pointer of cpu
		@return							CPU_BROKEN_START		if the CPU is bad at the beginning
										CPU_BROKEN_FINISH		if the CPU is bad at the end
										CPU_NOT_ENOUGH_ARGS		if there's not enough arguments in the stack
										CPU_ERROR_DIV_BY_ZERO	if cos(op) is zero
										CPU_OK if it's fine

**/

int cpu_tan(cpu* my_cpu);

/**


		cpu_sqrt						pops op, pushes sqrt(op)
		@param[out]		my_cpu			pointer of cpu
		@return							CPU_BROKEN_START		if the CPU is bad at the beginning
										CPU_BROKEN_FINISH		if the CPU is bad at the end
										CPU_NOT_ENOUGH_ARGS		if there's not enough arguments in the stack
										CPU_ERROR_SQRT_NEGATIVE if the argumen is negative
										CPU_OK if it's fine

**/

int cpu_sqrt(cpu* my_cpu);

/**
		cpu_sqrt						pops op2 and op1, pushes op1 ^ op2
		@param[out]		my_cpu			pointer of cpu
		@return							CPU_BROKEN_START		if the CPU is bad at the beginning
										CPU_BROKEN_FINISH		if the CPU is bad at the end
										CPU_NOT_ENOUGH_ARGS		if there's not enough arguments in the stack
										CPU_ERROR_SQRT_NEGATIVE if the op1 is negative
										CPU_OK if it's fine

**/


int cpu_pow(cpu* my_cpu);

/**
		cpu_catch_error					Standart error handler
										Catches the codes of errors and prints error messages to the file stream, or does nothing if everything is fine
		@param[out]		stream			file stream
		@param[out]		my_cpu			pointer of cpu
		@param			condition		error code
		@return							CPU_ERROR_CATCHER_BAD if there were errors
										CPU_ERROR_CATCHER_OK if there weren't errors
**/

int cpu_catch_error(FILE* stream, cpu* my_cpy, int condition);

/**
		cpu_dump						Proceeds dump print of the cpu
		@param[out]		stream			Output file stream
		@param[out]		my_cpu			Pointer of cpu
		@return							CPU_OK of CPU_CHECK_NULL, if the pointer is null
**/

int cpu_dump(FILE* stream, cpu* my_cpu);

/**
		cpu_mox_ax						function saves the value argument to the ax cpu register

		@param			values			saving value
		
		@return							CPU_BROKEN_START		if the CPU is bad at the beginning
										CPU_BROKEN_FINISH		if the CPU is bad at the end
										CPU_OK					if it's fine
**/
int cpu_mov_ax(cpu* my_cpu, double value);

/**
		cpu_space						function prints SPACE charecter to the output
		@param[out]			stream		output file stream
		@param[out]			my_cpu		pointer of cpu

		@return							CPU_BROKEN_START		if the CPU is bad at the beginning
										CPU_BROKEN_FINISH		if the CPU is bad at the end
										CPU_OK					if it's fine
**/

int cpu_space(FILE* stream, cpu* my_cpu);

/**
		cpu_enter						function prints ENTER charecter to the output
		@param[out]			stream		output file stream
		@param[out]			my_cpu		pointer of cpu

		@return							CPU_BROKEN_START		if the CPU is bad at the beginning
										CPU_BROKEN_FINISH		if the CPU is bad at the end
										CPU_OK					if it's fine
**/

int cpu_enter(FILE* stream, cpu* my_cpu);

/**
		cpu_tab							function prints TAB charecter to the output
		@param[out]			stream		output file stream
		@param[out]			my_cpu		pointer of cpu

		@return							CPU_BROKEN_START		if the CPU is bad at the beginning
										CPU_BROKEN_FINISH		if the CPU is bad at the end
										CPU_OK					if it's fine
**/
int cpu_tab(FILE* stream, cpu* my_cpu);

/**
		cpu_out							function prints values of stack, registers or any character from the ascii
		@param[out]			fi			input stream
		@param[out]			fo			output stream
		@param[out]			strerr		error stream
		@param[out]			my_cpu		the pointer of cpu

		@par							Syntax of out is very easy. There are four registers in cpu at the moment (1.1 Beta 2)
										out rg ax   -   printing the value of ax register
										out st		-	popping and printing the value of the first element of stack
										out ch 10	-   printing tenth character from the ascii.
		
		@return							CPU_BROKEN_START			if the CPU is bad at the beginning
										CPU_BROKEN_FINISH			if the CPU is bad at the end
										CPU_OK						if it's fine
										CPU_OUT_STREAM_IN_NULL		input stream pointer is NULL
										CPU_OUT_STREAM_OUT_NULL		output stream pointer is NULL
										CPU_OUT_STREAM_ERROR_NULL	error stream pointer is NULL
**/
int cpu_out(FILE* fi, FILE* fo, FILE* strerr, cpu* my_cpu);








cpu* cpu_construct(int stack_size)
{
	stack* constructed_stack = stack_construct(CPU_STACK_SIZE);
	VERIFY(constructed_stack);
	cpu* out_cpu = (cpu*) calloc(1, sizeof(cpu));
	VERIFY(out_cpu);
	out_cpu -> cpu_stack = stack_construct(stack_size);
	out_cpu -> ax = 0;
	VERIFY(out_cpu -> cpu_stack);
	return out_cpu;
}

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

int cpu_dump(FILE* stream, cpu* my_cpu)
{
	ASSERT(stream);
	int ret = 0;
	if (my_cpu == NULL) 
	{
		ret = fprintf(stream, "Pointer is null, no cpu\n");
		VERIFY(ret);
		return CPU_CHECK_NULL;							
	}
	fprintf(stream, "\\/ \\/ \\/ \\/ \\/ \\/ \\/ \\/ \\/ \\/ \\/ \\/ \\/ \\/ \\/ \\/\n");
	ret = fprintf(stream, "\nI'm CPU[%08x]\n", my_cpu);
	VERIFY(ret);
	int check = cpu_check(my_cpu);

	switch (check)
	{
	case (CPU_CHECK_OK):
		ret = fprintf(stream, "I'm OK\n");
		VERIFY(ret);
		break;
	case (CPU_CHECK_INV_STACK):
		ret = fprintf(stream, "I'm BAD\n");
		VERIFY(ret);
	default:
		VERIFY("CPU_CHECK ISN'T WORKING" || 0);
		break;
	}
	ret = fprintf(stream,"\nPrinting registers...\n");
	VERIFY(ret);
	ret = fprintf(stream, "ax = %lg\n", my_cpu -> ax);
	VERIFY(ret);
	fprintf(stream, "Calling dump of stack...");
	stack_dump(stream, my_cpu -> cpu_stack);
	ret = fprintf(stream, "\nCPU: end of dump\n");
	fprintf(stream, "/\\ /\\ /\\ /\\ /\\ /\\ /\\ /\\ /\\ /\\ /\\ /\\ /\\ /\\ /\\ /\\ \n");
	VERIFY(ret);
	return CPU_OK;
}


//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|



void cpu_destruct(cpu* my_cpu)
{
	//if (my_cpu == NULL) CPU_ERROR_NULL;
	stack_destruct(my_cpu -> cpu_stack);
	my_cpu -> cpu_stack = NULL;
	my_cpu -> ax = POISON;
	free(my_cpu);
}

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|


int cpu_check(cpu* my_cpu)
{
	if (my_cpu == NULL) return CPU_CHECK_NULL;
	if (stack_ok(my_cpu -> cpu_stack) == OK) return CPU_CHECK_OK;
	return CPU_CHECK_INV_STACK;
}


//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|


int cpu_push(cpu* my_cpu, char* input)
{
	if (stack_full(my_cpu -> cpu_stack) != 0) return CPU_ERROR_STACK_FULL; 
	double input_number = 0;
	if (sscanf(input, "%lg", &input_number))
	{
		stack_push(my_cpu -> cpu_stack, input_number);
		//stack_dump(stdout, my_cpu -> cpu_stack);
		return CPU_OK;
	}
	if (strcmp(_strlwr(input), "ax") == 0)
	{
		stack_push(my_cpu -> cpu_stack, my_cpu -> ax);
		return CPU_OK;
	}
	return CPU_PUSH_INV_TOKEN;
}

/*!!!!!!!!!!!!!!!!!!!
int cpu_dub(cpu* my_cpu)
{
	if (stack_full(my_cpu -> cpu_stack) != 0) return CPU_ERROR_STACK_FULL;

*/

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|


int cpu_pop(cpu* my_cpu, double* return_value)
{
	if (cpu_check(my_cpu) != CPU_CHECK_OK) return CPU_BROKEN_START;
	if (return_value == NULL) return CPU_POP_VALUE_NULL;
	if (stack_empty(my_cpu -> cpu_stack) == 1) return CPU_ERROR_STACK_EMPTY;
	
	//char dest[4] = {0};         !!!!!!!!!!!!!

	*return_value = stack_pop(my_cpu -> cpu_stack);
	
	
	if (cpu_check(my_cpu) != CPU_CHECK_OK) return CPU_BROKEN_FINISH;
	return CPU_OK;
}


enum registers_
{
	REG_NON = 900,
	REG_AX = 901,
	REG_BX = 902,
	REG_CX = 903,
	REG_DX = 904,
};

#define CHECK_REG_(word, name)	(strcmp(word, #name) == 0)? REG_##name: 	


int cpu_out(FILE* fi, FILE* fo, FILE* strerr, cpu* my_cpu)											//���������� pop ax, ������������ � ������� (����� �������� � out?)
{
	if (cpu_check(my_cpu) != CPU_CHECK_OK) return CPU_BROKEN_START;
	if (fi == NULL) return CPU_OUT_STREAM_IN_NULL;
	if (fo == NULL) return CPU_OUT_STREAM_OUT_NULL;
	if (strerr == NULL) return CPU_OUT_STREAM_ERROR_NULL;
	//int check_type = 0;
	int ret = 0;
	double out_value = 0;

	char type[4] = {0};
	fscanf(fi, "%s", type);
	
	_strlwr(type);
	
	
	
	if (strcmp(type, "st") == 0)
	{
		ret = cpu_pop(my_cpu, &out_value);
		if (ret != CPU_OK)
		{
			fprintf(strerr, "CPU_OUT: ERROR while popping\n");
			return ret;
		}
		fprintf(fo, "%lg", out_value);
		if (cpu_check(my_cpu) != CPU_CHECK_OK) return CPU_BROKEN_FINISH;
		return CPU_OK;
	}



	if (strcmp(type, "rg") == 0)
	{
		char reg[4] = {0};
		fscanf(fi, "%s", reg);
		_strupr(reg);
		int reg_number =	CHECK_REG_(reg, AX)
							CHECK_REG_(reg, BX)
							CHECK_REG_(reg, CX)
							CHECK_REG_(reg, DX)
							REG_NONE;
		switch (reg_number)
		{
		case REG_AX:
			fprintf(fo, "%lg", my_cpu -> ax);
			if (cpu_check(my_cpu) != CPU_CHECK_OK) return CPU_BROKEN_FINISH;
			return CPU_OK;
		case REG_BX:
			fprintf(fo, "%lg", my_cpu -> bx);
			if (cpu_check(my_cpu) != CPU_CHECK_OK) return CPU_BROKEN_FINISH;
			return CPU_OK;
		case REG_CX:
			fprintf(fo, "%lg", my_cpu -> cx);
			if (cpu_check(my_cpu) != CPU_CHECK_OK) return CPU_BROKEN_FINISH;
			return CPU_OK;
		case REG_DX:
			fprintf(fo, "%lg", my_cpu -> dx);
			if (cpu_check(my_cpu) != CPU_CHECK_OK) return CPU_BROKEN_FINISH;
			return CPU_OK;

		case REG_NONE:
			fprintf(strerr, "CPU_OUT: ERROR: bad token [%s]", reg);
			return CPU_OUT_BAD_TOKEN;
			break;
		}
	}



	if (strcmp(type, "ch") == 0)
	{
		int chr = 0;
		ret = fscanf(fi, "%d", &chr);
		if ((ret == 0) || (! ((0 <= chr) && (chr <= 255)) ))
		{
			fprintf(strerr, "CPU_OUT: ERROR: invalid number of character");
			return CPU_OUT_BAD_TOKEN;
		}
		fputc((char)chr, fo);
		if (cpu_check(my_cpu) != CPU_CHECK_OK) return CPU_BROKEN_FINISH;
		return CPU_OK;
	}

	fprintf(strerr, "cpu_out: ERROR: bad type token [%s]\n", type);
	return CPU_OUT_BAD_TOKEN;	

}
//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|


int cpu_add(cpu* my_cpu)
{
	if (cpu_check(my_cpu) != CPU_CHECK_OK) return CPU_BROKEN_START;
	if ((my_cpu -> cpu_stack -> size) < 2) return CPU_NOT_ENOUGH_ARGS;
	double op2 = stack_pop(my_cpu -> cpu_stack);
	double op1 = stack_pop(my_cpu -> cpu_stack);

	stack_push(my_cpu -> cpu_stack, op1 + op2);
	if (cpu_check(my_cpu) != CPU_CHECK_OK) return CPU_BROKEN_FINISH;
	return CPU_OK;
}

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|


int cpu_mul(cpu* my_cpu)
{
	if (cpu_check(my_cpu) != CPU_CHECK_OK) return CPU_BROKEN_START;
	if ((my_cpu -> cpu_stack -> size) < 2) return CPU_NOT_ENOUGH_ARGS;
	double op2 = stack_pop(my_cpu -> cpu_stack);
	double op1 = stack_pop(my_cpu -> cpu_stack);

	stack_push(my_cpu -> cpu_stack, op1 * op2);
	if (cpu_check(my_cpu) != CPU_CHECK_OK) return CPU_BROKEN_FINISH;
	return CPU_OK;
}

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|


int cpu_sub(cpu* my_cpu)
{
	if (cpu_check(my_cpu) != CPU_CHECK_OK) return CPU_BROKEN_START;
	if ((my_cpu -> cpu_stack -> size) < 2) return CPU_NOT_ENOUGH_ARGS;
	double op2 = stack_pop(my_cpu -> cpu_stack);
	double op1 = stack_pop(my_cpu -> cpu_stack);
	
	stack_push(my_cpu -> cpu_stack, op1 - op2);
	if (cpu_check(my_cpu) != CPU_CHECK_OK) return CPU_BROKEN_FINISH;
	return CPU_OK;
}

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|


int cpu_div(cpu* my_cpu)
{
	if (cpu_check(my_cpu) != CPU_CHECK_OK) return CPU_BROKEN_START;
	if ((my_cpu -> cpu_stack -> size) < 2) return CPU_NOT_ENOUGH_ARGS;
	double op2 = stack_pop(my_cpu -> cpu_stack);
	if (IS_ZERO(op2))
	{
		stack_push(my_cpu -> cpu_stack, op2);
		return CPU_ERROR_DIV_BY_ZERO;
	}
	double op1 = stack_pop(my_cpu -> cpu_stack);

	stack_push(my_cpu -> cpu_stack, op1 / op2);
	if (cpu_check(my_cpu) != CPU_CHECK_OK) return CPU_BROKEN_FINISH;
	return CPU_OK;
}

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|


int cpu_sin(cpu* my_cpu)
{
	if (cpu_check(my_cpu) != CPU_CHECK_OK) return CPU_BROKEN_START;
	if (stack_empty(my_cpu -> cpu_stack))  return CPU_NOT_ENOUGH_ARGS;;
	stack_push(my_cpu -> cpu_stack, sin(stack_pop(my_cpu -> cpu_stack)));
	if (cpu_check(my_cpu) != CPU_CHECK_OK) return CPU_BROKEN_FINISH;
	return CPU_OK;
}

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|


int cpu_cos(cpu* my_cpu)
{
	if (cpu_check(my_cpu) != CPU_CHECK_OK) return CPU_BROKEN_START;
	if (stack_empty(my_cpu -> cpu_stack))  return CPU_NOT_ENOUGH_ARGS;;
	stack_push(my_cpu -> cpu_stack, cos(stack_pop(my_cpu -> cpu_stack)));
	if (cpu_check(my_cpu) != CPU_CHECK_OK) return CPU_BROKEN_FINISH;
	return CPU_OK;
}

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|


int cpu_tan(cpu* my_cpu)
{
	if (cpu_check(my_cpu) != CPU_CHECK_OK) return CPU_BROKEN_START;
	if (stack_empty(my_cpu -> cpu_stack))  return CPU_NOT_ENOUGH_ARGS;
	double op = stack_pop(my_cpu -> cpu_stack);
	if (IS_ZERO(op))
	{
		stack_push(my_cpu -> cpu_stack, op);
		return CPU_ERROR_DIV_BY_ZERO;
	}
	stack_push(my_cpu -> cpu_stack, sin(op) / cos(op));
	if (cpu_check(my_cpu) != CPU_CHECK_OK) return CPU_BROKEN_FINISH;
	return CPU_OK;
}


//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|


int cpu_sqrt(cpu* my_cpu)
{
	if (cpu_check(my_cpu) != CPU_CHECK_OK) return CPU_BROKEN_START;
	if (stack_empty(my_cpu -> cpu_stack))  return CPU_NOT_ENOUGH_ARGS;;
	double op = stack_pop(my_cpu -> cpu_stack);
	if (op < 0)
	{
		stack_push(my_cpu -> cpu_stack, op);
		return CPU_ERROR_SQRT_NEGATIVE;
	}
	stack_push(my_cpu -> cpu_stack, sqrt(op));
	if (cpu_check(my_cpu) != CPU_CHECK_OK) return CPU_BROKEN_FINISH;
	return CPU_OK;
}

//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|


int cpu_pow(cpu* my_cpu)
{
	if (cpu_check(my_cpu) != CPU_CHECK_OK) return CPU_BROKEN_START;
	if ((my_cpu -> cpu_stack -> size) < 2) return CPU_NOT_ENOUGH_ARGS;
	double op2 = stack_pop(my_cpu -> cpu_stack);
	double op1 = stack_pop(my_cpu -> cpu_stack);
	if (op1 < 0)
	{
		stack_push(my_cpu -> cpu_stack, op1);
		stack_push(my_cpu -> cpu_stack, op2);
		return CPU_ERROR_NEGATIVE_BASE;
	}

	stack_push(my_cpu -> cpu_stack, powf((float)op1, (float)op2));
	if (cpu_check(my_cpu) != CPU_CHECK_OK) return CPU_BROKEN_FINISH;
	return CPU_OK;
}


//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|


int cpu_catch_error(FILE* stream, cpu* my_cpu, int condition)
{
	switch (condition)
	{
		case CPU_OUT_STREAM_ERROR_NULL:
			fprintf(stream, "\n CPU_OUT: The error stream pointer is invalid!\n");
			return CPU_ERROR_CATCHER_BAD;
		case CPU_OUT_STREAM_IN_NULL:
			fprintf(stream, "\n CPU_OUT: The input stream pointer is invalid!\n");
			return CPU_ERROR_CATCHER_BAD;

		case CPU_OUT_STREAM_OUT_NULL:
			fprintf(stream, "\n CPU_OUT: The output stream pointer is invalid!\n");
			return CPU_ERROR_CATCHER_BAD;
		
		case CPU_OUT_BAD_TOKEN:
			fprintf(stream, "\n CPU_OUT: There's bad token argument\n");
			return CPU_ERROR_CATCHER_BAD;
		
		case CPU_CHECK_NULL:
			fprintf(stream, "\nCPU checker found out that the pointer is NULL\n");
			return CPU_ERROR_CATCHER_BAD;
			break;
		
		case CPU_CHECK_OK:			
			return CPU_ERROR_CATCHER_OK;
			break;
		
		case CPU_CHECK_INV_STACK:
			fprintf(stream, "\nCPU checker found out that something bad with CPU\n");
			cpu_dump(stream, my_cpu);
			return CPU_ERROR_CATCHER_BAD;
			break;
		
		case CPU_ERROR_STACK_FULL:
			fprintf(stream, "\nERROR: stack if full\n");
			return CPU_ERROR_CATCHER_BAD;
			break;
		
		case CPU_ERROR_STACK_EMPTY:
			fprintf(stream, "\nERROR: stack if empty\n");
			return CPU_ERROR_CATCHER_BAD;
			break;
		
		case CPU_OK:
			return CPU_ERROR_CATCHER_OK;
			break;
		
		case CPU_PUSH_INV_TOKEN:
			fprintf(stream, "\nERROR: pushed invalid token\n");
			return CPU_ERROR_PUSH_BAD_TOKEN;
			break;
		
		case CPU_BROKEN_START:
			fprintf(stream, "\nERROR: stack is bad at the beginning\n");
			cpu_dump(stream, my_cpu);
			return CPU_ERROR_CATCHER_BAD;
			break;
		
		case CPU_BROKEN_FINISH:
			fprintf(stream, "\nERROR: stack is bad at the end\n");
			cpu_dump(stream, my_cpu);
			return CPU_ERROR_CATCHER_BAD;
			break;

		case CPU_NOT_ENOUGH_ARGS:
			fprintf(stream, "\nERROR: not enough arguments\n");
			cpu_dump(stream, my_cpu);
			return CPU_ERROR_CATCHER_BAD;
			break;
		
		case CPU_POP_VALUE_NULL:
			fprintf(stream, "\nERROR: value pointer is null\n");
			return CPU_ERROR_CATCHER_BAD;
			break;
		
		case CPU_ERROR_DIV_BY_ZERO:
			fprintf(stream, "\nERROR: division by zero\n");
			cpu_dump(stream, my_cpu);
			return CPU_ERROR_CATCHER_BAD;
			break;
		
		case CPU_ERROR_NEGATIVE_BASE:
			fprintf(stream, "\nERROR: power base is negative\n");
			cpu_dump(stream, my_cpu);
			return CPU_ERROR_CATCHER_BAD;
			break;
		
		case CPU_ERROR_SQRT_NEGATIVE:
			fprintf(stream, "\nERROR: sqrt argument is negative\n");
			cpu_dump(stream, my_cpu);
			return CPU_ERROR_CATCHER_BAD;
			
			break;
		default:
			fprintf(stream, "\n!!!ERROR: INVALID ERROR SIGNATURE!!!\n");
			return CPU_ERROR_CATCHER_BAD;
			break;
	}
}


//    /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\     /\  
//   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \   /  \ 
//  /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ /    \ 
// |______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|______|

int cpu_mov_ax(cpu* my_cpu, double value)
{
	if (cpu_check(my_cpu) != CPU_CHECK_OK) return CPU_BROKEN_START;
	my_cpu -> ax = value;
	if (cpu_check(my_cpu) != CPU_CHECK_OK) return CPU_BROKEN_FINISH;
	return CPU_OK;
}

int cpu_space(FILE* stream, cpu* my_cpu)
{
	if (cpu_check(my_cpu) != CPU_CHECK_OK) return CPU_BROKEN_START;
	VERIFY(stream != NULL);
	fputc(' ', stream);
	if (cpu_check(my_cpu) != CPU_CHECK_OK) return CPU_BROKEN_FINISH;
	return CPU_OK;
}

int cpu_enter(FILE* stream, cpu* my_cpu)
{
	if (cpu_check(my_cpu) != CPU_CHECK_OK) return CPU_BROKEN_START;
	VERIFY(stream != NULL);
	fputc('\n', stream);
	if (cpu_check(my_cpu) != CPU_CHECK_OK) return CPU_BROKEN_FINISH;
	return CPU_OK;
}

int cpu_tab(FILE* stream, cpu* my_cpu)
{
	if (cpu_check(my_cpu) != CPU_CHECK_OK) return CPU_BROKEN_START;
	VERIFY(stream != NULL);
	fputc('\t', stream);
	if (cpu_check(my_cpu) != CPU_CHECK_OK) return CPU_BROKEN_FINISH;
	return CPU_OK;
}