#ifndef IVANYCHEV_DEBUG_HEADER_
#define IVANYCHEV_DEBUG_HEADER_


/*!>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//!	@par	Debug Header contains essential debug macroses.
//			WARNING: Edit this message if the header is changed
//	
//	@ver	1.0
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
!*/



//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//								VERIFICATION MACROSES
//	VERIFY  - checks the expression, returns ERR_CODE if it's true and prints message to STDOUT
//	MVERIFY - checks the expression, prints error message in STRLOG if it's true
//
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


#define __LOG_TEMPLATE(place, cond, err_code, msg)					\
	if (!(_CrtCheckMemory()))	fprintf(stdout, "Memory fucked up, line [%d]", __LINE__);\
if (cond)															\
{																	\
	fprintf(STRERR, "ERROR# ");										\
	fprintf(STRERR, msg);											\
	fprintf(STRERR, "\nFILE: %s\n%d line\n", __FILE__, __LINE__);	\
	fprintf(STRLOG, #place"_ERROR# ");								\
	fprintf(STRLOG, msg);											\
	fprintf(STRLOG, "\nFILE: %s\n%d line\n", __FILE__, __LINE__);	\
																	\
	return err_code;												\
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>



#define VERIFY1(cond, err_code, msg, arg1)							\
if (!(_CrtCheckMemory()))	fprintf(stdout, "Memory fucked up, line [%d]", __LINE__);\
if (cond)															\
{																	\
	fprintf(STRERR, "VERIFY# ");									\
	fprintf(STRERR, msg, arg1);										\
	fprintf(STRERR, "\nFILE: %s\n%d line\n", __FILE__, __LINE__);	\
	fprintf(STRLOG, "VERIFY_ERROR# ");								\
	fprintf(STRLOG, msg, arg1);										\
	fprintf(STRLOG, "\nFILE: %s\n%d line\n", __FILE__, __LINE__);	\
																	\
	return err_code;												\
}
#define VERIFY2(cond, err_code, msg, arg1, arg2)					\
	if (!(_CrtCheckMemory()))	fprintf(stdout, "Memory fucked up, line [%d]", __LINE__);\
if (cond)															\
{																	\
	fprintf(STRERR, "VERIFY# ");									\
	fprintf(STRERR, msg, arg1, arg2);								\
	fprintf(STRERR, "\nFILE: %s\n%d line\n", __FILE__, __LINE__);	\
	fprintf(STRLOG, "VERIFY_ERROR# ");								\
	fprintf(STRLOG, msg, arg1, arg2);								\
	fprintf(STRLOG, "\nFILE: %s\n%d line\n", __FILE__, __LINE__);	\
																	\
	return err_code;												\
}

#define VERIFY3(cond, err_code, msg, arg1, arg2, arg3)				\
	if (!(_CrtCheckMemory()))	fprintf(stdout, "Memory fucked up, line [%d]", __LINE__);\
if (cond)															\
{																	\
	fprintf(STRERR, "VERIFY# ");									\
	fprintf(STRERR, msg, arg1, arg2, arg3);							\
	fprintf(STRERR, "\nFILE: %s\n%d line\n", __FILE__, __LINE__);	\
	fprintf(STRLOG, "VERIFY_ERROR# ");								\
	fprintf(STRLOG, msg, arg1, arg2, arg3);							\
	fprintf(STRLOG, "\nFILE: %s\n%d line\n", __FILE__, __LINE__);	\
																	\
	return err_code;												\
}


#define   VERIFY(cond, err_code, msg) __LOG_TEMPLATE(VERIFY, cond, err_code, msg)
#define  PRECOND(cond, err_code, msg) __LOG_TEMPLATE(VERIFY, cond, err_code, msg)
#define POSTCOND(cond, err_code, msg) __LOG_TEMPLATE(VERIFY, cond, err_code, msg)


#define ERR(msg)													\
	fprintf(STRERR, "ERROR# ");										\
	fprintf(STRERR, msg);											\
	fprintf(STRERR, "\nFILE: %s\n%d line\n", __FILE__, __LINE__);	\
	fprintf(STRLOG, "PRECOND_ERROR# ");								\
	fprintf(STRLOG, msg);											\
	fprintf(STRLOG, "\nFILE: %s\n%d line\n", __FILE__, __LINE__);	\

#define _ )
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#define MVERIFY(cond, msg)											\
if (!(_CrtCheckMemory()))	fprintf(stdout, "Memory fucked up, line [%d]", __LINE__);\
if (cond)															\
{																	\
	fprintf(STRERR, "VERIFY# ");									\
	fprintf(STRERR, msg);											\
	fprintf(STRERR, "\nFILE: %s\n%d line\n", __FILE__, __LINE__);	\
	fprintf(STRLOG, "VERIFY_ERROR# ");								\
	fprintf(STRLOG, msg);											\
	fprintf(STRLOG, "\nFILE: %s\n%d line\n", __FILE__, __LINE__);	\
																	\
}

#define MVERIFY1(cond, msg, arg1)									\
if (!(_CrtCheckMemory()))	fprintf(stdout, "Memory fucked up, line [%d]", __LINE__);\
if (cond)															\
{																	\
	fprintf(STRERR, "VERIFY# ");									\
	fprintf(STRERR, msg, arg1);										\
	fprintf(STRERR, "\nFILE: %s\n%d line\n", __FILE__, __LINE__);	\
	fprintf(STRLOG, "VERIFY_ERROR# ");								\
	fprintf(STRLOG, msg, arg1);										\
	fprintf(STRLOG, "\nFILE: %s\n%d line\n", __FILE__, __LINE__);	\
																	\
																	\
}
#define MVERIFY2(cond, msg, arg1, arg2)								\
	if (!(_CrtCheckMemory()))	fprintf(stdout, "Memory fucked up, line [%d]", __LINE__);\
if (cond)															\
{																	\
	fprintf(STRERR, "VERIFY# ");									\
	fprintf(STRERR, msg, arg1, arg2);								\
	fprintf(STRERR, "\nFILE: %s\n%d line\n", __FILE__, __LINE__);	\
	fprintf(STRLOG, "VERIFY_ERROR# ");								\
	fprintf(STRLOG, msg, arg1, arg2);								\
	fprintf(STRLOG, "\nFILE: %s\n%d line\n", __FILE__, __LINE__);	\
																	\
																	\
}

#define MVERIFY3(cond, msg, arg1, arg2, arg3)						\
	if (!(_CrtCheckMemory()))	fprintf(stdout, "Memory fucked up, line [%d]", __LINE__);\
if (cond)															\
{																	\
	fprintf(STRERR, "VERIFY# ");									\
	fprintf(STRERR, msg, arg1, arg2, arg3);							\
	fprintf(STRERR, "\nFILE: %s\n%d line\n", __FILE__, __LINE__);	\
	fprintf(STRLOG, "VERIFY_ERROR# ");								\
	fprintf(STRLOG, msg, arg1, arg2, arg3);							\
	fprintf(STRLOG, "\nFILE: %s\n%d line\n", __FILE__, __LINE__);	\
																	\
																	\
}





//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//								DEBUG MODE OUTPUT
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#define DEBUG_MODE

#ifdef DEBUG_MODE
#define D_OUT(thing) fprintf(STRLOG, "DEBUG# "); fprintf(STRLOG, thing); fputc('\n', STRLOG);
#define D_OUT1(thing, arg1) fprintf(STRLOG, "DEBUG# "); fprintf(STRLOG, thing, arg1); fputc('\n', STRLOG);
#define D_OUT2(thing, arg1, arg2) fprintf(STRLOG, "DEBUG# "); fprintf(STRLOG, thing, arg1 ,arg2); fputc('\n', STRLOG);
#define D_OUT3(thing, arg1, arg2, arg3) fprintf(STRLOG, "DEBUG# "); fprintf(STRLOG, thing, arg1, arg2, arg3); fputc('\n', STRLOG);
#define DBG_FREE
#else
#define D_OUT(thing)
#define D_OUT1(thing, arg1)
#define D_OUT2(thing, arg1, arg2) 
#define D_OUT3(thing, arg1, arg2, arg3) 
#define DBG_FREE if(0)










#endif


























#endif