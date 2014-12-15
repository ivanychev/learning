#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>


//=======================================================================================================================


const char* FIFO_NAME = "fifo";
const char* COPY_NAME = "copied";
const int   BUFSIZE   = 4 * 1024;

//=======================================================================================================================

int receiver();

int sender(const char* filename);

int open_fifo(int flag);

//=======================================================================================================================

int main(int argc, char const *argv[])
{
	if (argc > 2)
		exit(EXIT_FAILURE);

	if (argc == 1)
		receiver();
	else
		sender(argv[1]);
	return 0;
}

//=======================================================================================================================

int open_fifo(int flag)
{
	int cond = mkfifo(FIFO_NAME, 0600);

	if (cond == -1 && errno != EEXIST)
		exit(EXIT_FAILURE);
	int fifoid = open(FIFO_NAME, flag);
	if (fifoid == -1)
	{
		unlink(FIFO_NAME);
		exit(EXIT_FAILURE);
	}
	return fifoid;
}

//=======================================================================================================================

int sender(const char* filename)
{
	assert(filename);

	int fifoid = open_fifo(O_WRONLY);

	int fileid = open(filename, O_RDONLY);
	if (fileid == -1)
	{
		unlink(FIFO_NAME);
		exit(EXIT_FAILURE);
	}

	char buf[BUFSIZE];
	int cond   = 0;
	int nbytes = 0;

	while ((nbytes = read(fileid, buf, BUFSIZE)) != 0)
	{
		if (nbytes == -1)
		{
			perror("Couldn't read from file");
			unlink(FIFO_NAME);
			exit(EXIT_FAILURE);
		}
		cond = write(fifoid, buf, nbytes);
		if (cond == -1 || cond != nbytes)
		{
			perror("Couldn't read from file");
			unlink(FIFO_NAME);
			exit(EXIT_FAILURE);
		}
	}
	exit(EXIT_SUCCESS);
}

//=======================================================================================================================

int receiver()
{
	int fifoid = open_fifo(O_RDONLY);

	unlink(COPY_NAME);
	int fileid = open(COPY_NAME, O_WRONLY | O_CREAT, 0600);
	if (fileid == -1)
	{
		perror("Couldn't creat COPIED file");
		unlink(FIFO_NAME);
		exit(EXIT_FAILURE);
	}

	char buf[BUFSIZE];
	int nbytes = 0;
	int cond = 0;
	while ((nbytes = read(fifoid, buf, BUFSIZE)) != 0)
	{
		if (nbytes == -1)
		{
			perror("Couldn't read from FIFO");
			unlink(FIFO_NAME);
			unlink(COPY_NAME);
			exit(EXIT_FAILURE);
		}
		cond = write(fileid, buf, nbytes);

		if (cond != nbytes)
		{
			perror("Couldn't write to copy");
			unlink(FIFO_NAME);
			unlink(COPY_NAME);
			exit(EXIT_FAILURE);
		}
	}
	unlink(FIFO_NAME);
	close(fileid);
	exit(EXIT_SUCCESS);
}