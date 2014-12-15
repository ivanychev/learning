#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>


char* to_print = "Hello World!";

int main(int argc, char const *argv[])
{
	int len = strlen(to_print);
	int output_id = STDOUT_FILENO;
	int i = 0;
	for (i = 0; i < len; ++i)
	{
		int pid = fork();

		if (pid == 0)
		{
			putchar(to_print[i]);
			return 0;
		}
		wait(0);
	}
	putchar('\n');
	return 0;
}