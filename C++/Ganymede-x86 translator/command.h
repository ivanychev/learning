#ifndef COMMAND_INCLUDE_
#define COMMAND_INCLUDE_

#include "Ganymede-x86.h"






enum commands
{
	CMD_NONE  =	1000,
	CMD_PUSH  =	1001,
	CMD_POP   =	1002,
	CMD_ADD   =	1003,
	CMD_SUB   =	1004,
	CMD_MUL   =	1005,
	CMD_DIV   =	1006,
	CMD_SIN   =	1007,
	CMD_COS   =	1008,
	CMD_TAN   =	1009,
	CMD_SQRT  =	1010,
	CMD_POW   =	1011,
	CMD_END   =	1012,
	CMD_DUMP  =	1013,
	CMD_SPACE = 1014,
	CMD_ENTER = 1015,
	CMD_TAB   =	1016,
	CMD_OUT   =	1017,
	CMD_MOV   =	1018,
	CMD_SWAP  =	1019,
	CMD_DUB   =	1020,
	CMD_JMP   =	1021,
	CMD_JBE   =	1022,
	CMD_JB    =	1023,
	CMD_JAE   =	1024,
	CMD_JA    =	1025,
	CMD_JE    =	1026,
	CMD_JNE   =	1027,
	CMD_ERROR = 1028,
	CMD_FUNC  =	1029,
	CMD_CALL  =	1030,
	CMD_RET   =	1031,
	CMD_ASIN  = 1032,
	CMD_FAC   = 1033,
	CMD_LN    = 1034,
	CMD_DEF	  = 1035,
	CMD_IN    =	1036,
};


enum streams
{
	STR_NON		  =	900,
	STR_ax		  =	901,
	STR_bx   	  =	902,
	STR_cx		  =	903,
	STR_dx		  = 904,
	STR_out		  = 905,
	STR_st		  =	906,				// stack
	STR_ch		  =	907,				// char
	STR_value	  =	908,
	STR_var		  = 909,
	STR_sys_reg   =	910,
};



struct Template_command;

struct Command
{
public:

	double			gan_codes [MAXGANCOMMAND];
	unsigned int	gan_length;

	char*			x86_codes;
	unsigned int	x86_length;

	ofstream&		log_stream;

	void			get_command(ofstream& stream);
	void			translate_command();
	
	unsigned int	x86_address;
	unsigned int	gen_address;

					Command(ofstream& log);
				   ~Command();
	
	bool			load_template(const Template_command& copied);

	bool			check();
	bool			get_command(ifstream& source);

	void			print_x86(ostream& str) const;

	void			console_print_ganymede_command() const;
};

struct Template_command
{
	double			ganymede_command;
	unsigned int	ganymede_command_size;
	char*			x86_translation_template;
	unsigned int	translation_size;

	ofstream&		log_stream;
	
	//doesn't work
	//friend bool Command::operator=(const Template_command& copied);

					Template_command(double command, unsigned int size, char* translation, unsigned int translation_length, ofstream& log);
				   ~Template_command();
	void			console_dump() const;
};


/**
		@par					The data below is developed translation templates for each command of Ganymede processor, that are
								stored in binary format. The machine code have been executed from compiled by MASM32 file, where all
								of function have been written and tested. These templates don't contain any offsets or addresses, for
								obvious reasons. They will be used while initializing Command structures when Code would be getting 
								instructions from Ganymede binary file

**/

#define COND_JUMP_COMMON																											\
0xDE, 0xD9,													/*fcompp	-	comparing and popping both of numbers out*/				\
0x9B,														/*waiting for co-processor*/												\
																																	\
0xDF, 0xE0,													/*loading CX to AX register to deal with results*/						\
0x66, 0x8B, 0x3D, 0x00, 0x00, 0x00, 0x00,					/*mov di, word ptr __UNEQU*/											\
0x66, 0x23, 0xC7,											/*and ax, bx*/															\
0x66, 0x8B, 0xD8,											/*mov bx, ax*/															\
0x66, 0x33, 0xC7,											/*xor ax, di*/															\
0x0F, 0x84, 0x00/*23*/, 0x00, 0x00, 0x00					/*je __COPROC_ERROR*/													\

																														
#define JNE_PART																						\
0x66, 0x8B, 0xC3,																						\
0x66, 0x33, 0x1D, 0x00, 0x00, 0x00, 0x00,					/*one of constant flag variables*/			\
0x0F, 0x85, 0x00, 0x00, 0x00, 0x00							/*destination offset*/						\

