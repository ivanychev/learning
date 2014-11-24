#include "iv_signals.h"

int global_fileid = 0;

void go_child(char const* filename);

void go_parent(pid_t child);

int getbit(void* ptr, unsigned offset, unsigned bit_index);

int send(pid_t dad, void* buf, long len);

int child_sigterm_set();

void clear_child();



int main(int argc, char const *argv[])
{
	if (argc != 2)
	{
		printf("Invalid number of arguments. Terminating...\n");
		exit(EXIT_FAILURE);
	}

	pid_t ret = fork();
	CHECKN(ret != -1, "Failed to fork");

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
	CHECKN(filename != 0, IVPTRNULL);
	int fileid = open(filename, O_RDONLY);
	CHECKN(fileid == -1, IVFOPENFAIL);
	global_fileid = fileid;

	pid_t dad = getppid(PR_SET_PDEATHSIG, SIGTERM);
	CHECK(dad != -1, "Failed to set signal for the death of the parent");
	
	cond = child_sigterm_set();
	CHECK(cond != -1, "");

	char buf[BUFSIZE] = {};	
	sigset_t ignored;
	sigfillset(&ignored);
//	sigdelset( &ignored, SIGUSR1);
//	sigdelset( &ignored, SIGTERM);
	
	cond = sigprocmask(SIG_BLOCK, &ignored, NULL);
	CHECK(cond != -1, "Failed to set mask");

	int cond = 0;
	while ((cond = read(fileid, buf, BUFSIZE)) != -1)
	{
		int verify = send(dad, buf, cond, fileid);
		CHECK(verify != -1, "Sending buffer failed");
	}
	clear_child();
	exit(EXIT_SUCCESS);
}

#undef  F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE return -1;

int send(pid_t dad, void* buf, long len)
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
			cond = send_bit(dad, bit);
			CHECK(cond != -1, "Failed to send bit");
		}
	}
	return 0;
}

int getbit(void* ptr, unsigned offset, unsigned bit_index)
{
	assert(ptr);
	unsigned char that_byte = *((char*)ptr + offset);
	that_byte >>= bit_index;
	that_byte  &= (0xfe);		// 0b11111110
	return (int)that_byte;
}

int sendbit(pid_t dad, int bit)
{
	int cond = 0;
	sigset_t now;
	cond = sigprocmask(SIG_SETMASK, &now, NULL);
	CHECK(cond != -1, "Failed to get current signal mask");

	switch(bit)
	{
	case 0:
		cond = kill(dad, SIGUSR1);
		cond = sigsuspend(&now);
//		CHECK(cond != -1, "Failed to send a signal");
		break;
	case 1:
		cond = kill(dad, SIGUSR2);
		cond = sigsuspend(&now);
//		CHECK(cond != -1, "Failed to send a signal");
		break;
	default:
		OUT1("Argumented bit is %d\n", bit);
		return -1;
	}
	return 0;
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
	memset(term_act, 0, sizeof(term_act));
	term_act.sa_handler = child_sigusr1_handler;
	term_act.sa_mask = mask;
	int cond = sigaction(SIGUSR1, &term_act, NULL);
	CHECK(cond != -1, "Failed to set child action for SIGUSR1");

	return 0;
}

void child_sigterm_handler(int sigid)
{
	clear_child();
	exit(EXIT_SUCCESS);
}

void child_sigusr1_handler(int sigid)
{}

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
	sigset_t chld_look;
	int cond = sigfillset(&chld_look);
	CHECK(cond != -1, "Failed to set mask");
	    cond = sigdelset( &chld_look, SIGCHLD);
	CHECK(cond != -1, "Failed to set mask");

}