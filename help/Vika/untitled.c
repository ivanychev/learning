#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>


int main(int argc, char const *argv[])
{
	const char* filename = argv[1];   // передаем имя файла первым аргументом
	int fileid = open(filename, O_RDONLY);

	printf("fileid = %d\n", fileid);
	if (fileid == -1)
	{
		perror("Failed to open");
		return -1;
	}

	char buf[1024];
	int nbytes = 0;

	while ((nbytes = read(fileid, buf, 1024)) > 0)
	{
		if (nbytes == -1)
			return -1;
		int cond = write(STDOUT_FILENO, buf, nbytes);
	}
	return 0;
}