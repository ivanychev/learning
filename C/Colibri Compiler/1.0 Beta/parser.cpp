#include "compiler.h"

extern FILE* strlog;
extern FILE* strerr;

#define DTREE tree_dump(stdout, my_tree -> head);


/*

Pgm		::= B
B		::= '{' Op+ '}'
Op		::= IfOp | AssnOp| WhileOp| DoOp| Print | Print_val';'
IfOp	::= "if" (Cmp) Op|B
AssnOp	::= V [+-/*]?' =' E
WhileOp	::= "while" (Cmp) Op|B
DoOp	::= "do" B "until" (Cmp)
Print ::= "print(" Str ")" 
Print_val ::= "print_val(" E ")" 
V		::= [A-Za-z_]
F		::=	[A-Za-z_] '('E {,E}+ ')'
E		::= T{[+-]T}*
T		::= P{[+-]T}*
P		::= [+-]+ N | V | F | '('E')'
N		::= [0-9]+ {'.'[0-9]+}?
Cmp		::= E {"=="|"<="|">="|"!="E}?
Str		::= '"' "[- \n\t,.!?A-Za-z]" '"'

*/

int get_pgm(token* code, tree_head** syntax_tree);

int get_b(token** code, tree* my_tree);

int get_op(token** code, tree* my_tree);

int get_if(token** code, tree* my_tree);

int get_assnop(token** code, tree* my_tree);

int get_while(token** code, tree* my_tree);

int get_do(token** code, tree* my_tree);

int get_print(token** code, tree* my_tree);

int get_print_val(token** code, tree* my_tree);

int get_v(token** code, tree* my_tree, int side);

int get_f(token** code, tree* my_tree);

int get_e(token** code, tree* my_tree, int side);

int get_t(token** code, tree* my_tree);

int get_p(token** code, tree* my_tree);

int get_n(token** code, tree* my_tree);

int get_cmp(token** code, tree* my_tree);




#define CALL(func) ret = func; if (ret != SNTX_OK) return SNTX_OK;

