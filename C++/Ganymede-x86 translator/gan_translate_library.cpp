
/**
		@file				gan_translate_library.cpp

		@par				This library is one of the key things in translation which is aimed to
							finish building code located in Command structures of Code object. There's
							a little DSL there.

							Each function has one argument - unsigned integer which is the number of Command
							object, analysing in function.

							PTR(NUM)	- the pointer of NUM'th byte, located in x86_translation array of the Command.
							VALUE(NUM)	- the value, contained in NUM'th cell of double Ganymede command array
							ADDR(NUM)	- the address in virtual memory space of executing translation of NUM'th byte in
										  x86_translation
							STREAM		- often, stream arguments of Ganymede commands are located in the second cell of 
										  Ganymede commands array. This macros get's it and translates it into the address
										  in memory space
							EQUAL(v1, v2)
										- equals to (abs((v1) - (v2)) < DBL_EPSILON)
**/



#include "exception.h"
#include "command.h"
#include "Code.h"

#define _I(name) &Code::##name##_translate,


typedef void (Code::*tr_func)(unsigned number);

tr_func translation_funcs [] =
{
#include "Ganymede_instructions.h"
};
#undef _I(name)

const char* PATCH_FAILED = "Patching failed";

#define CMD command_array[number]
#define	CHECK_CMD(num) RT_ASSERT(CMD -> check(), #num " command is broken");
#define CHECK CHECK_CMD(number);
//----------------------------------------------------------------------------------------------------------------------
#define VALUE(num) (command_array[number] -> gan_codes[num])
#define PTR(num) (char*)(&(command_array[number] -> x86_codes[num]))
#define STREAM get_stream_address(VALUE(1), VALUE(2))
#define ADDR(offset)	command_array[number] -> x86_address + offset

//----------------------------------------------------------------------------------------------------------------------


//is it good?
#define _IF(gan_stream, address)			\
if (EQUAL(stream, gan_stream))				\
{											\
	addr = address;							\
	goto get_stream_label;					\
}											\


unsigned get_stream_address(double stream, double variable)
{
	unsigned offset = 0;
	unsigned addr   = 0;

	_IF(STR_ax, (AX));
	_IF(STR_bx, (BX));
	_IF(STR_cx, (CX));
	_IF(STR_dx, (DX));
	try
	{
	_IF(STR_var, var_address(variable));
	}

	CATCH_IV("Variable address calculate failure");

	
get_stream_label:
	LG_ASSERT(addr > 0, "Address search failed");
	return addr;
}

#undef _IF

#define EMPTY_CHANGE_FUNCS(func)					\
	void Code::##func##_translate(unsigned number)	\
{													\
	CHECK;											\
};													\



EMPTY_CHANGE_FUNCS(NONE);

//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------


void Code::PUSH_translate(unsigned number)
{
	CHECK;
	if (EQUAL(VALUE(1), STR_value))
	{
		*(double*)(PTR(2)) = VALUE(2);				//be attentive
		CALL(patch_dword(ADDR(2), PTR(12)), PATCH_FAILED); 
	}
	else
	{		
	CALL(patch_dword(STREAM, PTR(2)), PATCH_FAILED);
	}	
	CHECK;
}
//----------------------------------------------------------------------------------------------------------------------

void Code::POP_translate(unsigned number)
{
	CHECK;
	CALL(patch_dword(STREAM, PTR(2)), PATCH_FAILED);
}
//----------------------------------------------------------------------------------------------------------------------


EMPTY_CHANGE_FUNCS(ADD);
EMPTY_CHANGE_FUNCS(SUB);
EMPTY_CHANGE_FUNCS(MUL);
EMPTY_CHANGE_FUNCS(DIV);
EMPTY_CHANGE_FUNCS(SIN);
EMPTY_CHANGE_FUNCS(COS);
EMPTY_CHANGE_FUNCS(TAN);
EMPTY_CHANGE_FUNCS(SQRT);

//----------------------------------------------------------------------------------------------------------------------

void Code::POW_translate(unsigned number)
{
	CHECK;
	CALL(patch_dword(DI,	 PTR(2)),		PATCH_FAILED);
	CALL(patch_dword(SI,	 PTR(8)),		PATCH_FAILED);
	CALL(patch_dword(DI + 4, PTR(14)),		PATCH_FAILED);
	CALL(patch_dword(DI,	 PTR(20)),		PATCH_FAILED);
	CALL(patch_dword(SI + 4, PTR(26)),		PATCH_FAILED);
	CALL(patch_dword(SI,	 PTR(32)),		PATCH_FAILED);
	CALL(patch_jmp_offset(	 ADDR(36), POW, PTR(37)), PATCH_FAILED);
}

