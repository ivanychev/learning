#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	// char* file = argv[1];
	// int open_cond = open("TEMPFILE", O_CREAT|O_EXCL, O_RDWR);
	// printf("%d\n", open_cond);

	// if (open_cond == -1)
	// 	perror("Unable to create file");
	// unlink("TEMPFILE");
	
	int mk_cond = mkfifoat(0, "/tmp/TMP_FIFO");
	printf("%d<<<<<", mk_cond);
	perror("");
	getchar();
	return 0;
}