#define CHECK_ARGS_(func)																												\
	int _size = 0;																														\
	PRECOND(code == NULL,													SNTX_ARG_NULL,	   #func ": %s" _ sntx_errors[TOK_NULL]);	\
	PRECOND(my_tree == NULL,												SNTX_ARG_NULL,	   #func ": %s" _ sntx_errors[TR_NULL] );	\
	PRECOND(tree_check(my_tree -> head -> root, &_size) != TREE_CHECK_OK,	SNTX_INVALID_TREE, #func ": %s" _ sntx_errors[INJURED] );	\
	_size = 0;

#define CHECK_TREE_(func)																						\
int _init_size = 0;																								\
int init_check_tree = tree_check(my_tree -> head -> root, &_init_size);											\
VERIFY(init_check_tree != TREE_CHECK_OK, SNTX_INVALID_TREE, #func "END : Tree injured");						\




//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


int get_pgm(token* code, tree_head** syntax_tree)
{
	PRECOND(code == NULL,		 SNTX_ARG_NULL,		"GET PGM: Argumented code array is NULL");
	PRECOND(syntax_tree == NULL, SNTX_ARG_NULL,		"GET PGM: Argumented tree head array is NULL");
	
	int ret = head_ctr(syntax_tree);
	VERIFY(ret != TREE_OK,		 SNTX_CTR_FAILED,	"GET PGM: Tree head construction failed");
	ret = tree_burn((*syntax_tree) -> root, TR_PGM);				// Maybe save some info about compilation?
	VERIFY(ret != TREE_OK,		 SNTX_BURN_FAILED,	"GET PGM: Tree root burn fail");

	int token_counter = 0;
	token* temp_code = code;
	while (token_counter < MAXTOKEN && temp_code -> type != TKN_END) 
	{
		token_counter++;
		temp_code++;
	}

	VERIFY(token_counter == MAXTOKEN, SNTX_NO_END, "GET PGM: No end in token array or too long program");
	token** arg_code = (token**) calloc(1, sizeof(token*));
	*arg_code = code;

	ret = get_b(arg_code, (*syntax_tree) -> root);

	free(arg_code);
	VERIFY(code -> type == TKN_END, SNTX_MISSED_END, "GET PGM: Can't fing END!!");
	VERIFY(ret != SNTX_OK, CPLR_BAD, "GET PGM: Tokenize fault");
	return CPLR_OK;
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int get_b(token** code, tree* my_tree)
{
	CHECK_ARGS_(GET B);
	int ret = 0;
	VERIFY(((*code) -> type != TKN_SEP) || (*((int*)((*code) -> value)) != '{'),		SNTX_BAD,		"GET B: Haven't found '{' in the beginning of block");
	(*code)++;
	tree* cur_tree = NULL;
	
	ret = tree_ctr(&cur_tree, my_tree -> head);
	VERIFY(ret != TREE_OK,	SNTX_CTR_FAILED, "GET B: %s" _ sntx_errors[CTR_FAIL]);
	ret = tree_burn(cur_tree, TR_B);
	VERIFY(ret != TREE_OK,	SNTX_BURN_FAILED,"GET B: %s" _ sntx_errors[BURN_FAIL]);
	tree_add_right(my_tree, cur_tree);
	VERIFY(ret != TREE_OK,	SNTX_ADD_FAILED, "GET B: %s" _ sntx_errors[ADD_FAIL]);
	
	while ( ( ((*code) -> type != TKN_SEP) && (*((int*)((*code) -> value)) != '}') ) || ((*code) -> type != TKN_END) )
	{
		if (((*code) -> type == TKN_SEP) && (*((int*)((*code) -> value)) == '}')) break;
		CALL(get_op(code, cur_tree));
		//VERIFY( (((*code) -> type) == TKN_SEP) && (*(int*)((*code) -> value) ),		SNTX_BAD_END_OP, "GET
		cur_tree = cur_tree -> right;		
	}
	print_token(*code, stdout);

	tree* end_tree = NULL;
	ret = tree_ctr(&end_tree, my_tree -> head);
	VERIFY(ret != TREE_OK,	SNTX_CTR_FAILED, "GET B: %s" _ sntx_errors[CTR_FAIL]);
	ret = tree_burn(end_tree, TR_NONE);
	VERIFY(ret != TREE_OK,	SNTX_BURN_FAILED,"GET B: %s" _ sntx_errors[BURN_FAIL]);
	tree_add_right(cur_tree, end_tree);
	VERIFY(ret != TREE_OK,	SNTX_ADD_FAILED, "GET B: %s" _ sntx_errors[ADD_FAIL]);

	(*code)++;
	CHECK_TREE_(GET B);
	return SNTX_OK;
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#define CHECK_KEY(word)	(key == WORD_##word)? get_##word(code, my_tree -> right):

int get_op(token** code, tree* my_tree)
{
	CHECK_ARGS_(GET OP);
	VERIFY((*code) -> type != TKN_KEY && (*code) -> type != TKN_ID, SNTX_BAD_OP_TOKEN, "GET OP: Bad token at the beginning of operation");
	int ret = 0;
	
	tree* cur_tree = NULL;
	ret = tree_ctr(&cur_tree, my_tree -> head);
	VERIFY(ret != TREE_OK,	SNTX_CTR_FAILED, "GET OP: %s" _ sntx_errors[CTR_FAIL]);
	ret = tree_burn(cur_tree, TR_OP);
	VERIFY(ret != TREE_OK,	SNTX_BURN_FAILED,"GET OP: %s" _ sntx_errors[BURN_FAIL]);
	tree_add_right(my_tree, cur_tree);
	VERIFY(ret != TREE_OK,	SNTX_ADD_FAILED, "GET OP: %s" _ sntx_errors[ADD_FAIL]);
	int type = (*code) -> type;

	int key = 0;
	if (type == TKN_KEY) key = *(int*)((*code) -> value);

	//printf("%d", key);

	if (type == TKN_ID) 
	{
		CALL(get_assnop(code, my_tree -> right));
		print_token(*code, stdout);
		VERIFY( (((*code) -> type != TKN_SEP) || (*(int*)((*code) -> value) != ';')), SNTX_BAD_OP_END, "GET OP: Bad ending of operation");
		(*code)++;
		
		CHECK_TREE_(GET OP);

		return SNTX_OK;
	}

	ret = CHECK_KEY(if)
		  CHECK_KEY(while)
		  CHECK_KEY(do)
		  CHECK_KEY(print)
		  CHECK_KEY(print_val)
		  0;

	assert(ret != 0);
	
	if (ret != SNTX_OK) return ret;
	VERIFY( (key != WORD_if && key != WORD_while) && (((*code) -> type != TKN_SEP) || (*(int*)((*code) -> value) != ';')), SNTX_BAD_OP_END, "GET OP: Bad ending of operation");
	if (key != WORD_if && key != WORD_while) (*code)++;

	CHECK_TREE_(GET OP);
	return SNTX_OK;	

}

#undef CHECK_KEY

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int get_assnop(token** code, tree* my_tree)
{
	CHECK_ARGS_(GET ASSNOP);
	VERIFY( !((*code) -> type == TKN_ID && (*(code) + 1) -> type == TKN_ASSGN), SNTX_BAD,		"GET ASSNOP: Bad assign begin, there's no variable or assign operator");

	tree* cur_tree = NULL;

	int ret = tree_ctr(&cur_tree, my_tree -> head);
	VERIFY(ret != TREE_OK,	SNTX_CTR_FAILED, "GET ASSNOP: %s" _ sntx_errors[CTR_FAIL]);
	ret = tree_burn(cur_tree, TR_ASSN, *(int*)((*code + 1) -> value));
	VERIFY(ret != TREE_OK,	SNTX_BURN_FAILED,"GET ASSNOP: %s" _ sntx_errors[BURN_FAIL]);
	ret = tree_add_left(my_tree, cur_tree);
	VERIFY(ret != TREE_OK,	SNTX_ADD_FAILED, "GET ASSNOP: %s" _ sntx_errors[ADD_FAIL]);

	CALL(get_v(code, cur_tree, LEFT)); //code increased
	(*code)++;
	//DTREE;
	print_token(*code, stdout);
	
	CALL(get_e(code, cur_tree, RIGHT));


	CHECK_TREE_(GET ASSNOP);
	return SNTX_OK;
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int get_if(token** code, tree* my_tree)
{
	CHECK_ARGS_(GET IF);

	VERIFY( (((*code) -> type != TKN_KEY) || *(int*)((*code) -> value) != WORD_if || (*code + 1) -> type != TKN_SEP || *(int*)((*code + 1) -> value) != '('), SNTX_BAD, "GET IF: Invalid IF syntax at the beginning");
	(*code) += 2;

	tree* cur_tree = NULL;
	
//-----------------------------------------
	int ret = tree_ctr(&cur_tree, my_tree -> head);
	VERIFY(ret != TREE_OK,	SNTX_CTR_FAILED, "GET IF: %s" _ sntx_errors[CTR_FAIL]);
	ret = tree_burn(cur_tree, TR_IF);
	VERIFY(ret != TREE_OK,	SNTX_BURN_FAILED,"GET IF: %s" _ sntx_errors[BURN_FAIL]);
	ret = tree_add_left(my_tree, cur_tree);
	VERIFY(ret != TREE_OK,	SNTX_ADD_FAILED, "GET IF: %s" _ sntx_errors[ADD_FAIL]);
	my_tree = cur_tree;
//-----------------------------------------

	CALL(get_cmp(code, cur_tree));
	(*code)++;

	if (((*code) -> type == TKN_SEP) && *(int*)((*code) -> value) == '{')
	{
		CALL(get_b(code, cur_tree));
		//VERIFY(((*code) -> type == TKN_SEP) && *(int*)((*code) -> value) == '}', SNTX_BAD, "GET IF: No closing '}'");
		
		CHECK_TREE_(GET IF);
		return SNTX_OK;
	}
	
	CALL(get_op(code, cur_tree));
	
	CHECK_TREE_(GET IF);
	return SNTX_OK;
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int get_while(token** code, tree* my_tree)
{
	CHECK_ARGS_(GET WHILE);

	VERIFY( (((*code) -> type != TKN_KEY) || *(int*)((*code) -> value) != WORD_while || (*code + 1) -> type != TKN_SEP || *(int*)((*code + 1) -> value) != '('), SNTX_BAD, "GET WHILE: Invalid WHILE syntax at the beginning");
	(*code) += 2;

	tree* cur_tree = NULL;
	
//-----------------------------------------
	int ret = tree_ctr(&cur_tree, my_tree -> head);
	VERIFY(ret != TREE_OK,	SNTX_CTR_FAILED, "GET WHILE: %s" _ sntx_errors[CTR_FAIL]);
	ret = tree_burn(cur_tree, TR_WHILE);
	VERIFY(ret != TREE_OK,	SNTX_BURN_FAILED,"GET WHILE: %s" _ sntx_errors[BURN_FAIL]);
	ret = tree_add_left(my_tree, cur_tree);
	VERIFY(ret != TREE_OK,	SNTX_ADD_FAILED, "GET WHILE: %s" _ sntx_errors[ADD_FAIL]);
	my_tree = cur_tree;
//-----------------------------------------

	CALL(get_cmp(code, cur_tree));
	(*code)++;

	if (((*code) -> type == TKN_SEP) && *(int*)((*code) -> value) == '{')
	{
		CALL(get_b(code, cur_tree));
		//VERIFY(((*code) -> type == TKN_SEP) && *(int*)((*code) -> value) == '}', SNTX_BAD, "GET IF: No closing '}'");
		
		CHECK_TREE_(GET IF);
		return SNTX_OK;
	}
	
	CALL(get_op(code, cur_tree));
	
	CHECK_TREE_(GET IF);
	return SNTX_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int get_do(token** code, tree* my_tree)
{
	CHECK_ARGS_(GET DO);

	VERIFY( (((*code) -> type != TKN_KEY) || *(int*)((*code) -> value) != WORD_do), SNTX_BAD, "GET WHILE: Invalid DO syntax at the beginning");
	(*code)++;
	tree* cur_tree = NULL;
		
//-----------------------------------------

	int ret = tree_ctr(&cur_tree, my_tree -> head);
	VERIFY(ret != TREE_OK,	SNTX_CTR_FAILED, "GET DO: %s" _ sntx_errors[CTR_FAIL]);
	ret = tree_burn(cur_tree, TR_DO);
	VERIFY(ret != TREE_OK,	SNTX_BURN_FAILED,"GET DO: %s" _ sntx_errors[BURN_FAIL]);
	ret = tree_add_left(my_tree, cur_tree);
	VERIFY(ret != TREE_OK,	SNTX_ADD_FAILED, "GET DO: %s" _ sntx_errors[ADD_FAIL]);

	my_tree = cur_tree;
//-----------------------------------------
	
	VERIFY( !(((*code) -> type == TKN_SEP) && *(int*)((*code) -> value) == '{'), SNTX_BAD, "GET DO: Invalid block beginning");
	print_token(*code, stdout);
	CALL(get_b(code, cur_tree));
	print_token(*code, stdout);

	//VERIFY(((*code) -> type == TKN_SEP) && *(int*)((*code) -> value) == '}', SNTX_BAD, "GET WHILE: No closing '}'");
	
	VERIFY((*code) -> type != TKN_SEP || *(int*)((*code) -> value) != '(', SNTX_BAD, "GET DO: Bad beginning of comparison");
	(*code)++;
	print_token(*code, stdout);
	CALL(get_cmp(code, cur_tree));
	print_token(*code, stdout);
	VERIFY((*code) -> type != TKN_SEP || *(int*)((*code) -> value) != ')', SNTX_BAD, "GET DO: Bad ending of comparison");
	(*code)++;

	CHECK_TREE_(GET DO);
	return SNTX_OK;
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int convert_string(token* my_token)
{
	assert(my_token);
	assert(my_token -> type == TKN_STR);
	char* _1c = (char*)my_token -> value;
	char* _2c = _1c + 1;
	if ((*_2c == 0) || (*_1c == 0)) return SNTX_OK;
	int i = 0;
	while (*_2c != '\0')
	{
		/*if (*_1c == '\\')
		{
			switch(*_2c)
			{
			case 'n':
				*_1c = '\n';
				strcpy(_2c, _2c + 1);
				break;
			case 't':
				*_1c = '\t';
				strcpy(_2c, _2c + 1);
				break;
			case '\\':
				*_1c = '\\';
				strcpy(_2c, _2c + 1);
				break;
			case '\"':
				*_1c = '\"';
				strcpy(_2c, _2c + 1);
				break;
			case '\%':
				*_1c = '\%';
				strcpy(_2c, _2c + 1);
				break;
			default:
				strcpy(_1c, _2c);
				break;
			}
		}
		*/
		_2c++;
		_1c++;
		i++;
		assert(i < MAXLINE);
	}

	return SNTX_OK;
}
		
		

int get_print(token** code, tree* my_tree)
{
	CHECK_ARGS_(GET DO);
	VERIFY((		((*code) -> type != TKN_KEY) || *(int*)((*code) -> value) != WORD_print 
		|| ((*code + 1) -> type) != TKN_SEP || *(int*)((*code + 1) -> value) != '('
		|| ((*code + 2) -> type) != TKN_STR
		|| ((*code + 3) -> type) != TKN_SEP || *(int*)((*code + 3) -> value) != ')'), 
		SNTX_BAD, "GET PRINT: Invalid PRINT syntax at the beginning");
	//(*code) += 2;
	int ret = 0;
	CALL(convert_string(*code + 2));

	tree* cur_tree = NULL;

	ret = tree_ctr(&cur_tree, my_tree -> head);
	VERIFY(ret != TREE_OK,	SNTX_CTR_FAILED, "GET PRINT: %s" _ sntx_errors[CTR_FAIL]);
	ret = tree_burn(cur_tree, TR_PRINT);
	VERIFY(ret != TREE_OK,	SNTX_BURN_FAILED,"GET PRINT: %s" _ sntx_errors[BURN_FAIL]);
	ret = tree_add_left(my_tree, cur_tree);
	VERIFY(ret != TREE_OK,	SNTX_ADD_FAILED, "GET PRINT: %s" _ sntx_errors[ADD_FAIL]);

	ret = tree_ctr(&cur_tree, my_tree -> head);
	VERIFY(ret != TREE_OK,	SNTX_CTR_FAILED, "GET PRINT: %s" _ sntx_errors[CTR_FAIL]);
	ret = tree_burn(cur_tree, TR_STR, (char*)((*code + 2) -> value));
	VERIFY(ret != TREE_OK,	SNTX_BURN_FAILED,"GET PRINT: %s" _ sntx_errors[BURN_FAIL]);
	ret = tree_add_right(my_tree -> left, cur_tree);
	VERIFY(ret != TREE_OK,	SNTX_ADD_FAILED, "GET PRINT: %s" _ sntx_errors[ADD_FAIL]);
	
	(*code) += 4;
	print_token(*code, stdout);
	CHECK_TREE_(GET PRINT);
	return SNTX_OK;
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int get_print_val(token** code, tree* my_tree)
{
	CHECK_ARGS_(GET DO);

	VERIFY((		((*code) -> type != TKN_KEY) || *(int*)((*code) -> value) != WORD_print_val 
		|| ((*code + 1) -> type) != TKN_SEP || *(int*)((*code + 1) -> value) != '('
		//|| ((*code + 2) -> type) != TKN_ID
		/*|| ((*code + 3) -> type) != TKN_SEP || *(int*)((*code + 3) -> value) != ')'*/), 
		SNTX_BAD, "GET PRINT_VAL: Invalid PRINT syntax at the beginning");

	tree* cur_tree = NULL;

	int ret = tree_ctr(&cur_tree, my_tree -> head);
	VERIFY(ret != TREE_OK,	SNTX_CTR_FAILED, "GET PRINT VAL: %s" _ sntx_errors[CTR_FAIL]);
	ret = tree_burn(cur_tree, TR_PRVAL);
	VERIFY(ret != TREE_OK,	SNTX_BURN_FAILED,"GET PRINT VAL: %s" _ sntx_errors[BURN_FAIL]);
	ret = tree_add_left(my_tree, cur_tree);
	VERIFY(ret != TREE_OK,	SNTX_ADD_FAILED, "GET PRINT VAL: %s" _ sntx_errors[ADD_FAIL]);

	/*
	ret = tree_ctr(&cur_tree, my_tree -> head);
	VERIFY(ret != TREE_OK,	SNTX_CTR_FAILED, "GET PRINT VAL: %s" _ sntx_errors[CTR_FAIL]);
	ret = tree_burn(cur_tree, TR_V, (char*)((*code + 2) -> value));
	VERIFY(ret != TREE_OK,	SNTX_BURN_FAILED,"GET PRINT VAL: %s" _ sntx_errors[BURN_FAIL]);
	ret = tree_add_right(my_tree -> left, cur_tree);
	VERIFY(ret != TREE_OK,	SNTX_ADD_FAILED, "GET PRINT VAL: %s" _ sntx_errors[ADD_FAIL]);
	*/
	(*code) += 2;
	CALL(get_e(code, cur_tree, RIGHT));
	//tree_delete(cur_tree -> right);
	VERIFY((*code) -> type != TKN_SEP || *(int*)((*code) -> value) != ')', SNTX_BAD, "GET PRINT_VAL: No closing bracket");
	(*code)++;
	//(*code) += 4;
	CHECK_TREE_(GET PRINT VAL);
	return SNTX_OK;
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

/*
			Now there's another strategy to parse expression. We argument expression functions pointers,
			which are the BEGINNINGS of what they are building

*/
int get_e(token** code, tree* my_tree, int side)					//
{
	CHECK_ARGS_(GET E);
	VERIFY(side != LEFT && side != RIGHT,	SNTX_BAD,	"GET E: Bad side");
	
	tree* cur_tree = NULL;
	tree* origin_tree = my_tree;

	int ret = tree_ctr(&cur_tree, my_tree -> head);
	VERIFY(ret != TREE_OK,	SNTX_CTR_FAILED, "GET E: Tree construction failed");
	
	if (side == LEFT)	ret = tree_add_left (my_tree, cur_tree);
	else				ret = tree_add_right(my_tree, cur_tree);

	CALL(get_t(code, cur_tree));
	
	while (((*code) -> type == TKN_OP) && (*(int*)((*code) -> value) == '+' || *(int*)((*code) -> value) == '-'))
	{
		tree_burn(cur_tree, TR_SIGN, *(int*)((*code) -> value));
		(*code)++;

		my_tree = cur_tree;
		int ret = tree_ctr(&cur_tree, my_tree -> head);
		VERIFY(ret != TREE_OK,	SNTX_CTR_FAILED, "GET E: Tree construction failed");
		
		ret = tree_add_right(my_tree, cur_tree);
		VERIFY(ret != TREE_OK,	SNTX_ADD_FAILED, "GET E: %s" _ sntx_errors[ADD_FAIL]);
		
		CALL(get_t(code, cur_tree));
	}
	/*
	if (side_sticked == false)
	{
		if (side == RIGHT)
			{
				ret = tree_add_right(my_tree, cur_tree);
				VERIFY(ret != TREE_OK,	SNTX_ADD_FAILED, "GET E: %s" _ sntx_errors[ADD_FAIL]);
			}
			else
			{
				ret = tree_add_left(my_tree, cur_tree);
				VERIFY(ret != TREE_OK,	SNTX_ADD_FAILED, "GET E: %s" _ sntx_errors[ADD_FAIL]);
			}
		side_sticked = true;
	}
	else
	{
		ret = tree_add_right(my_tree, cur_tree);
		VERIFY(ret != TREE_OK,	SNTX_ADD_FAILED, "GET E: %s" _ sntx_errors[ADD_FAIL]);
	}
	*/
	//ret = tree_destr(cur_tree);
	//VERIFY(ret != TREE_OK, SNTX_BAD, "GET E: Tree hasn't been destroyed");
	ret = tree_delete(cur_tree, LEFT);
	VERIFY(ret != TREE_OK, SNTX_BAD, "GET E: Temporary tree hasn't been deleted properly");

	CHECK_TREE_(GET E);
	return SNTX_OK;
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


int get_t(token** code, tree* my_tree)
{
	CHECK_ARGS_(GET T);

	tree* cur_tree = NULL;

	int ret = tree_ctr(&cur_tree, my_tree -> head);
	VERIFY(ret != TREE_OK,	SNTX_CTR_FAILED, "GET T: Tree construction failed");
	ret = tree_add_left(my_tree, cur_tree);
	VERIFY(ret != TREE_OK,	SNTX_ADD_FAILED, "GET T: %s" _ sntx_errors[ADD_FAIL]);
	
	CALL(get_p(code, cur_tree));

	while (((*code) -> type == TKN_OP) && (*(int*)((*code) -> value) == '*' || *(int*)((*code) -> value) == '/'))
	{

		tree_burn(cur_tree, TR_SIGN, *(int*)((*code) -> value));
		(*code)++;
		
		my_tree = cur_tree;
		int ret = tree_ctr(&cur_tree, my_tree -> head);
		VERIFY(ret != TREE_OK,	SNTX_CTR_FAILED, "GET T: Tree construction failed");
		ret = tree_add_right(my_tree, cur_tree);
		VERIFY(ret != TREE_OK,	SNTX_ADD_FAILED, "GET T: %s" _ sntx_errors[ADD_FAIL]);

		CALL(get_p(code, cur_tree));
	}

	/*
	if (side_sticked == false)
		{
			
			ret = tree_add_left(my_tree, cur_tree);
			VERIFY(ret != TREE_OK,	SNTX_ADD_FAILED, "GET T: %s" _ sntx_errors[ADD_FAIL]);
			
			side_sticked = true;
		}
		else
		{
			ret = tree_add_right(my_tree, cur_tree);
			VERIFY(ret != TREE_OK,	SNTX_ADD_FAILED, "GET T: %s" _ sntx_errors[ADD_FAIL]);
			
		}
	*/
	
	ret = tree_delete(cur_tree, LEFT);
	VERIFY(ret != TREE_OK, SNTX_BAD, "GET T: Temporary tree hasn't been deleted properly");

	CHECK_TREE_(GET T);
	return SNTX_OK;
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int get_p(token** code, tree* my_tree)
{
	CHECK_ARGS_(GET T);

	int sign = 1;
	while ((*code) -> type == TKN_OP)
	{
		if (*(int*)((*code) -> value) == '+')
		{
			sign *= 1;
			(*code)++;
			continue;
		}
		if (*(int*)((*code) -> value) == '-')
		{
			sign *= -1;
			(*code)++;
			continue;
		}
		VERIFY(true, SNTX_BAD, "GET P: Sign is not '+' or '-'");
	}

	tree* cur_tree = NULL;

	int ret = tree_ctr(&cur_tree, my_tree -> head);
	VERIFY(ret != TREE_OK,	SNTX_CTR_FAILED, "GET P: Tree construction failed");
	ret = tree_burn(cur_tree, TR_SIGN, '*');
	VERIFY(ret != TREE_OK,	SNTX_BURN_FAILED,"GET P: %s" _ sntx_errors[BURN_FAIL]);

	ret = tree_add_left(my_tree, cur_tree);
	VERIFY(ret != TREE_OK,	SNTX_ADD_FAILED, "GET P: %s" _ sntx_errors[ADD_FAIL]);

	ret = tree_ctr(&cur_tree, my_tree -> head);
	VERIFY(ret != TREE_OK,	SNTX_CTR_FAILED, "GET P: Tree construction failed");
	ret = tree_burn(cur_tree, TR_N, (double)sign);
	VERIFY(ret != TREE_OK,	SNTX_BURN_FAILED,"GET P: %s" _ sntx_errors[BURN_FAIL]);
	ret = tree_add_left(my_tree -> left, cur_tree);
	VERIFY(ret != TREE_OK,	SNTX_ADD_FAILED, "GET P: %s" _ sntx_errors[ADD_FAIL]);


	if ((*code) -> type == TKN_NUM)
	{
		CALL(get_n(code, my_tree -> left));
		return SNTX_OK;
	}
	if (((*code) -> type == TKN_SEP) && *(int*)((*code) -> value) == '(')
	{
		(*code)++;
		CALL(get_e(code , my_tree -> left, RIGHT));
		return SNTX_OK;
	}
	if (((*code) -> type == TKN_ID) && ( (*(code) + 1) -> type == TKN_SEP ) && ( *(int*)((*(code) + 1) -> value) == '('))
	{
		CALL(get_f(code, my_tree -> left));
		return SNTX_OK;
	}
	if (((*code) -> type == TKN_ID))
	{
		CALL(get_v(code, my_tree -> left, RIGHT));
		return SNTX_OK;
	}

	CHECK_TREE_(GET P);
	VERIFY(true,	SNTX_BAD,	"GET P: Hasn't reckognized token");
	
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int get_n(token** code, tree* my_tree)
{
	CHECK_ARGS_(GET N);

	VERIFY((*code) -> type != TKN_NUM, SNTX_BAD, "GET N: Number expected");

	tree* cur_tree = NULL;

	int ret = tree_ctr(&cur_tree, my_tree -> head);
	VERIFY(ret != TREE_OK,	SNTX_CTR_FAILED, "GET N: Tree construction failed");
	ret = tree_burn(cur_tree, TR_N, *(double*)((*code) -> value));
	VERIFY(ret != TREE_OK,	SNTX_BURN_FAILED,"GET N: %s" _ sntx_errors[BURN_FAIL]);
	ret = tree_add_right(my_tree, cur_tree);
	VERIFY(ret != TREE_OK,	SNTX_ADD_FAILED, "GET N: %s" _ sntx_errors[ADD_FAIL]);

	(*code)++;
	
	CHECK_TREE_(GET N);
	return SNTX_OK;
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int get_v(token** code, tree* my_tree, int side)
{
	CHECK_ARGS_(GET V);

	VERIFY((*code) -> type != TKN_ID, SNTX_BAD, "GET V: ID expected");
	VERIFY(side != LEFT && side != RIGHT, SNTX_BAD, "GET V: invalid side");

	tree* cur_tree = NULL;
	
	
	int ret = tree_ctr(&cur_tree, my_tree -> head);
	VERIFY(ret != TREE_OK,	SNTX_CTR_FAILED, "GET V: Tree construction failed");
	ret = tree_burn(cur_tree, TR_V, (char*)((*code) -> value));
	VERIFY(ret != TREE_OK,	SNTX_BURN_FAILED,"GET V: %s" _ sntx_errors[BURN_FAIL]);
	
	if (side == LEFT)	ret = tree_add_left (my_tree, cur_tree);
	else				ret = tree_add_right(my_tree, cur_tree);

	VERIFY(ret != TREE_OK,	SNTX_ADD_FAILED, "GET V: %s" _ sntx_errors[ADD_FAIL]);

	(*code)++;
	
	CHECK_TREE_(GET V);
	return SNTX_OK;
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int get_f_check_args(token* code, int* argc)
{
	assert(code != NULL);
	print_token(code, stdout);
	*argc = 0;

	if ((code -> type == TKN_SEP)&&(*(int*)(code -> value) == ')'))
	{
		return SNTX_OK;
	}
	*argc = 1;
	int count_brackets = 0;
	while (!( (code -> type == TKN_END) || (((code -> type == TKN_SEP)&&(*(int*)(code -> value) == ')')) && count_brackets == 0)))
	{
		print_token(code, stdout);
		if (code -> type == TKN_SEP)
		switch (*(int*)((code) -> value))
		{
		case '(': count_brackets++; break;
		case ')': count_brackets--; break;
		case ',': if (count_brackets == 0) (*argc)++; break;
		default: break;
		}
		code++;
	}

	VERIFY((code -> type == TKN_END), SNTX_BAD, "GET F: no end of args bracket");
	return SNTX_OK;
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int get_f(token** code, tree* my_tree)
{
	CHECK_ARGS_(GET F);

	VERIFY((*code) -> type != TKN_ID, SNTX_BAD, "GET V: ID expected");
	
	int ret = 0;
	int argc = 0;

	CALL(get_f_check_args((*code + 2), &argc));

	int i = 0;
	for (i = 0; i < FUNC_NUM; ++i) 	if (strcmp((char*)((*code) -> value), (math_funcs[i]).name) == 0)	break;

	VERIFY((i == FUNC_NUM), SNTX_BAD, "GET F: No such function");
	
	VERIFY((argc != math_funcs[i].argc), SNTX_BAD, "GET F: Invalid number of arguments, waited for [%d], got [%d]" _ math_funcs[i].argc _ argc);

	tree* cur_tree = NULL;
	ret = tree_ctr(&cur_tree, my_tree -> head);
	VERIFY(ret != TREE_OK,	SNTX_CTR_FAILED, "GET F: Tree construction failed");
	ret = tree_burn(cur_tree, TR_F, (char*)((*code) -> value));
	VERIFY(ret != TREE_OK,	SNTX_BURN_FAILED,"GET F: %s" _ sntx_errors[BURN_FAIL]);
	ret = tree_add_right(my_tree, cur_tree);
	VERIFY(ret != TREE_OK,	SNTX_ADD_FAILED, "GET F: %s" _ sntx_errors[ADD_FAIL]);

	my_tree = cur_tree;
	(*code)++;

	for (int i = 0; i < argc; ++i)
	{
		(*code)++;
		print_token(*code, stdout);
		ret = tree_ctr(&cur_tree, my_tree -> head);
		VERIFY(ret != TREE_OK,	SNTX_CTR_FAILED, "GET F: Tree construction failed");
		ret = tree_add_right(my_tree, cur_tree);
		VERIFY(ret != TREE_OK,	SNTX_ADD_FAILED, "GET F: %s" _ sntx_errors[ADD_FAIL]);
		CALL(get_e(code, cur_tree, LEFT));
		my_tree = my_tree -> right;
	}
	my_tree = my_tree -> papa;
	ret = tree_delete(my_tree -> right, LEFT);
	VERIFY(ret != TREE_OK, SNTX_BAD, "GET F: Temporary tree hasn't been deleted properly");
	print_token(*code, stdout);
	VERIFY(((*code) -> type != TKN_SEP) || *(int*)((*code) -> value) != ')', SNTX_BAD, "GET F: Invalid ending of args brackets, waited for '('");
	(*code)++;
	CHECK_TREE_(GET F);
	return SNTX_OK;

}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int get_cmp(token** code, tree* my_tree)
{
	CHECK_ARGS_(GET CMP);

	tree* cur_tree = NULL;
	int ret = tree_ctr(&cur_tree, my_tree -> head);

	VERIFY(ret != TREE_OK,	SNTX_CTR_FAILED, "GET CMP: Tree construction failed");
	ret = tree_burn(cur_tree, TR_NONE);
	VERIFY(ret != TREE_OK,	SNTX_BURN_FAILED,"GET CMP: %s" _ sntx_errors[BURN_FAIL]);
	ret = tree_add_left(my_tree, cur_tree);
	VERIFY(ret != TREE_OK,	SNTX_ADD_FAILED, "GET CMP: %s" _ sntx_errors[ADD_FAIL]);

	CALL(get_e(code, cur_tree, LEFT));
	VERIFY((*code) -> type != TKN_COMP, SNTX_BAD, "GET CMP: No comparison sign after expression");
	ret = tree_burn(cur_tree, TR_CMP, (*(int*)((*code) -> value)));
	VERIFY(ret != TREE_OK,	SNTX_BURN_FAILED,"GET CMP: %s" _ sntx_errors[BURN_FAIL]);

	(*code)++;
	CALL(get_e(code, cur_tree, RIGHT));

	CHECK_TREE_(GET CMP);
	return SNTX_OK;
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

/*
	TKN_OP			= 2001,
	TKN_COMP		= 2002,
	TKN_ID			= 2003,
	TKN_NUM			= 2004,
	TKN_SEP			= 2005,
	TKN_ASSGN		= 2006,
	TKN_STR			= 2007,
	TKN_END			= 2008,
	TKN_KEY			= 2009,
*/