#include "compiler.h"

/**
			@par					Token parcing library is contained here

			@par					V 1.01
			
**/
extern FILE* strlog;
extern FILE* strerr;



int get_token(token* save_loc, FILE* strin);

int get_token_num(token* save_loc, FILE* strin);

int get_token_got_equal(token* save_loc, FILE* strin);

int print_token(token* my_token, FILE* strout);

int token_construct(token** my_token);

int token_destruct(token* my_token);

int token_word_is_key(char* string);

int token_word_is_valid(char* string);

int token_write(token* my_token, int type, const void* source);

int get_token_got_cmp(token* save_loc, FILE* strin, int c);

int tokenize_stream(FILE* strin, token** token_stream, int* token_count);


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


int tokenize_stream(FILE* strin, token** token_stream, int* token_count)
{

	D_OUT(">>>>>>>>>>>>>>>>>TOKENIZE START<<<<<<<<<<<<<<<<<<<<<<<");
	PRECOND(strin == NULL,			CPLR_TOKENIZE_FAULT,	"TOKENIZE_STREAM(): Argumented file stream is NULL");
	PRECOND(token_stream == NULL,	CPLR_TOKENIZE_FAULT,	"TOKENIZE_STREAM(): argumented token pointer is NULL");

	token* temp_token = (token*) calloc(1, sizeof(token));
	assert(temp_token);

	int ret = token_construct(&temp_token);
	VERIFY(ret != TOKEN_OK,			CPLR_TOKENIZE_FAULT,	"TOKENIZE_STREAM(): Temporary token construction fault");

	ret = get_token(temp_token, strin);
	VERIFY(ret != TOKEN_OK,			CPLR_TOKENIZE_FAULT,	"TOKENIZE_STREAM(): get_token() fail");
	
	int i = 1;

	while (temp_token -> type != TKN_END)
	{
		ret = get_token(temp_token, strin);
		VERIFY(ret != TOKEN_OK,		CPLR_TOKENIZE_FAULT,	"TOKENIZE_STREAM(): get_token() fail");
		i++;
	}
	ret = token_destruct(temp_token);
	temp_token = NULL;

	assert(fseek(strin, 0, SEEK_SET) == 0);
	
	char temp_word[MAXLINE] = {};

	VERIFY(ret != TOKEN_OK,			CPLR_TOKENIZE_FAULT,	"TOKENIZE_STREAM(): token_destruct() fail");
	
	ret = fscanf_s(strin, "%s", temp_word, MAXLINE);
	assert(ret);

	(*token_stream) = (token*) calloc(i, sizeof(token));
	assert(*token_stream);
	//printf("[%08x]", (*token_stream));
	int i_copy = i;											//Verifying, that we're going to get the same ammount of tokens
		i = 0;

	while ((*token_stream + i - 1) -> type != TKN_END || i == 0)
	{
		ret = get_token((*token_stream + i), strin);
		print_token(*token_stream + i, strlog);
		VERIFY(ret != TOKEN_OK,		CPLR_TOKENIZE_FAULT,	"TOKENIZE_STREAM(): get_token() fail");
		i++;
	}

	VERIFY2(i != i_copy,				CPLR_TOKENIZE_FAULT,	"TOKENIZE_STREAM(): i and i_copy don't match, i = %d, i_copy = %d", i , i_copy);
	
	D_OUT("LIST OF SCANNED TOKENS BEGIN>>>>>>>>>>>>>>>>>>>>>>\n");
	for (i = 0; i < i_copy; i++) 
	{
		fprintf(strlog, "%d", i);
		print_token(*token_stream + i, strlog);
	}
	D_OUT("LIST OF SCANNED TOKENS FINISH<<<<<<<<<<<<<<<<<<<<<<\n");
	

	D_OUT1(">>>>>>>>>>>>>>>>>TOKENIZE FINISHED, GOT %d TOKENS<<<<<<<<<<<<<<<<<", i);
	*token_count = i;
	printf("[%08x]", (*token_stream));
	return CPLR_OK;
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

int token_construct(token** my_token)
{
	D_OUT("Token constructing...\n");
	VERIFY(my_token == NULL, TOKEN_BAD, "TOKEN_CONSTRUCT(): token pointer is NULL");
	(*my_token) = (token*) calloc(1, sizeof(token));
	assert(*my_token);
	(*my_token) -> type  = 0;
	(*my_token) -> value = NULL;

	D_OUT1("done -> %08x\n", *my_token);
	printf(">>>[%08x]\n", *my_token);
	return TOKEN_OK;
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

int token_destruct(token* my_token)
{
	D_OUT1("Token [%08x] destructing...\n", my_token);
	VERIFY( my_token == NULL, TOKEN_BAD,  "TOKEN_DESTRUCT(): argumented pointer is null");
	
	
	my_token -> type = POISON;
	if (my_token -> value != NULL) 
	{
		DBG_FREE fprintf(stdout, "[%08x] token.cpp, token_destruct, my_token -> value\n", my_token -> value);
		free(my_token -> value);
	}
	my_token -> value = NULL;
	DBG_FREE fprintf(stdout, "[%08x] token.cpp, token_destruct, my_token\n", my_token);

	free(my_token);
	my_token = NULL;

	D_OUT("done\n");
	return TOKEN_OK;
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#define CHECK_KEY_(word, key) (!(strcmp(word, _strlwr(#key))))? WORD_##key :

int token_word_is_key(char* word)
{
	D_OUT1("%s", word);
	int c = word[0];
	if (c != 'i' && c != 'e' && c != 'w' && c != 'd' && c != 'u' && c != 'p') return 0;
	
	int ret =		CHECK_KEY_(word, if)
					CHECK_KEY_(word, else)
					CHECK_KEY_(word, while)
					CHECK_KEY_(word, do)
					CHECK_KEY_(word, until)
					CHECK_KEY_(word, print)
					CHECK_KEY_(word, print_val)
					0;
	return			ret;			
}


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


int token_word_is_valid(char* string)
{
	char* ptr = string;
	while (*ptr != '\0') 
	{
		if (   !(isalpha(*ptr) || *(ptr) == '_' )   ) return 0;
		ptr++;
	}
	return 1;
}



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#define TOKEN_BURN(token_type, ptr_type)														\
	my_token -> type	     = token_type;														\
	my_token -> value    = calloc(1, sizeof(ptr_type));											\
	assert(my_token -> value);																	\
	*(((ptr_type*)my_token -> value)) = *((ptr_type*)source);									\


int token_write(token* my_token, int type, const void* source)
{
	D_OUT2("Writing to [%08x] token, type = %d\n", my_token, type);
	int c = 0;
	int str_len = 0;
	switch (type)
	{
	case TKN_OP:
		c = *((int*)source);
		D_OUT1("Got [%c]", c);
		VERIFY1((c != '+' && c != '-' && c != '*' && c != '/'),	TOKEN_BAD, "TOKEN_WRITE(): Expected +-//*, got [%c]", c);
		TOKEN_BURN(TKN_OP, int);
		break;

	case TKN_COMP:
		c = *((int*)source);
		D_OUT1("Got [%d] code", c);
		VERIFY1( (!(c >= CMP_B && c <= CMP_NE)),					TOKEN_BAD, "TOKEN_WRITE(): got [%d]", c);	
		TOKEN_BURN(TKN_COMP, int);
		break;

	case TKN_ID:
		str_len = strlen((char*)source);
		
		VERIFY1(str_len > MAXLINE,								TOKEN_BAD, "TOKEN_WRITE(): got too big identificator \n%50s", (char*)source);
		D_OUT1("Got [%s]", (char*)source);
		VERIFY1(token_word_is_valid((char*)source) == 0,			TOKEN_BAD, "TOKEN_WRITE(): got invalid identificator only [-_A-Za-z] allowed, '_' can't be first, got [%s]", (char*)source);
		VERIFY1(token_word_is_key  ((char*)source) != 0,			TOKEN_BAD, "TOKEN_WRITE(): inputted identificator is key word, got [%s]", 	(char*)source);
		
		my_token -> type = type;
		my_token -> value =  calloc(str_len + 2, sizeof(char));
		assert(my_token -> value);
		strcpy((char*)my_token -> value, (char*)source);
		break;

	case TKN_NUM:
		D_OUT1("Got [%lg]", *((double*)source));
		TOKEN_BURN(TKN_NUM, double);
		break;

	case TKN_SEP:
		c = *((char*)(source));
		D_OUT1("Got [%c]", c);
		VERIFY1((c!= ',' && c != ';' && c != '(' && c != ')' && c != '{' && c != '}'),	TOKEN_BAD, "TOKEN_WRITE(): Expected ;{}(), got [%c]", c);
		TOKEN_BURN(TKN_SEP, int);
		break;

	case TKN_ASSGN:
		c = *((int*)source);
		D_OUT1("Got [%d] code", c);
		VERIFY1( (!(ASSGN <= c && c <= ASSGN_DIV)),				TOKEN_BAD, "TOKEN_WRITE(): input assign code is wrong [%d]", c);
		TOKEN_BURN(TKN_ASSGN, int);
		break;

	case TKN_STR:
		str_len = strlen((char*)source);
		
		VERIFY1(str_len > MAXLINE,								TOKEN_BAD, "TOKEN_WRITE(): got too big string \n%50s", (char*)source);
		D_OUT1("Got [%s]", (char*)source);
		my_token -> type = type;
		my_token -> value =  calloc(str_len + 2, sizeof(char));
		assert(my_token -> value);
		strcpy((char*)my_token -> value, (char*)source);
		break;	

	case TKN_END:
		c = *((int*)source);
		D_OUT1("Got [%d]", c);
		VERIFY1(c != 0,											TOKEN_BAD, "TOKEN_WRITE(): strange end [%c]", *(char*)source);
		TOKEN_BURN(TKN_END, int);
		break;	
	case TKN_KEY:
		c = *((int*)source);
		D_OUT1("Got [%d] code", c);my_token -> type = type;
		VERIFY1( (!(WORD_if <= c && c <= WORD_print_val)),		TOKEN_BAD, "TOKEN_WRITE(): input key code is wrong [%d]", c);
		TOKEN_BURN(TKN_KEY, int);
		break;
	default:
		VERIFY1(true, TOKEN_BAD, "Invalid type of token type, got [%d]", type);
		break;	

	}
	D_OUT("Token written successfully");
	return TOKEN_OK;
	
}

#undef TOKEN_BURN


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


int get_token_got_op(token* save_loc, FILE* strin, int c)
{
	assert(save_loc);
	assert(strin);
	int drop = 0;
	int cc = 0;
	while (isspace(cc = getc(strin)));																	D_OUT1("Checking next symbol, it's [%c]", cc);
		if (cc == '=')
		{
																										D_OUT("It's assignition");
			switch (c)
			{
			case '+':
				drop = ASSGN_ADD;
				return token_write(save_loc, TKN_ASSGN, (void*)(&drop));
				break;
			case '-':
				drop = ASSGN_SUB;
				return token_write(save_loc, TKN_ASSGN, (void*)(&drop));
				break;
			case '*':
				drop = ASSGN_MUL;
				return token_write(save_loc, TKN_ASSGN, (void*)(&drop));
				break;
			case '/':
				drop = ASSGN_DIV;
				return token_write(save_loc, TKN_ASSGN, (void*)(&drop));
				break;
			default: assert(("Unexpected happened", 0));
			}
		}
		else
		{
			ungetc(cc, strin);																		D_OUT("It's not assignition");
			return token_write(save_loc, TKN_OP, (void*)(&c));
		}
		return TOKEN_OK;
}


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


int get_token_got_equal(token* save_loc, FILE* strin)
{
	int cc = 0;
	while (isspace(cc = getc(strin)));																				D_OUT("Got '=', checking next symbol...");

	if (cc == '=')
	{
		int drop = CMP_E;																			D_OUT("Found '==', saving token...");
		return token_write(save_loc, TKN_COMP, (void*)(&drop));
	}																								D_OUT1("Found [%c], it's assignition", cc);
	ungetc(cc, strin);																
	int drop = ASSGN;
	return token_write(save_loc, TKN_ASSGN, (void*)(&drop));
}


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


int get_token_num(token* save_loc, FILE* strin)
{
																									D_OUT("Scanning for number...")
	int c = 0;
	while (isspace(c = getc(strin)));																			

	if (!('0' <= c && c <= '9')) return TOKEN_BAD;

	double res = 0;																					D_OUT2("Got [%c], result = %lg", c, res);

	while ('0' <= c && c <= '9') 
	{
		res = 10 * res + (c - '0');
		while (isspace(c = getc(strin)));															D_OUT2("Got [%c], result = %lg", c, res);
	}

	if (c != '.')
	{
		ungetc(c, strin);																			D_OUT1("Done, result is %lg", res);
		return token_write(save_loc, TKN_NUM, (void*)(&res));	
	}
	else 
	{
		while (isspace(c = getc(strin)));															D_OUT2("Got [%c], result = %lg", c, res);
	}

	int i = 0;
	while ('0' <= c && c <= '9') 
	{
		res += (double)(c - '0') * powf(10.0, (float)(-(++i)));
		while (isspace(c = getc(strin)));															D_OUT2("Got [%c], result = %lg", c, res);
	}
	ungetc(c, strin);

	return token_write(save_loc, TKN_NUM, (void*)(&res));

}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<



int get_token_got_cmp(token* save_loc, FILE* strin, int c)
{
	int cc = 0;
	while (isspace(cc = getc(strin)));																D_OUT2("First - [%c], Analysing next symbol, it's [%c]", c, cc)
	if (cc != '=' && c == '!') 
	{
		ERR("GET_TOKEN_GOT_CMP: Unknown operator '!'");
		return TOKEN_BAD;
	}
	int type = 0;

	if (c == '>' && cc != '=') type = CMP_A;
	if (c == '<' && cc != '=') type = CMP_B;
	if (c == '>' && cc == '=') type = CMP_AE;
	if (c == '<' && cc == '=') type = CMP_BE;
	if (c == '!' && cc == '=') type = CMP_NE;														
	if (cc != '=') ungetc(cc, strin);

	return token_write(save_loc, TKN_COMP, (void*)(&type));	
}


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


int get_token(token* save_loc, FILE* strin)
{
																									
	
	//VERIFY(token_construct(save_loc) != TOKEN_OK, TOKEN_BAD, "GET_TOKEN(): Error while creating token");
	int c = 0;
	while (isspace(c = getc(strin)));	
	D_OUT("Getting token...");
	D_OUT1("Got [%c] character", c);
	if (isdigit(c))
	{
		ungetc(c, strin);																			D_OUT("Number recognized");
		return get_token_num(save_loc, strin);

	}

	if (c == '+' || c == '-' || c == '*' || c == '/')
	{																								D_OUT("It's operator, calling got_op()...");
		return get_token_got_op(save_loc, strin, c);												
	}

	if (c == '=')
	{																								D_OUT("It's [=], calling got_equal()...");
		return get_token_got_equal(save_loc, strin);
	}

	if (c == '>' || c == '<' || c == '!')
	{																								D_OUT1("It's [%c], that's supposed to be compare operator, calling got_cmp()...", c);
		return get_token_got_cmp(save_loc, strin, c);
	}

	if (c == '(' || c == ')' || c == '{' || c == '}' || c == ';' || c == ',')
	{																								D_OUT1("It's [%c], separator", c);
		return token_write(save_loc, TKN_SEP, (void*)(&c));
	}

	if (c == '\"')
	{
		char word[MAXLINE] = {};																	D_OUT("Found \", string in front...");
		int i = 0;
		int cc = 0;
		while ((c = getc(strin)) != '"' && c != EOF && c!= '\0' && i < MAXLINE - 1) 
		{
			if (c == '\\')
			{
				cc = getc(strin);
				switch (cc)
				{
				case '\\': c = '\\'; break;
				case 'n':  c = '\n'; break;
				case 't':  c = '\t'; break;
				default:			 break;
				}
			}

			word[i++] = c;
		}
		VERIFY(c == EOF , TOKEN_BAD, "GET_TOKEN(): Unexpected end of file");
		word[i] = '\0';																				D_OUT1("Scanned string [%s]", word);
		return token_write(save_loc, TKN_STR, (void*)(word));
	}

	if (isalpha(c) || c == '_')
	{																								D_OUT1("Found letter [%c], looking for identificator...", c);
		char word[MAXLINE] = {};
		int i = 0;
		while ((isalpha(c) || c == '_') && i < MAXLINE - 1) 
		{
			word[i++] = c;
			while (isspace(c = getc(strin)));
		}
		//VERIFY(c == EOF, TOKEN_BAD, "GET_TOKEN(): Unexpected end of file");
		word[i] = '\0';
		ungetc(c, strin);																			D_OUT1("Scanned identificator is [%s]", word);
		D_OUT1("%s", word);
		int is_key = token_word_is_key(word);
		if (is_key == 0)  return token_write(save_loc, TKN_ID, (void*)(word));
		else return token_write(save_loc, TKN_KEY, (void*)(&is_key));
	}

	if (c == EOF)
	{																								D_OUT("Found end of file");
		int __ = 0;
		return token_write(save_loc, TKN_END, (void*)(&__));
	}
																									D_OUT("Scanned symbol is strange, terminating...");
	return TOKEN_BAD;
}


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

int print_token(token* my_token, FILE* strout)
{
	assert(my_token);
	assert(strout);

	fprintf(strout, "type: [%d],", my_token -> type);

	switch (my_token -> type)
	{
	case TKN_OP:		fprintf(strout, "value: [%c]\n",  *((int*)   (my_token -> value))); break;
	case TKN_COMP:		fprintf(strout, "value: [%d]\n",  *((int*)   (my_token -> value))); break;
	case TKN_ID:		fprintf(strout, "value: [%s]\n",   ((char*)  (my_token -> value))); break;
	case TKN_NUM:		fprintf(strout, "value: [%lg]\n", *((double*)(my_token -> value))); break;
	case TKN_SEP:		fprintf(strout, "value: [%c]\n",  *((char*)  (my_token -> value))); break;
	case TKN_ASSGN:		fprintf(strout, "value: [%d]\n",  *((int*)   (my_token -> value))); break;
	case TKN_STR:		fprintf(strout, "value: [%s]\n",   ((char*)  (my_token -> value))); break;
	case TKN_END:		fprintf(strout, "value: [%d]\n",  *((int*)   (my_token -> value))); break;
	case TKN_KEY:		fprintf(strout, "value: [%s]\n",   ((char*)  (my_token -> value))); break;
	default:			assert(0);//VERIFY1(true,		TOKEN_BAD,		"PRINT TOKEN: GOT WRONG TOKEN, TYPE [%d]", my_token -> type);
	}

	return TOKEN_OK;
}