#define NOT_JNE_PART																					\
0x66, 0x8B, 0xC3,																						\
0x66, 0x33, 0x1D, 0x00, 0x00, 0x00, 0x00,																\
0x0F, 0x84, 0x00, 0x00, 0x00, 0x00																		\



const unsigned char TR_NONE[] = {0x90};										// nop
const unsigned char TR_PUSH[] = {0xDD, 0x05, 0x00, 0x00, 0x00, 0x00};		// fld real8 ptr ...
const unsigned char TR_PUSH_VAL[] = {	
								 0xEB, 0x08,								// JMP 8h
								 0x00, 0x00,	0x00, 0x00,	
								 0x00, 0x00, 0x00, 0x00,					// DOUBLE IS HERE
								 0xDD, 0x05, 0x00, 0x00, 0x00, 0x00
									};										// FLD it

const unsigned char TR_POP [] = {0xDD, 0x15, 0x00, 0x00, 0x00, 0x00};		// fst real8 ptr ...
const unsigned char TR_ADD [] = {0xDE, 0xC1};								// fadd
const unsigned char TR_SUB [] = {0xDE, 0xE9};								// fsub
const unsigned char TR_MUL [] = {0xDE, 0xC9};								// fmul	
const unsigned char TR_DIV [] = {0xDE, 0xF9};								// fdivr
const unsigned char TR_SIN [] = {0xD9, 0xFE};
const unsigned char TR_COS [] = {0xD9, 0xFF};
const unsigned char TR_TAN [] = {0xD9, 0xF2};
const unsigned char TR_SQRT[] = {0xD9, 0xFA};
const unsigned char TR_POW [] = {0xDD, 0x1D, 0x00, 0x00, 0x00, 0x00,		//0040101A  |. DD1D 20404000  FSTP QWORD PTR DS:[404020]
								 0xDD, 0x1D, 0x00, 0x00, 0x00, 0x00,		//00401020  |. DD1D 28404000  FSTP QWORD PTR DS:[404028]
								 0xFF, 0x35, 0x00, 0x00, 0x00, 0x00,		//00401026  |. FF35 24404000  PUSH DWORD PTR DS:[404024]
								 0xFF, 0x35, 0x00, 0x00, 0x00, 0x00,		//0040102C  |. FF35 20404000  PUSH DWORD PTR DS:[404020]
								 0xFF, 0x35, 0x00, 0x00, 0x00, 0x00,		//00401032  |. FF35 2C404000  PUSH DWORD PTR DS:[40402C]
								 0xFF, 0x35, 0x00, 0x00, 0x00, 0x00,		//00401038  |. FF35 28404000  PUSH DWORD PTR DS:[404028]
								 0xE8, 0x00, 0x00, 0x00, 0x00,				//0040103E  |. E8   15150000  CALL <JMP.&msvcrt.pow>
								 0x83, 0xC4, 0x10};							//00401043  |. 83C4 10        ADD ESP,10
const unsigned char	TR_END  []= {0x6A, 0x00,								//PUSH 0
								 0xE8, 0x00, 0x00, 0x00, 0x00};				//Call ...
const unsigned char TR_SPACE[]= {0x68, 0x00, 0x00, 0x00, 0x00,				//PUSH POINTER
								 0xE8, 0x00, 0x00, 0x00, 0x00};				//Calling printf
const unsigned char TR_ENTER[]= {0x68, 0x00, 0x00, 0x00, 0x00,				//PUSH POINTER
								 0xE8, 0x00, 0x00, 0x00, 0x00};				//Calling printf
const unsigned char TR_TAB [] = {0x68, 0x00, 0x00, 0x00, 0x00,				//PUSH POINTER
								 0xE8, 0x00, 0x00, 0x00, 0x00};				//Calling printf
const unsigned char TR_OUT [] = {0xFF, 0x35, 0x00, 0x00, 0x00, 0x00,		//0040100E  |. FF35 04404000  PUSH DWORD PTR DS:[404004]
								 0xFF, 0x35, 0x00, 0x00, 0x00, 0x00,		//00401014  |. FF35 00404000  PUSH DWORD PTR DS:[404000]               ; |
								 0x68, 0x00, 0x00, 0x00, 0x00,				//0040101A  |. 68 31404000    PUSH console_.00404031                   ; |format = "%lg"
								 0xE8, 0x00, 0x00, 0x00, 0x00,				//0040101F  |. E8 14150000    CALL <JMP.&msvcrt.printf>                ; \printf
								 0x83, 0xC4, 0x0C};							//00401024  |. 83C4 0C        ADD ESP,0C