//----------------------------------------------------------------------------------------------------------------------


void Code::END_translate(unsigned number)
{
	CHECK;
	CALL(patch_jmp_offset(ADDR(2), EXITPROCESS, PTR(3)), PATCH_FAILED);
}

//----------------------------------------------------------------------------------------------------------------------


#define SPACEENTERTAB(name)											\
void Code::##name##_translate(unsigned number)						\
{																	\
	CHECK;															\
	CALL(patch_dword(name, PTR(1)), PATCH_FAILED);					\
	CALL(patch_jmp_offset(ADDR(5), PRINTF, PTR(6)), PATCH_FAILED);	\
}																	\

SPACEENTERTAB(SPACE)
SPACEENTERTAB(ENTER)
SPACEENTERTAB(TAB)

//----------------------------------------------------------------------------------------------------------------------

void Code::OUT_translate(unsigned number)
{
	CHECK;
	if (EQUAL(VALUE(1), STR_ch))
	{
		unsigned char ch_out = (unsigned char)(VALUE(2));
		*(PTR(1)) =   ch_out;
		CALL(patch_jmp_offset(ADDR(3), PUTCHAR, PTR(4)), PATCH_FAILED);
	}
	else
		if	(EQUAL(VALUE(1), STR_st))
		{
			CALL(patch_dword(DI,  PTR(2)), PATCH_FAILED);
			CALL(patch_dword(DI+4,PTR(8)), PATCH_FAILED);
			CALL(patch_dword(DI,  PTR(14)),PATCH_FAILED);
			CALL(patch_dword(FIO, PTR(19)),PATCH_FAILED);
			CALL(patch_jmp_offset(ADDR(23), PRINTF, PTR(24)), PATCH_FAILED);
		}
		else
		{
			unsigned str = 0;
			CALL(str = STREAM, PATCH_FAILED);
			CALL(patch_dword(str + 4,		PTR(2)), PATCH_FAILED);
			CALL(patch_dword(str,			PTR(8)), PATCH_FAILED);
			CALL(patch_dword(FIO,			PTR(13)),PATCH_FAILED);
			CALL(patch_jmp_offset(ADDR(17), PRINTF, PTR(18)), PATCH_FAILED);
		}
}

//----------------------------------------------------------------------------------------------------------------------


void Code::MOV_translate(unsigned number)
{
	CHECK;
	if (EQUAL(VALUE(1), STR_value))
	{
		*(double*)(PTR(2)) = VALUE(2);
		CALL(patch_dword(ADDR(2), PTR(12)), PATCH_FAILED);
		CALL(patch_dword(get_stream_address(VALUE(3), 0.0), PTR(18)), PATCH_FAILED);
	}
	else
	{
		CALL(patch_dword(STREAM, PTR(2)), PATCH_FAILED);
		CALL(patch_dword(get_stream_address(VALUE(2), 0.0), PTR(8)), PATCH_FAILED);
	}
}

//----------------------------------------------------------------------------------------------------------------------

EMPTY_CHANGE_FUNCS(SWAP);
EMPTY_CHANGE_FUNCS(DUB);

//----------------------------------------------------------------------------------------------------------------------


void Code::JMP_translate(unsigned number)
{
	CHECK;
	CALL(patch_to_gan(this, PTR(1), VALUE(1), ADDR(0)), PATCH_FAILED);
}

//----------------------------------------------------------------------------------------------------------------------


void Code::conditional_jumps_common(unsigned number)
{
	CHECK;
	CALL(patch_dword(UNEQU, PTR(8)), PATCH_FAILED);
	CALL(patch_jmp_offset(ADDR(2), FLOAT_ERROR, PTR(23)), PATCH_FAILED);
}

//----------------------------------------------------------------------------------------------------------------------

#define COND2_JUMP(name, cond1, cond2)													\
void Code::##name##_translate(unsigned number)											\
{																						\
	CHECK;conditional_jumps_common(number);													\
	unsigned begin = 27;																\
																						\
	CALL(patch_dword(cond1, PTR(begin + 6)), PATCH_FAILED);								\
	CALL(patch_to_gan(this, PTR(begin + 12), VALUE(1), ADDR(begin + 11)), PATCH_FAILED);\
																						\
	begin += 16;																		\
																						\
	CALL(patch_dword(cond2, PTR(begin + 6)), PATCH_FAILED);								\
	CALL(patch_to_gan(this, PTR(begin + 12), VALUE(1), ADDR(begin + 11)), PATCH_FAILED);\
}																						\

