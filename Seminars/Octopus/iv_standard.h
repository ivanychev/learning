#ifndef __IV_STANDARD
#define __IV_STANDARD

/*
*		@brief				This header contains common macroses and constants used by Sergey Ivanychev
*		
*		@author 			Sergey Ivanychev, DCAM MIPT
*		
*		@version 			1.01
*              	
*              	@par				Changelog v.1.01
*              	        			--  Added "do while" constructions
*		
*/

//===============================================================================================================
//			Macroses
//===============================================================================================================

#define DEBUG

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

#define OUT(str)				if (0)			printf(str);
#define OUT1(str, arg1)				if (0)			printf(str, arg1);
#define OUT2(str, arg1, arg2)			if (0)			printf(str, arg1, arg2);
#define OUT3(str, arg1, arg2, arg3)		if (0)			printf(str, arg1, arg2, arg3);
#define OUT4(str, arg1, arg2, arg3, arg4)	if (0)			printf(str, arg1, arg2, arg3, arg4);
#define LOC_OUT(str) 				if (0)			printf(str);				
#define LOC_OUT1(str, arg1)			if (0)			printf(str, arg1);	
#define LOC_OUT2(str, arg1, arg2)		if (0)			printf(str, arg1, arg2);


#endif

enum ERROR_MESSAGES
{
	IVPTRNULL,
	IVFOPENFAIL,
	IVINVALPID,
	IVNEGSIZE,
	IVINVALARGNUM,
	IVALLOCFAIL
};

char const* iv_msgs[] = {
	"Argumented pointer is null",
	"Failed to open the file",
	"Invalid pid",
	"Size is below zero",
	"Invalid number of arguments",
	"Memory allocation failed"
};

#define F_CHECK_EXIT_CODE

#ifdef DEBUG

#define F_CHECK(stream, cond, msg)				\
	do 							\
	{							\
		if (!(cond))					\
		{						\
			F_LOCATION(stream);			\
			fprintf(stream, "Message:  %s\n", msg);	\
			fflush(stream);				\
			perror("ERRNO\t\t");			\
			fputc('\n', stream);			\
			F_CHECK_EXIT_CODE			\
								\
			exit(EXIT_FAILURE);			\
		}						\
	}while (0);						\

#else

#define F_CHECK(stream, cond, msg)				\
	do 							\
	{							\
		if (!(cond))					\
		{						\
			F_CHECK_EXIT_CODE			\
			exit(EXIT_FAILURE);			\
		}						\
	}while (0);						\

#endif


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


//===============================================================================================================
//===============================================================================================================


#endif