const unsigned char TR_OUT_ST[] =
								{
								 0xDD, 0x1D, 0x00, 0x00, 0x00, 0x00,		// FSTP
								 0xFF, 0x35, 0x00, 0x00, 0x00, 0x00,		//0040100E  |. FF35 04404000  PUSH DWORD PTR DS:[404004]
								 0xFF, 0x35, 0x00, 0x00, 0x00, 0x00,		//00401014  |. FF35 00404000  PUSH DWORD PTR DS:[404000]               ; |
								 0x68, 0x00, 0x00, 0x00, 0x00,				//0040101A  |. 68 31404000    PUSH console_.00404031                   ; |format = "%lg"
								 0xE8, 0x00, 0x00, 0x00, 0x00,				//0040101F  |. E8 14150000    CALL <JMP.&msvcrt.printf>                ; \printf
								 0x83, 0xC4, 0x0C};	

const unsigned char TR_OUT_CH[]={0xB0, 0x00,								// MOV AL, Unsigned hex number we want to print
								 0x50,										// PUSH EAX
								 0xE8, 0x00, 0x00, 0x00, 0x00,				// CALL PUTCHAR
								 0x83, 0xC4, 0x04};							// ADD ESP, 4

const unsigned char TR_MOV [] = {0xDD, 0x05, 0x00, 0x00, 0x00, 0x00,		// fld to stack
								 0xDD, 0x1D, 0x00, 0x00, 0x00, 0x00};		// fstp to destination
const unsigned char TR_MOV_VAL[]=
								{
								0xEB, 0x08,									// JMP 8h
								0x00, 0x00,	0x00, 0x00,	
								0x00, 0x00, 0x00, 0x00,
								0xDD, 0x05, 0x00, 0x00, 0x00, 0x00,			// fld to stack
								0xDD, 0x1D, 0x00, 0x00, 0x00, 0x00};
const unsigned char TR_SWAP[] = {0xD9, 0xC9};								// fxch st(1)
const unsigned char TR_DUB [] = {0xD9, 0xC0};
const unsigned char TR_JMP [] = {0xE9, 0x00, 0x00, 0x00, 0x00};				// to - from - 5 (this is length of jmp instruction of x86)
const unsigned char TR_JBE_JAE  [] = {COND_JUMP_COMMON, NOT_JNE_PART, NOT_JNE_PART};
const unsigned char TR_JB_JE_JA [] = {COND_JUMP_COMMON, NOT_JNE_PART};
const unsigned char TR_JNE		[] = {COND_JUMP_COMMON, JNE_PART};
const unsigned char TR_FUNC		[] = "";
const unsigned char TR_CALL[] = {0xE8, 0x00, 0x00, 0x00, 0x00};
const unsigned char TR_RET [] = {0xC3};
const unsigned char TR_ASIN[] = {
								0xDD, 0x15, 0x00, 0x00, 0x00, 0x00,			// DI
								0xDD, 0x05, 0x00, 0x00, 0x00, 0x00,			// again DI
								0xDD, 0x05, 0x00, 0x00, 0x00, 0x00,			// and again DI
								0xDE, 0xC9,
								0xD9, 0xE8,
								0xDE, 0xE1,
								0xD9, 0xFA,
								0xDD, 0x05, 0x00, 0x00, 0x00, 0x00,			// well, you know ... DI
								0xDE, 0xF1,
								0xD9, 0xE8,
								0xD9, 0xF3
								};
const unsigned char TR_LN  [] = {
								0xD9, 0xE8,
								0xD9, 0xC9,
								0xD9, 0xF1,
								0xD9, 0xEA,
								0xDE, 0xF9
								};
const unsigned char TR_DEF  [] = "";
const unsigned char TR_IN	[] = {
								0x68, 0x00, 0x00, 0x00, 0x00,		// where to save
								0x68, 0x00, 0x00, 0x00, 0x00,		// __FIO
								0xE8, 0x00, 0x00, 0x00, 0x00,		// scanf address
								0x83, 0xC4, 0x08					// add esp, 8
								};

const unsigned char TR_IN_ST[]={
								0x68, 0x00, 0x00, 0x00, 0x00,		// where to save
								0x68, 0x00, 0x00, 0x00, 0x00,		// __FIO
								0xE8, 0x00, 0x00, 0x00, 0x00,		// scanf address
								0x83, 0xC4, 0x08,					// add esp, 8
								0xDD, 0x05, 0x00, 0x00, 0x00, 0x00
								};

/**
		@par			Static Template_command array below represents the range of command that are possible to translate 
						via Ganymede-x86. Each of them initialized with double value, which is the number of Ganymede command and
						its size and x86 template and its size.

						When CODE loads template object, it recieves the information about the size of Ganymede instruction with its
						arguments ant the template of it. The particulars will be analyzed later
**/