COND2_JUMP(JBE, BELOW, EQUALL);
COND2_JUMP(JAE, ABOVE, EQUALL);

//----------------------------------------------------------------------------------------------------------------------

#define COND1_JUMP(name, cond1)															\
void Code::##name##_translate(unsigned number)											\
{																						\
	conditional_jumps_common(number);													\
	unsigned begin = 27;																\
																						\
	CALL(patch_dword(cond1, PTR(begin + 6)), PATCH_FAILED);								\
	CALL(patch_to_gan(this, PTR(begin + 12), VALUE(1), ADDR(begin + 11)), PATCH_FAILED);\
}
//	CALL(patch_to_gan(this, PTR(1), VALUE(1), ADDR(0)), PATCH_FAILED);

COND1_JUMP(JA,  ABOVE);
COND1_JUMP(JB,  BELOW);
COND1_JUMP(JE,  EQUALL);
COND1_JUMP(JNE, EQUALL);

//----------------------------------------------------------------------------------------------------------------------
EMPTY_CHANGE_FUNCS(ERROR);
EMPTY_CHANGE_FUNCS(FUNC);
//----------------------------------------------------------------------------------------------------------------------

void Code::CALL_translate(unsigned number)
{
	CHECK;
	CALL(patch_to_gan(this, PTR(1), VALUE(1), ADDR(0)), PATCH_FAILED);
}
//----------------------------------------------------------------------------------------------------------------------

void Code::ASIN_translate(unsigned number)
{
	CHECK;
	CALL(patch_dword(DI, PTR(2)),  PATCH_FAILED);
	CALL(patch_dword(DI, PTR(8)),  PATCH_FAILED);
	CALL(patch_dword(DI, PTR(14)), PATCH_FAILED);
	CALL(patch_dword(DI, PTR(28)), PATCH_FAILED);
}

//----------------------------------------------------------------------------------------------------------------------

EMPTY_CHANGE_FUNCS(LN);
EMPTY_CHANGE_FUNCS(DEF);
EMPTY_CHANGE_FUNCS(FAC);
EMPTY_CHANGE_FUNCS(RET);
EMPTY_CHANGE_FUNCS(DUMP);

//----------------------------------------------------------------------------------------------------------------------

					
void Code::IN_translate(unsigned number)
{
	CHECK;
	if (!(EQUAL(VALUE(1), STR_st)))
	{
	CALL(patch_dword(get_stream_address(VALUE(1), 0.0), PTR(1)), PATCH_FAILED);
	CALL(patch_dword(FIO, PTR(6)), PATCH_FAILED);
	CALL(patch_jmp_offset(ADDR(10), SCANF, PTR(11)), PATCH_FAILED);
	}
	else
	{
	CALL(patch_dword(DI, PTR(1)), PATCH_FAILED);
	CALL(patch_dword(FIO, PTR(6)), PATCH_FAILED);
	CALL(patch_jmp_offset(ADDR(10), SCANF, PTR(11)), PATCH_FAILED);
	CALL(patch_dword(DI, PTR(20)), PATCH_FAILED);
	}
}

//----------------------------------------------------------------------------------------------------------------------

const char JMP_CMD_LENGTH = 5;

#define BIN_OUT(ptr, count)									\
for (int i = 0; i < count; ++i) printf("%02hhx ", ptr[i]);	\
putchar('\n');		

unsigned char* Code::first_jump_patch() const
{
	unsigned char* JMP_AND_VARS = NULL;
	CALL(JMP_AND_VARS = new unsigned char[JMP_CMD_LENGTH], "Allocation failed");
	memset(JMP_AND_VARS, 0, JMP_CMD_LENGTH);

	JMP_AND_VARS[0] = 0xE9;								// JMP_COMMAND
	CALL(patch_jmp_offset(FIRST_JUMP_ADDR, CODE_BEGIN, (char*)(&(JMP_AND_VARS[1]))), "Failed to patch the head");
	
	BIN_OUT(JMP_AND_VARS, 5);
	return JMP_AND_VARS;
}

//----------------------------------------------------------------------------------------------------------------------
