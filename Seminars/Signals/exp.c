#include "iv_signals.h"

void dad_handler(int signal)
{
	printf("Signal %d caught\n", signal);
}

void parent(pid_t child)
{
	sigset_t sig;
	sigset_t empty;
	sigemptyset(&empty);
	sigfillset(&sig);
	sigdelset(&sig, SIGUSR1);
	printf("Parent here\n");
	sigset_t all;
	sigfillset(&all);

	struct sigaction act = {};
	memset(&act, 0, sizeof(act));

	act.sa_handler = dad_handler;
	act.sa_mask    = empty;

	sigaction(SIGUSR1, &act, NULL);
	int cond = sigsuspend(&sig);
	exit(EXIT_SUCCESS);
}

void child()
{
	pid_t dad = getppid();
	int cond = prctl()
	sigset_t ignored;
	sigemptyset(&sig);
	sigaddset(&sig, SIGUSR1);
	printf("Child here\n");
	sleep(5);
	kill(dad, SIGUSR1);
	printf("Children out\n");
	exit(EXIT_SUCCESS);
}


int main(int argc, char const *argv[])
{
	pid_t pid = fork();
	CHECK(pid != -1, "Failed to fork");

	if (pid != 0)
		parent(pid);
	else
		child();
	return 0;
}