const Template_command GANYMEDE_INSTRUCTIONS[] =
{
	Template_command(1000, 1, (char*)TR_NONE ,		sizeof(TR_NONE),	strlog),		//NONE
	Template_command(1001, 3, (char*)TR_PUSH ,		sizeof(TR_PUSH),	strlog),		//PUSH
	Template_command(1002, 3, (char*)TR_POP  ,		sizeof(TR_POP),		strlog),		//POP
	Template_command(1003, 1, (char*)TR_ADD  ,		sizeof(TR_ADD),		strlog),		//ADD
	Template_command(1004, 1, (char*)TR_SUB  ,		sizeof(TR_SUB),		strlog),		//SUB
	Template_command(1005, 1, (char*)TR_MUL  ,		sizeof(TR_MUL),		strlog),		//MUL
	Template_command(1006, 1, (char*)TR_DIV  ,		sizeof(TR_DIV),		strlog),		//DIV
	Template_command(1007, 1, (char*)TR_SIN  ,		sizeof(TR_SIN),		strlog),		//SIN
	Template_command(1008, 1, (char*)TR_COS  ,		sizeof(TR_COS),		strlog),		//COS
	Template_command(1009, 1, (char*)TR_TAN  ,		sizeof(TR_TAN),		strlog),		//TAN
	Template_command(1010, 1, (char*)TR_SQRT ,		sizeof(TR_SQRT),	strlog),		//SQRT
	Template_command(1011, 1, (char*)TR_POW  ,		sizeof(TR_POW),		strlog),		//POW
	Template_command(1012, 1, (char*)TR_END  ,		sizeof(TR_END),		strlog),		//END
	Template_command(1013, 1, ""			 ,		0,					strlog),		//DUMP not supported
	Template_command(1014, 1, (char*)TR_SPACE,		sizeof(TR_SPACE),	strlog),		//SPACE
	Template_command(1015, 1, (char*)TR_ENTER,		sizeof(TR_ENTER),	strlog),		//ENTER
	Template_command(1016, 1, (char*)TR_TAB  ,		sizeof(TR_TAB),		strlog),		//TAB
	Template_command(1017, 3, (char*)TR_OUT  ,		sizeof(TR_OUT),		strlog),		//OUT - REMEMBER ABOUT OUT CH!!!
	Template_command(1018, 4, (char*)TR_MOV  ,		sizeof(TR_MOV),		strlog),		//MOV
	Template_command(1019, 1, (char*)TR_SWAP ,		sizeof(TR_SWAP),	strlog),		//SWAP
	Template_command(1020, 1, (char*)TR_DUB  ,		sizeof(TR_DUB),		strlog),		//DUB
	Template_command(1021, 2, (char*)TR_JMP  ,		sizeof(TR_JMP),		strlog),		//JMP
	Template_command(1022, 2, (char*)TR_JBE_JAE,	sizeof(TR_JBE_JAE), strlog),		//JBE
	Template_command(1023, 2, (char*)TR_JB_JE_JA,	sizeof(TR_JB_JE_JA),strlog),		//JB
	Template_command(1024, 2, (char*)TR_JBE_JAE,	sizeof(TR_JBE_JAE), strlog),		//JAE
	Template_command(1025, 2, (char*)TR_JB_JE_JA,	sizeof(TR_JB_JE_JA),strlog),		//JA
	Template_command(1026, 2, (char*)TR_JB_JE_JA,	sizeof(TR_JB_JE_JA),strlog),		//JE
	Template_command(1027, 2, (char*)TR_JNE,		sizeof(TR_JNE),		strlog),		//JNE
	Template_command(1028, 1, "",					0,					strlog),		//ERROR not supported
	Template_command(1029, 0, (char*)TR_FUNC ,		0,					strlog),		//FUNC
	Template_command(1030, 2, (char*)TR_CALL ,		sizeof(TR_CALL),	strlog),		//CALL
	Template_command(1031, 1, (char*)TR_RET  ,		sizeof(TR_RET),		strlog),		//RET
	Template_command(1032, 1, (char*)TR_ASIN ,		sizeof(TR_ASIN),	strlog),		//ASIN
	Template_command(1033, 1, "",					0,					strlog),		//FAC not supported
	Template_command(1034, 1, (char*)TR_LN   ,		sizeof(TR_LN),		strlog),		//LN
	Template_command(1035, 2, (char*)TR_DEF  ,		0,		strlog),					//DEF
	Template_command(1036, 2, (char*)TR_IN   ,		sizeof(TR_IN),		strlog)			//IN
};

#endif