#define _XOPEN_SOURCE
#include <unistd.h>


int main(int argc, char const *argv[])
{
	int i = 0;
	int sym = 0;

	for (int i = 1; i < argc; ++i)
	{
		if (argv[i][0] == '-' && argv[i][1] == 's')
			sym = 1;
	}

	const char* file1 = argv[1];
	const char* file2 = argv[2];

	if (sym == 0)
		link(file1, file2);
	else
		symlink(file1, file2);
	return 0;
}