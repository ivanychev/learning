#ifndef __IV_STANDARD
#define __IV_STANDARD

/*
*		@brief				This header contains common macroses and constants used by Sergey Ivanychev
*		
*		@author 			Sergey Ivanychev, DCAM MIPT
*		
*		@version 			1.03
*              	
*              	@par				Changelog v.1.01
*              	        			--  Added "do while" constructions
*              	        			
*              	        			Changelog v.1.02
*              	        			--  Added *OUT macroses for fast variable printing
*						--  F_CHECK is verbose by default
*						
*						Changelog v1.03
*						--  Added iv_standard.o library declarations
*						
*/

//===============================================================================================================
//			Macroses
//===============================================================================================================

//#define DEBUG

#define F_LOCATION(stream)				\
	fprintf(stream, "File:     %s\n"		\
			"Line:     %d\n"		\
			"Function: %s\n",		\
			__FILE__,			\
			__LINE__,			\
			__PRETTY_FUNCTION__);		\
	fflush(stream);			

#define LOCATION F_LOCATION(stdout)

							
#ifdef 	DEBUG

#define OUT(str) 						printf(str);				fflush(stdout);		
#define OUT1(str, arg1)						printf(str, arg1);			fflush(stdout);
#define OUT2(str, arg1, arg2)					printf(str, arg1, arg2);		fflush(stdout);
#define OUT3(str, arg1, arg2, arg3)				printf(str, arg1, arg2, arg3);		fflush(stdout);
#define OUT4(str, arg1, arg2, arg3, arg4)			printf(str, arg1, arg2, arg3, arg4);	fflush(stdout);
#define LOC_OUT(str) 			LOCATION;		printf(str);				fflush(stdout);		
#define LOC_OUT1(str, arg1)		LOCATION;		printf(str, arg1);			fflush(stdout);
#define LOC_OUT2(str, arg1, arg2)	LOCATION;		printf(str, arg1, arg2);		fflush(stdout);


#else

#define OUT(str)			
#define OUT1(str, arg1)			
#define OUT2(str, arg1, arg2)		
#define OUT3(str, arg1, arg2, arg3)	
#define OUT4(str, arg1, arg2, arg3, arg4)
#define LOC_OUT(str) 			
#define LOC_OUT1(str, arg1)		
#define LOC_OUT2(str, arg1, arg2)	


#endif



extern char const* iv_msgs[];

enum ERROR_MESSAGES
{
	IV_PTRNULL,
	IV_FOPENFAIL,
	IV_INVALPID,
	IV_NEGSIZE,
	IV_INVALARGNUM,
	IV_ALLOCFAIL
};

enum IV_ERRORCODES
{
	IV_INVALARGS 		= -1,
	IV_STATFAIL  		= -2,
	IV_OPENFAIL  		= -3,
	IV_COPYALLOCFAIL 	= -4,
	IV_BUFALLOCFAIL		= -5,
	IV_READFAIL 		= -6,
	IV_COPYSIZEFAIL 	= -7,
	IV_NONUMBER 		= -8
};

#define F_CHECK_EXIT_CODE

// #ifdef DEBUG

#ifndef DEBUG
#undef  F_LOCATION
#define F_LOCATION(str)
#endif

#define F_CHECK(stream, cond, msg)				\
	do 							\
	{							\
		if (!(cond))					\
		{						\
			F_LOCATION(stream);			\
			fprintf(stream, "Message : %s\n", msg);	\
			fflush(stream);				\
			perror("ERRNO\t");			\
			fputc('\n', stream);			\
			F_CHECK_EXIT_CODE			\
								\
			exit(EXIT_FAILURE);			\
		}						\
	}while (0);						\


/* #else
 #define F_CHECK(stream, cond, msg)	((void)(cond))		\
 	do 							\
 	{							\
 		if (!(cond))					\
 		{						\
 			F_CHECK_EXIT_CODE			\
 			exit(EXIT_FAILURE);			\
 		}						\
 	}while (0);						\

#endif
*/

