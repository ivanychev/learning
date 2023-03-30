#include "iv_signals.h"

char logic_shift_left(unsigned char arg, int count) {
  count %= 8;
  arg = (arg << count) | (arg >> (sizeof(char) * 8 - count));
  return arg;
}

char logic_shift_right(unsigned char arg, int count) {
  count %= 8;
  return logic_shift_left(arg, 8 - count);
}

int base2(int ex) {
  int ret = 1;
  for (int i = 0; i < ex; ++i)
    ret *= 2;
  return ret;
}

void print_binary(char arg) {
  printf("%x ", arg);
  printf("0b");
  unsigned char a = 1;

  for (int i = 7; i >= 0; --i) {
    if (base2(i) - arg >= 0) {
      putchar('1');
      arg -= base2(i);
    } else
      putchar('0');
  }

  printf(" %x", arg);
  putchar('\n');
}

void dad_handler(int signal) { printf("Signal %d caught\n", signal); }

// void parent(pid_t child)
// {
// 	sigset_t sig;
// 	sigset_t empty;
// 	sigemptyset(&empty);
// 	sigfillset(&sig);
// 	sigdelset(&sig, SIGUSR1);
// 	printf("Parent here\n");
// 	sigset_t all;
// 	sigfillset(&all);

// 	struct sigaction act = {};
// 	memset(&act, 0, sizeof(act));

// 	act.sa_handler = dad_handler;
// 	act.sa_mask    = empty;

// 	sigaction(SIGUSR1, &act, NULL);
// 	int cond = sigsuspend(&sig);
// 	exit(EXIT_SUCCESS);
// }

// void child()
// {
// 	pid_t dad = getppid();
// 	sigset_t ignored;
// 	sigemptyset(&sig);
// 	sigaddset(&sig, SIGUSR1);
// 	printf("Child here\n");
// 	sleep(5);
// 	kill(dad, SIGUSR1);
// 	printf("Children out\n");
// 	exit(EXIT_SUCCESS);
// }

int main(int argc, char const *argv[]) {
  pid_t pid = fork();
  CHECK(pid != -1, "Failed to fork");
  char a = 1;
  while (a != 0) {
    unsigned short aa = 0;
    scanf("%hhu", &a);
    printf("%hhx ", a);
    a = logic_shift_left(a, 4);
    printf("%hhx\n", a);
  }
  // if (pid != 0)
  // 	parent(pid);
  // else
  // 	child();
  return 0;
}