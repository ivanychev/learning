// parcer.cpp V 1.01
#include "compiler.h"

extern FILE* strlog;
extern FILE* strerr;

#define DTREE tree_dump(stdout, my_tree -> head);

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

int get_t(token** code, tree* my_tree, int side);

int get_p(token** code, tree* my_tree, int side);

int get_n(token** code, tree* my_tree);

int get_cmp(token** code, tree* my_tree);


#define HEAD(my_tree) (my_tree -> head)
#define ROOT(my_tree) (my_tree -> head -> root)
#define WORD(my_tree)	 (char*)(my_tree -> value)
#define DOUBLE(my_tree) *(double*)(my_tree -> value)
#define INT(my_tree)	*((int*)(my_tree -> value))




#define CALL(func) ret = func; if (ret != SNTX_OK) return ret;
#define TREE_CALL(func) ret = func; if (ret != TREE_OK) return SNTX_INIT_FAIL;

#define CHECK_ARGS_(func)																												\
	int _size = 0;																														\
	VERIFY1(code == NULL,													SNTX_ARG_NULL,	   #func ": %s", sntx_errors[TOK_NULL]);	\
	VERIFY1(my_tree == NULL,												SNTX_ARG_NULL,	   #func ": %s", sntx_errors[TR_NULL] );	\
	VERIFY1(tree_check(my_tree -> head -> root, &_size) != TREE_CHECK_OK,	SNTX_INVALID_TREE, #func ": %s", sntx_errors[INJURED] );	\
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
	assert(arg_code);
	*arg_code = code;

	ret = get_e(arg_code, (*syntax_tree) -> root, RIGHT);
	DBG_FREE fprintf(stdout, "[%08x] Get pgm. Arg_code\n", arg_code);
	free(arg_code);
	arg_code = NULL;
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
	
	TREE_CALL(tree_init(&cur_tree, HEAD(my_tree), my_tree, "GET B", TR_B, RIGHT));

	while ( ( ((*code) -> type != TKN_SEP) && (*((int*)((*code) -> value)) != '}') ) || ((*code) -> type != TKN_END) )
	{
		if (((*code) -> type == TKN_SEP) && (*((int*)((*code) -> value)) == '}')) break;
		CALL(get_op(code, cur_tree));
		
		cur_tree = cur_tree -> right;		
	}
	//print_token(*code, stdout);

	tree* end_tree = NULL;
	TREE_CALL(tree_init(&end_tree, HEAD(my_tree), cur_tree, "GET B", TR_NONE, RIGHT));

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

	//TREE_CALL(tree_init(&cur_tree, HEAD(my_tree), my_tree, "GET OP", TR_OP, RIGHT));
	
	
	ret = tree_ctr(&cur_tree, my_tree -> head);
	VERIFY1(ret != TREE_OK,	SNTX_CTR_FAILED, "GET OP: %s", sntx_errors[CTR_FAIL]);
	ret = tree_burn(cur_tree, TR_OP);
	VERIFY1(ret != TREE_OK,	SNTX_BURN_FAILED,"GET OP: %s", sntx_errors[BURN_FAIL]);
	tree_add_right(my_tree, cur_tree);
	VERIFY1(ret != TREE_OK,	SNTX_ADD_FAILED, "GET OP: %s", sntx_errors[ADD_FAIL]);
	
	
	int type = (*code) -> type;

	int key = 0;
	if (type == TKN_KEY) key = *(int*)((*code) -> value);


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
	print_token(*code, stdout);
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
	int ret = 0;

	tree* cur_tree = NULL;

	//TREE_CALL(tree_init(&cur_tree, HEAD(my_tree), my_tree, "GET ASSNOP", TR_ASSN, LEFT));
	
	ret = tree_ctr(&cur_tree, my_tree -> head);
	VERIFY1(ret != TREE_OK,	SNTX_CTR_FAILED, "GET ASSNOP: %s", sntx_errors[CTR_FAIL]);
	ret = tree_burn(cur_tree, TR_ASSN, *(int*)((*code + 1) -> value));
	VERIFY1(ret != TREE_OK,	SNTX_BURN_FAILED,"GET ASSNOP: %s", sntx_errors[BURN_FAIL]);
	ret = tree_add_left(my_tree, cur_tree);
	VERIFY1(ret != TREE_OK,	SNTX_ADD_FAILED, "GET ASSNOP: %s", sntx_errors[ADD_FAIL]);
	

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
	int ret = 0;
	VERIFY( (((*code) -> type != TKN_KEY) || *(int*)((*code) -> value) != WORD_if || (*code + 1) -> type != TKN_SEP || *(int*)((*code + 1) -> value) != '('), SNTX_BAD, "GET IF: Invalid IF syntax at the beginning");
	(*code) += 2;

	tree* cur_tree = NULL;
	

	TREE_CALL(tree_init(&cur_tree, HEAD(my_tree), my_tree, "GET IF", TR_IF, LEFT));


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
	int ret = 0;
	VERIFY( (((*code) -> type != TKN_KEY) || *(int*)((*code) -> value) != WORD_while || (*code + 1) -> type != TKN_SEP || *(int*)((*code + 1) -> value) != '('), SNTX_BAD, "GET WHILE: Invalid WHILE syntax at the beginning");
	(*code) += 2;

	tree* cur_tree = NULL;
	

	TREE_CALL(tree_init(&cur_tree, HEAD(my_tree), my_tree, "GET WHILE", TR_WHILE, LEFT));


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
	int ret = 0;
	VERIFY( (((*code) -> type != TKN_KEY) || *(int*)((*code) -> value) != WORD_do), SNTX_BAD, "GET WHILE: Invalid DO syntax at the beginning");
	(*code)++;
	tree* cur_tree = NULL;

	TREE_CALL(tree_init(&cur_tree, HEAD(my_tree), my_tree, "GET DO", TR_DO, LEFT));

	my_tree = cur_tree;

	
	VERIFY( !(((*code) -> type == TKN_SEP) && *(int*)((*code) -> value) == '{'), SNTX_BAD, "GET DO: Invalid block beginning");
	print_token(*code, stdout);
	CALL(get_b(code, cur_tree));
	print_token(*code, stdout);

	
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

	TREE_CALL(tree_init(&cur_tree, HEAD(my_tree), my_tree, "GET PRINT", TR_PRINT, LEFT));
	
	ret = tree_ctr(&cur_tree, my_tree -> head);
	VERIFY1(ret != TREE_OK,	SNTX_CTR_FAILED, "GET PRINT: %s", sntx_errors[CTR_FAIL]);
	ret = tree_burn(cur_tree, TR_STR, (char*)((*code + 2) -> value));
	VERIFY1(ret != TREE_OK,	SNTX_BURN_FAILED,"GET PRINT: %s", sntx_errors[BURN_FAIL]);
	ret = tree_add_right(my_tree -> left, cur_tree);
	VERIFY1(ret != TREE_OK,	SNTX_ADD_FAILED, "GET PRINT: %s", sntx_errors[ADD_FAIL]);
	

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

	int ret = 0;
	tree* cur_tree = NULL;

	TREE_CALL(tree_init(&cur_tree, HEAD(my_tree), my_tree, "GET PRINT_VAL", TR_PRVAL, LEFT));

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
	VERIFY(side != RIGHT && side != LEFT,		SNTX_BAD,		"GET E: Invalid side");
	int side_to_insert = 0;

	tree* cur_tree = NULL;
	tree* new_node = NULL;

	int ret = tree_ctr(&cur_tree, my_tree -> head);
	VERIFY(ret != TREE_OK,	SNTX_CTR_FAILED, "GET E: Tree construction failed");
	
	if (side == LEFT)	ret = tree_add_left (my_tree, cur_tree);
	else				ret = tree_add_right(my_tree, cur_tree);
	VERIFY1(ret != TREE_OK,	SNTX_ADD_FAILED, "GET E: %s", sntx_errors[ADD_FAIL]);

	CALL(get_t(code, cur_tree, LEFT));
	
	while (((*code) -> type == TKN_OP) && (INT((*code)) == '+' || INT((*code)) == '-'))
	{
		
		tree_burn(cur_tree, TR_SIGN, INT((*code)));
		(*code)++;
		CALL(get_t(code, cur_tree, RIGHT));

		ret = tree_get_side(cur_tree, &side_to_insert);
		VERIFY(ret != TREE_OK,		CPLR_BAD,		"GET E: Can't get side");

		ret = node_insert(cur_tree -> papa, &new_node, side_to_insert, LEFT);
		VERIFY1(ret != TREE_OK,		SNTX_BAD,		"GET E: Node insertion failed, error [%d]", ret);

		cur_tree = new_node;
	}

	ret = tree_delete(cur_tree, LEFT);
	VERIFY(ret != TREE_OK, SNTX_BAD, "GET E: Temporary tree hasn't been deleted properly");

	CHECK_TREE_(GET E);
	return SNTX_OK;
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


int get_t(token** code, tree* my_tree, int side)
{
	CHECK_ARGS_(GET T);
	VERIFY(side != RIGHT && side != LEFT,		SNTX_BAD,		"GET T: Invalid side");

	tree* cur_tree = NULL;
	tree* new_node = NULL;
	int side_to_insert = 0;

	int ret = tree_ctr(&cur_tree, my_tree -> head);
	VERIFY(ret != TREE_OK,	SNTX_CTR_FAILED, "GET T: Tree construction failed");
	
	if (side == LEFT)	ret = tree_add_left (my_tree, cur_tree);
	else				ret = tree_add_right(my_tree, cur_tree);
	VERIFY1(ret != TREE_OK,	SNTX_ADD_FAILED, "GET T: %s", sntx_errors[ADD_FAIL]);
	
	CALL(get_p(code, cur_tree, LEFT));

	while (((*code) -> type == TKN_OP) && (*(int*)((*code) -> value) == '*' || *(int*)((*code) -> value) == '/'))
	{
		tree_burn(cur_tree, TR_SIGN, INT((*code)));
		(*code)++;
		CALL(get_p(code, cur_tree, RIGHT));

		ret = tree_get_side(cur_tree, &side_to_insert);
		VERIFY(ret != TREE_OK,		CPLR_BAD,		"GET T: Can't get side");


		ret = node_insert(cur_tree -> papa, &new_node, side_to_insert, LEFT);
		VERIFY1(ret != TREE_OK,		SNTX_BAD,		"GET T: Node insertion failed, error [%d]", ret);

		cur_tree = new_node;
		
		/*
		my_tree = cur_tree;
		ret = tree_ctr(&cur_tree, my_tree -> head);
		VERIFY(ret != TREE_OK,	SNTX_CTR_FAILED, "GET T: Tree construction failed");
		ret = tree_add_right(my_tree, cur_tree);
		VERIFY1(ret != TREE_OK,	SNTX_ADD_FAILED, "GET T: %s", sntx_errors[ADD_FAIL]);

		CALL(get_p(code, cur_tree, RIGHT));
		*/
	}

	ret = tree_delete(cur_tree, LEFT);
	VERIFY(ret != TREE_OK, SNTX_BAD, "GET T: Temporary tree hasn't been deleted properly");

	CHECK_TREE_(GET T);
	return SNTX_OK;
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int get_p(token** code, tree* my_tree, int side)
{
	CHECK_ARGS_(GET T);
	VERIFY(side != RIGHT && side != LEFT,		SNTX_BAD,		"GET P: Invalid side");

	int sign = 1;
	int ret = 0;
	while ((*code) -> type == TKN_OP)
	{
		if (INT((*code)) == '+')
		{
			sign *= 1;
			(*code)++;
			continue;
		}
		if (INT((*code)) == '-')
		{
			sign *= -1;
			(*code)++;
			continue;
		}
		VERIFY(true, SNTX_BAD, "GET P: Sign is not '+' or '-'");
	}

	tree* cur_tree = NULL;

	ret = tree_ctr(&cur_tree, my_tree -> head);
	VERIFY(ret != TREE_OK,	SNTX_CTR_FAILED, "GET P: Tree construction failed");
	ret = tree_burn(cur_tree, TR_SIGN, '*');
	VERIFY1(ret != TREE_OK,	SNTX_BURN_FAILED,"GET P: %s", sntx_errors[BURN_FAIL]);
	if (side == RIGHT)	ret = tree_add_right(my_tree, cur_tree);
	else				ret = tree_add_left (my_tree, cur_tree);
	VERIFY1(ret != TREE_OK,	SNTX_ADD_FAILED, "GET P: %s", sntx_errors[ADD_FAIL]);

	VERIFY1(ret != TREE_OK,	SNTX_ADD_FAILED, "GET P: %s", sntx_errors[ADD_FAIL]);
	

	//TREE_CALL(tree_init(&cur_tree, HEAD(my_tree), my_tree -> left, "GET P", TR_N, LEFT)); //!!!!!!!!!!!!!!!
	
	ret = tree_ctr(&cur_tree, my_tree -> head);
	VERIFY(ret != TREE_OK,	SNTX_CTR_FAILED, "GET P: Tree construction failed");
	ret = tree_burn(cur_tree, TR_N, (double)sign);
	VERIFY1(ret != TREE_OK,	SNTX_BURN_FAILED,"GET P: %s", sntx_errors[BURN_FAIL]);

	tree* child_side = NULL;

	if (side == RIGHT)	child_side = my_tree -> right;
	else				child_side = my_tree -> left;
	
	ret = tree_add_left(child_side, cur_tree);
	VERIFY1(ret != TREE_OK,	SNTX_ADD_FAILED, "GET P: %s", sntx_errors[ADD_FAIL]);
	

	if ((*code) -> type == TKN_NUM)
	{
		CALL(get_n(code, child_side));
		return SNTX_OK;
	}
	if (((*code) -> type == TKN_SEP) && *(int*)((*code) -> value) == '(')
	{
		(*code)++;
		CALL(get_e(code,  child_side, RIGHT));
		VERIFY(((*code) -> type != TKN_SEP) || *(int*)((*code) -> value) != ')', SNTX_BAD, "GET P: No closin bracket found for bracketed expression");
		
		(*code)++;
		//print_token(*code, stdout);
		CHECK_TREE_(GET P);
		return SNTX_OK;
	}
	if (((*code) -> type == TKN_ID) && ( (*(code) + 1) -> type == TKN_SEP ) && ( *(int*)((*(code) + 1) -> value) == '('))
	{
		CALL(get_f(code, child_side));
		CHECK_TREE_(GET P);
		return SNTX_OK;
	}
	if (((*code) -> type == TKN_ID))
	{
		CALL(get_v(code, child_side, RIGHT));
		CHECK_TREE_(GET P);
		return SNTX_OK;
	}

	
	VERIFY(true,	SNTX_BAD,	"GET P: Hasn't reckognized token");
	
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

int get_n(token** code, tree* my_tree)
{
	CHECK_ARGS_(GET N);

	VERIFY((*code) -> type != TKN_NUM, SNTX_BAD, "GET N: Number expected");
	int ret = 0;
	tree* cur_tree = NULL;

	//TREE_CALL(tree_init(&cur_tree, HEAD(my_tree), my_tree, "GET N", TR_N, RIGHT));
	
	ret = tree_ctr(&cur_tree, my_tree -> head);
	VERIFY(ret != TREE_OK,	SNTX_CTR_FAILED, "GET N: Tree construction failed");
	ret = tree_burn(cur_tree, TR_N, *(double*)((*code) -> value));
	VERIFY1(ret != TREE_OK,	SNTX_BURN_FAILED,"GET N: %s", sntx_errors[BURN_FAIL]);
	ret = tree_add_right(my_tree, cur_tree);
	VERIFY1(ret != TREE_OK,	SNTX_ADD_FAILED, "GET N: %s", sntx_errors[ADD_FAIL]);
	
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
	int ret = 0;
	tree* cur_tree = NULL;
	

	
	ret = tree_ctr(&cur_tree, my_tree -> head);
	VERIFY(ret != TREE_OK,	SNTX_CTR_FAILED, "GET V: Tree construction failed");
	ret = tree_burn(cur_tree, TR_V, (char*)((*code) -> value));
	VERIFY1(ret != TREE_OK,	SNTX_BURN_FAILED,"GET V: %s", sntx_errors[BURN_FAIL]);
	
	if (side == LEFT)	ret = tree_add_left (my_tree, cur_tree);
	else				ret = tree_add_right(my_tree, cur_tree);
	

	VERIFY1(ret != TREE_OK,	SNTX_ADD_FAILED, "GET V: %s", sntx_errors[ADD_FAIL]);

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
	
	VERIFY2((argc != math_funcs[i].argc), SNTX_BAD, "GET F: Invalid number of arguments, waited for [%d], got [%d]", math_funcs[i].argc, argc);

	tree* cur_tree = NULL;

	//TREE_CALL(tree_init(&cur_tree, HEAD(my_tree), my_tree, "GET F", TR_F, RIGHT));
	
	ret = tree_ctr(&cur_tree, my_tree -> head);
	VERIFY(ret != TREE_OK,	SNTX_CTR_FAILED, "GET F: Tree construction failed");
	ret = tree_burn(cur_tree, TR_F, (char*)((*code) -> value));
	VERIFY1(ret != TREE_OK,	SNTX_BURN_FAILED,"GET F: %s", sntx_errors[BURN_FAIL]);
	ret = tree_add_right(my_tree, cur_tree);
	VERIFY1(ret != TREE_OK,	SNTX_ADD_FAILED, "GET F: %s", sntx_errors[ADD_FAIL]);
	
	my_tree = cur_tree;
	(*code)++;

	for (int i = 0; i < argc; ++i)
	{
		(*code)++;
		print_token(*code, stdout);
		
		//TREE_CALL(tree_init(&cur_tree, HEAD(my_tree), my_tree, "GET F", TR_NONE, RIGHT));

		
		ret = tree_ctr(&cur_tree, my_tree -> head);
		VERIFY(ret != TREE_OK,	SNTX_CTR_FAILED, "GET F: Tree construction failed");
		ret = tree_burn(cur_tree, TR_NONE);
		VERIFY1(ret != TREE_OK,	SNTX_BURN_FAILED,"GET F: %s", sntx_errors[BURN_FAIL]);
		ret = tree_add_right(my_tree, cur_tree);
		VERIFY1(ret != TREE_OK,	SNTX_ADD_FAILED, "GET F: %s", sntx_errors[ADD_FAIL]);
		
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
	
	int ret = 0;
	
	//TREE_CALL(tree_init(&cur_tree, HEAD(my_tree), my_tree, "GET CMP", TR_NONE, LEFT));
	
	ret = tree_ctr(&cur_tree, my_tree -> head);
	VERIFY(ret != TREE_OK,	SNTX_CTR_FAILED, "GET CMP: Tree construction failed");
	ret = tree_burn(cur_tree, TR_NONE);
	VERIFY1(ret != TREE_OK,	SNTX_BURN_FAILED,"GET CMP: %s", sntx_errors[BURN_FAIL]);
	ret = tree_add_left(my_tree, cur_tree);
	VERIFY1(ret != TREE_OK,	SNTX_ADD_FAILED, "GET CMP: %s", sntx_errors[ADD_FAIL]);
	
	CALL(get_e(code, cur_tree, LEFT));
	VERIFY((*code) -> type != TKN_COMP, SNTX_BAD, "GET CMP: No comparison sign after expression");
	ret = tree_burn(cur_tree, TR_CMP, (*(int*)((*code) -> value)));
	VERIFY1(ret != TREE_OK,	SNTX_BURN_FAILED,"GET CMP: %s", sntx_errors[BURN_FAIL]);

	(*code)++;
	CALL(get_e(code, cur_tree, RIGHT));

	CHECK_TREE_(GET CMP);
	return SNTX_OK;
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
