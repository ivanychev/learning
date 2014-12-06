/*
*	@mainpage
*	
*	@author			Sergey Ivanychev
*				DCAM MIPT, 376 group
*	
*	@version		v 0.1.1
*
*/

#include "iv_signals.h"


//======================================================================================================
//			GLOBALS
//======================================================================================================


int global_fileid = 0;

int global_child_terminated = 0;

int global_last_bit = 0;


//======================================================================================================
//======================================================================================================
 

int main(int argc, char const *argv[])
{
	if (argc != 2)
	{
		printf("Invalid number of arguments. Terminating...\n");
		exit(EXIT_FAILURE);
	}
	int cond = 0;
	
	sigset_t origin;
	cond = sigfillset(&origin);
	CHECK(cond != -1, "");
	cond = sigprocmask(SIG_BLOCK, &origin, NULL);
	CHECK(cond != -1, "");


	pid_t ret = fork();
	CHECK(ret != -1, "Failed to fork");

	if (ret == 0)
		sleep(1);

	if (ret == 0)
		go_child(argv[1]);
	else
		go_parent(ret);
	return 0;
}

//======================================================================================================
//	CHILD PART
//======================================================================================================

void go_child(char const* filename)
{
	OUT("[CHILD]  Born\n");
	CHECKN(filename != 0, IVPTRNULL);
	int fileid = open(filename, O_RDONLY);
	CHECKN(fileid != -1, IVFOPENFAIL);
	global_fileid = fileid;

	pid_t dad = getppid();
	int cond = prctl(PR_SET_PDEATHSIG, SIGTERM, 0, 0, 0);
	CHECK(cond != -1, "Failed to set signal for the death of the parent");
	
	cond = child_sigterm_set();
	CHECK(cond != -1, "");
	cond = child_sigusr1_set();
	CHECK(cond != -1, "");


	char buf[BUFSIZE] = {};	
	sigset_t ignored;
	cond = sigfillset(&ignored);
	CHECK(cond != -1, "");
	cond = sigdelset( &ignored, SIGUSR1);
	CHECK(cond != -1, "");
	cond = sigdelset( &ignored, SIGTERM);
	CHECK(cond != -1, "");

	OUT("[CHILD]  Prepared\n");

	cond = sigsuspend(&ignored);
	OUT("[CHILD]  Receieved\n");

	while ((cond = read(fileid, buf, BUFSIZE)) != 0)
	{
		int verify = send(dad, buf, cond, &ignored);
		OUT("[CHILD]  Sent bit\n");
		CHECK(verify != -1, "Sending buffer failed");
	}
	clear_child();

	OUT("Child exits successfully");
	exit(EXIT_SUCCESS);
}

#undef  F_CHECK_EXIT_CODE

//======================================================================================================
//======================================================================================================

#define F_CHECK_EXIT_CODE return -1;

int send(pid_t dad, void* buf, long len, const sigset_t* ignored)
{
	
	CHECKN(dad >= 0,    IVINVALPID);
	CHECKN(buf != NULL, IVPTRNULL);
	CHECKN(len >= 0,    IVNEGSIZE);
	int bit  = 0;
	int cond = 0;

	for (int i = 0; i < len; ++i)
	{
		for (int j = 0; j < BITSPERBYTE; j++)
		{
			bit  = getbit(buf, i, j);
			cond = sendbit(dad, bit, ignored);
			CHECK(cond != -1, "Failed to send bit");
		}
	}
	return 0;
}

//======================================================================================================
//======================================================================================================

int getbit(void* ptr, unsigned offset, unsigned bit_index)
{
	assert(ptr);
	unsigned char that_byte = *((char*)ptr + offset);
	that_byte >>= bit_index;
	that_byte  &= (0x01);		// 0b00000001
	return (int)that_byte;
}

int sendbit(pid_t dad, int bit, const sigset_t* now)
{
	int cond = 0;

	switch(bit)
	{
	case 0:
		cond = kill(dad, SIGUSR1);
		CHECK(cond != -1, "");
		cond = sigsuspend(now);
//		CHECK(cond != -1, "Failed to send a signal");
		break;
	case 1:
		cond = kill(dad, SIGUSR2);
		CHECK(cond != -1, "");
		cond = sigsuspend(now);
//		CHECK(cond != -1, "Failed to send a signal");
		break;
	default:
		OUT1("Argumented bit is %d\n", bit);
		return -1;
	}
	return 0;
}

//======================================================================================================
//======================================================================================================

void child_sigterm_handler(int sigid)
{
	clear_child();
	OUT("[CHILD]  SIGTERM Caught\n");
	exit(EXIT_SUCCESS);
}

void child_sigusr1_handler(int sigid)
{
	OUT("[CHILD]  SIGUSR1 Caught\n");
}

int child_sigterm_set()
{
	struct sigaction term_act;
	sigset_t mask;
	sigfillset(&mask);
	memset(&term_act, 0, sizeof(term_act));
	term_act.sa_handler = child_sigterm_handler;
	term_act.sa_mask  = mask;
	int cond = sigaction(SIGTERM, &term_act, NULL);
	CHECK(cond != -1, "Failed to set child action for SIGTERM");

	return 0;
}

int child_sigusr1_set()
{
	struct sigaction term_act;
	sigset_t mask;
	sigfillset(&mask);
	memset(&term_act, 0, sizeof(term_act));
	term_act.sa_handler = child_sigusr1_handler;
	term_act.sa_mask = mask;
	int cond = sigaction(SIGUSR1, &term_act, NULL);
	CHECK(cond != -1, "Failed to set child action for SIGUSR1");

	return 0;
}

void clear_child()
{
	close(global_fileid);
}

#undef  F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE

