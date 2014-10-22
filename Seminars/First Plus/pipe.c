#include "pipe.h"


int main(int argc, char const *argv[])
{
	assert(argv);
	
	switch(argc)
	{
	case 1: 
		receive();
		break;
	case 2: 
		send(argv[1]);
		break;
	default:
		printf("Invalid number of arguments");
		exit(EXIT_FAILURE);
		break;
	}
	
	return 0;
}

int send(char const *filename)
{
	int is_sender = open(SEND_NAME, O_CREAT|O_EXCL, O_RDONLY);
	if (is_sender == -1 && errno == EEXIST)
	{
		printf("Sender is already working...");
		return 0;
	}
	CHECK(is_sender != -1, "Failed to create SENDER flag in /tmp");

	int fifo_cond = mkfifo(FIFO_NAME, 0600);

	if (fifo_cond == -1 && errno == EEXIST)
		OUT("[SENDER] FIFO file has been found...\n");

	int fifo_id = open(FIFO_NAME, O_WRONLY);
	CHECK(fifo_id != -1, "Failed to open fifo for writing");

	int file_id = open(filename, O_RDONLY);
	CHECK(file_id != -1, "Failed to open argumented file for reading");

	int  read_sz    = 0;
	int  write_cond = 0;
	char buf[BUF_SIZE] = {};

	while ((read_sz = read(file_id, buf, BUF_SIZE)) != 0)
	{
		write_cond = write(fifo_id, buf, read_sz);
		CHECK(write_cond == read_sz, "Written ammound isn't equal to")
	}

	close(fifo_id);

	return 0;
}


int receive()
{
	int is_receiver = open(RECEIVE_NAME, O_CREAT|O_EXCL, O_RDONLY);
	if (is_receiver == -1 && errno == EEXIST)
	{
		printf("Receiver is already working...");
		return 0;
	}
	CHECK(is_receiver != -1, "Failed to create RECEIVER in /tmp");

	int fifo_cond = mkfifo(FIFO_NAME, 0600);

	if (fifo_cond == -1 && errno == EEXIST)
		OUT("[SENDER] FIFO file has been found...\n");

	int fifo_id = open(FIFO_NAME, O_RDONLY);
	CHECK(fifo_id != -1, "Failed to open fifo for writing");

	int read_sz    = 0;
	int write_cond = 0;
	char buf[BUF_SIZE] = {};

	while ((read_sz = read(fifo_id, buf, BUF_SIZE)) != 0)
	{
			write_cond = write(STDOUT_FILENO, buf, read_sz);
			CHECK(write_cond == read_sz, "Printed ammound isn't equal to")
	}

	close(fifo_id);

	
	int unlink_cond = unlink(FIFO_NAME);
	CHECK(unlink_cond != -1, "Failed to unlink fifo");
	unlink_cond 	= unlink(RECEIVE_NAME);
	CHECK(unlink_cond != -1, "Failed to unlink RECEIVE flag");
	unlink_cond	= unlink(SEND_NAME);
	CHECK(unlink_cond != -1, "Failed to unlink SEND flag");
	
	return 0;
}