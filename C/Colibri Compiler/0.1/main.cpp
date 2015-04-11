#include "compiler.h"

/*

Grammar V 1.1

- Removed Id, because that was useless
- Added Print and Print_val types into Op
- Now programmer is allowed only to write comparison in While, If and Do

Pgm			::= B
B			::= '{' Op+ '}'
Op			::= IfOp | AssnOp| WhileOp| DoOp| Print | Print_val';'
IfOp		::= "if" (Cmp) Op|B
AssnOp		::= V [+-/*]?' =' E
WhileOp		::= "while" (Cmp) Op|B
DoOp		::= "do" B "until" (Cmp)
Print		::= "print(" Str ")" 
Print_val	::= "print_val(" E ")" 
V			::= [A-Za-z_]
F			::=	[A-Za-z_] '('E|F {,E|F}+ ')'
E			::= T{[+-]T}*
T			::= P{[+-]T}*
P			::= [+-]+ N | V | F | '('E')'
N			::= [0-9]+ {'.'[0-9]+}?
Cmp			::= E {"=="|"<="|">="|"!="E}?
Str			::= '"' "[- \n\t,.!?A-Za-z]" '"'

Tree types

TR_PGM
TR_B
TR_OP
TR_ASSN
TR_WHILE
TR_DO
TR_PRINT
TR_PRVAL				
TR_V					//contain string
TR_F					//contain string
TR_E
TR_T
TR_P
TR_N					//contain double value
TR_CMP
TR_STR					//contain string
TR_NONE

Types of tokens

TKN_OP					// + - / *
TKN_COMP				// < > <= >= == !=
TKN_ID					// various names, check whether it is key word or built in function
TKN_NUM					// 25.936, -9.0
TKN_SEP					// { } ( ) ; ,
TKN_ASSGN				// += -= *= /=
TKN_STR					// "aASDasdfasdfaSDFa"
TKN_END					// \0
*/

FILE* strlog = NULL;
FILE* strerr = NULL;



int main()
{
	FILE* strin		= fopen("input.txt", "r");
	FILE* strout	= stdout;
		  strlog	= fopen("compiler_log.txt", "w");
		  strerr	= strout;
	
	token** token_stream = (token**) calloc(1, sizeof(token*));
	VERIFY(token_stream == NULL,	-1,			"MAIN(): Calloc fail, token_stream hasn't been initialized");
	int stream_size = 0;
	int ret = tokenize_stream(strin, token_stream, &stream_size);
	VERIFY(ret != CPLR_OK,			-1,			"MAIN(): Tokenize fail");
	printf("Size = %d\n", stream_size);
	tree_head* syntax_tree = NULL;
	ret = get_pgm(*token_stream, &syntax_tree);

	tree_dump(strout, syntax_tree);
	
	if (ret == SNTX_OK) 
	{
		
		fprintf(strout, "\n\nOptimizing...........\n");
		bool is_optimized = false;
		ret = tree_optimize(syntax_tree -> root, &is_optimized);
		int _size = 0;
		ret = tree_check(syntax_tree -> root, &_size);

		VERIFY(ret == SNTX_DIV_BY_ZERO, 0, "MAIN: There's division by zero");
		tree_dump(strout, syntax_tree);
		while (is_optimized == true)
		{
			is_optimized = false;
			ret = tree_optimize(syntax_tree -> root, &is_optimized);
			VERIFY(ret == SNTX_DIV_BY_ZERO, 0, "MAIN: There's division by zero");
			tree_dump(strout, syntax_tree);
		}
		fprintf(strout, "\n\nDONE!\n");
		
		tree_dump(strout, syntax_tree);
	}
	else fprintf(strout, "Building tree failed, watch log\n");

	return 0;

}