//======================================================================================================
//		PARENT PART
//======================================================================================================

void go_parent(pid_t child)
{
//	OUT("[PARENT] Born\n");
	sigset_t wait;
	sigset_t blocked;
	int cond = 0;
	set_block_mask(&blocked);
	set_wait_mask(&wait);
	cond = parent_set_handlers(blocked);
	CHECK(cond != -1, "Failed to set handlers for parent");

	OUT("[PARENT] Prepared\n");
	cond = sigprocmask(SIG_BLOCK, &blocked, NULL);


	OUT("[PARENT] Set mask\n");
	char buf[BUFSIZE] = {};
	cond = kill(child, SIGUSR1);
	OUT("[PARENT] Sent signal\n");
	unsigned long nbits = 0;

	while (nbits < BUFSIZE * BITSPERBYTE)
	{
		cond = sigsuspend(&wait);
		OUT2("[PARENT] TERM[%d] LSTBIT[%d]\n",
			global_child_terminated,
			global_last_bit);
		if (global_child_terminated == 1)
		{
			OUT1("[PARENT] Printing result, nbits = %lu\n", nbits);
			print_buf(buf, nbits);
			break;
		}
		writebit(buf, nbits++);
		if (nbits == BUFSIZE * BITSPERBYTE)
		{
			print_buf(buf, nbits);
			nbits = 0;
		}
		kill(child, SIGUSR1);
	}

	exit(EXIT_SUCCESS);
}

#undef  F_CHECK_EXIT_CODE

//======================================================================================================
//======================================================================================================

#define F_CHECK_EXIT_CODE return -1;

char cicular_shift_left(unsigned char arg, int count)
{
	count %= 8;
	arg = (arg << count) | (arg >> (sizeof(char)*8 - count));
	return arg;
}

char cicular_shift_right(unsigned char arg, int count)
{
	count %= 8;
	return cicular_shift_left(arg, 8 - count);
}

//======================================================================================================
//======================================================================================================

int writebit(char* buf, unsigned long index)
{
	CHECKN(buf, IVPTRNULL);
	CHECK(global_last_bit == 0 || global_last_bit == 1,
		"Invalid value of global_last_bit");
	unsigned long byte_offset = index / 8;
	unsigned      bit_index   = index % 8;
	unsigned char new_byte 	  = buf[byte_offset];
	// OUT1("[PARENT] Index = %lu\n", index);
	// OUT1("[PARENT] Was %hhx\n", new_byte);
	// OUT1("[PARENT] Last bit = %d\n", global_last_bit);

	new_byte = cicular_shift_right(new_byte, bit_index);
//	OUT1("[PARENT] Shifted right      = %hhx\n", new_byte);	
	new_byte = new_byte &  0xfe; // 0b11111110
//	OUT1("[PARENT] Removed last       = %hhx\n", new_byte);
	new_byte = new_byte | ((unsigned char)global_last_bit);
//	OUT1("[PARENT] Attached last read = %hhx\n", new_byte);
	new_byte = cicular_shift_left(new_byte, bit_index);
//	OUT1("[PARENT] Shifted left       = %hhx\n", new_byte);

	buf[byte_offset] = new_byte;
//	OUT1("[PARENT] Become %hhx\n", new_byte);
//	getchar();
	return 0;
}

int print_buf(char* buf, unsigned long nbits)
{
	CHECKN(buf, IVPTRNULL);
	unsigned long byte_offset = nbits / 8;
	int cond = write(STDOUT_FILENO, buf, byte_offset);
	fflush(stdout);

//	OUT1("[PARENT] Written %d bytes\n", cond);
	CHECK(cond == byte_offset, "Written bytes and expected are different");

	return 0;
}

//======================================================================================================
//======================================================================================================

void parent_sigusr1_handler(int signal)
{
	global_last_bit = 0;
}

void parent_sigusr2_handler(int signal)
{
	global_last_bit = 1;
}

void parent_sigchld_handler(int signal)
{
	global_child_terminated = 1;
}

int parent_set_handlers(sigset_t blocked)
{
	struct sigaction par_usr1;
	struct sigaction par_usr2;
	struct sigaction par_chld;
	memset(&par_usr1, 0, sizeof(struct sigaction));
	memset(&par_usr2, 0, sizeof(struct sigaction));
	memset(&par_chld, 0, sizeof(struct sigaction));

	par_usr1.sa_handler = parent_sigusr1_handler;
	par_usr2.sa_handler = parent_sigusr2_handler;
	par_chld.sa_handler = parent_sigchld_handler;
	par_usr1.sa_mask    = blocked;
	par_usr2.sa_mask    = blocked;
	par_chld.sa_mask    = blocked;

	int cond = 0;

	cond = sigaction(SIGUSR1, &par_usr1, NULL);
	CHECK(cond != -1, "Failed to set action for SIGUSR1");
	cond = sigaction(SIGUSR2, &par_usr2, NULL);
	CHECK(cond != -1, "Failed to set action for SIGUSR2");
	cond = sigaction(SIGCHLD, &par_chld, NULL);
	CHECK(cond != -1, "Failed to set action for SIGCHLD");

	return 0;
}


//======================================================================================================
//======================================================================================================


int set_block_mask(sigset_t* blocked)
{
	assert(blocked);
	int cond = 0;
	cond = sigfillset(blocked);
	cond = sigdelset( blocked,   SIGTERM);

	return 0;
}

int set_wait_mask(sigset_t* wait)
{
	assert(wait);
	int cond = 0;
	cond = sigfillset(wait);
	cond = sigdelset( wait, SIGCHLD);
	cond = sigdelset( wait, SIGUSR1);
	cond = sigdelset( wait, SIGUSR2);

	return 0;
}