#define CALL(var, func, cond, msg)			\
do{							\
	var = func;					\
	CHECK(cond, msg);				\
} while (0);						\



#define CALLN(var, func, cond, index) CALL(func, var, cond, iv_msgs[index])
#define CHECK( cond, msg) F_CHECK(stdout, cond, msg)
#define CHECKN(cond, index) CHECK(cond, iv_msgs[index])

#ifdef DEBUG

#define F_WARN(stream, cond, msg)			\
do {							\
if (!(cond))						\
{							\
	fprintf(stream, "WARNING>>>>\n");		\
	F_LOCATION(stream);				\
	fprintf(stream, "Message:  %s\n", msg);		\
	fflush(stream);					\
	perror("ERRNO\t\t");				\
	fputc('\n', stream);				\
	fprintf(stream, ">>>>>>>>>>>\n");		\
	fflush(stream);					\
}							\
}while(0);						\

#else
#define F_WARN(stream, condm, msg)
#endif						

#define WARN(cond, msg) F_WARN(stdout, cond, msg)


#define TEMPLATE_OUT(arg, spec) 					\
do {									\
	printf("## Line %d:\n## " #arg " = %"spec "\n", __LINE__, arg);	\
	fflush(stdout);							\
} while (0);								\

#define IOUT(num) 	TEMPLATE_OUT(num, "d")
#define LOUT(num) 	TEMPLATE_OUT(num, "ld")
#define LUOUT(num) 	TEMPLATE_OUT(num, "uld")
#define DOUT(num) 	TEMPLATE_OUT(num, "lg")
#define UOUT(num) 	TEMPLATE_OUT(num, "u")
#define POUT(num) 	TEMPLATE_OUT(num, "p")
#define SOUT(num) 	TEMPLATE_OUT(num, "s")

#ifdef _STDINT_H
#define U32OUT(num) 	TEMPLATE_OUT(num, PRIu32)
#define U64OUT(num) 	TEMPLATE_OUT(num, PRIu64)
#define I32OUT(num) 	TEMPLATE_OUT(num, PRIu32)
#define I64OUT(num) 	TEMPLATE_OUT(num, PRIu64)
#endif

 

//===============================================================================================================
//===============================================================================================================

/**
 * @brief 	Gets argumented file's size
 * 
 * 
 * @param 	path
 * @param 	to_save variable to save size
 * 
 * @return 	IV_INVALARGS 	if corrupted arguments
 * 		IV_STATFAIL	if stat() failed
 * 		0 		if success
 */
int iv_getfilesize(const char* path, size_t* to_save);

/**
 * @brief Allocates buffer for file and copies file in that buffer
 * @details Buffer is allocated via malloc. Don't forget to free 
 * 
 * @param path 
 * @param copy 		where to save pointer
 * @param file_size  	where to save size
 * @return  		IV_INVALARGS 		if arguments are corrupted
 * 			IV_OPENFAIL 		if open() failed
 * 			iv_getfilesize error codes if it has failed
 * 			IV_ALLOCFAIL		if malloc() failed
 * 			IV_READFAIL 		if read() failed
 * 			IV_COPYSIZEFAILED 	if number of read bytes != file size
 * 			0 			if success
 * 			
 */
int iv_allocbuffer_copy(const char* path, char** copy, size_t* file_size);

/**
 * @brief Gets first long number from the string
 * 
 * 
 * @param save 	where to save	
 * @param str  	
 * 
 * @return 	IV_INVALARGS 	if arguments are corrupted
 * 		IV_NONUMBER 	if there's no number in string
 * 		0 		if success
 */
int iv_getlong(long* save, const char* str);

/**
 * @brief prints binary output starting from argumented pointer
 * @details maximal length of one call output is limited by IV_PRINTBIN_BUFSIZE
 * 
 * @param ptr
 * @param int how many bits to print
 * 
 * @return 	IV_INVALARGS	if arguments are corrupted
 * 		0 		if OK
 */
int iv_printbinary(char* ptr, unsigned int bits);


int iv_getsemval(int sem, int index);

#endif
