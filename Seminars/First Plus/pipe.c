#include "pipe.h"

/**
 * @brief 	Sending file via pipe
 * @mainpage
 * 
 * @author	Sergey Ivanychev, DCAM MIPT 376 group
 *
 * @version	v0.2
 * 
 * @par		Changelog v0.2
 * 		-- Added forced_fifo_open() function. Purifying code
 */


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
	
	int is_cur_sender = is_sender();
	if (is_cur_sender == 0)
		return 0;
	CHECK(is_cur_sender != -1, "Failed to create SENDER flag in /tmp");


	int fifo_id = 0;
	int fifo_cond = forced_open_fifo(FIFO_NAME, 0600, O_WRONLY, &fifo_id);
	CHECK(fifo_cond != FOFC_OPEN_ERROR, "Failed to open FIFO for writing");

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
	int is_cur_receiver = is_receiver();
	if (is_cur_receiver == 0)
		return 0;

	CHECK(is_cur_receiver != -1, "Failed to create RECEIVER in /tmp");

	int fifo_id = 0;
	int fifo_cond = forced_open_fifo(FIFO_NAME, 0600, O_RDONLY, &fifo_id);
	CHECK(fifo_cond != FOFC_OPEN_ERROR, "Failed to open FIFO for reading");

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


int is_sender()
{
	int is_sender = open(SEND_NAME, O_CREAT|O_EXCL, O_RDONLY);
	if (is_sender == -1 && errno == EEXIST)
		return 0;
	return (is_sender == -1)? -1: 1;
}

int is_receiver()
{
	int is_receiver = open(RECEIVE_NAME, O_CREAT|O_EXCL, O_RDONLY);
	if (is_receiver == -1 && errno == EEXIST)
		return 0;
	return (is_receiver == -1)? -1: 1;
}

int forced_open_fifo(const char* name, mode_t mode, int flags, int* to_save)
{
	CHECK(to_save != NULL, "Argumented pointer is NULL");
	int fifo_cond = mkfifo(name, mode);	
	if (fifo_cond == -1 && errno == EEXIST)
		OUT("FIFO file has been found...");

	int fifo_id = open(FIFO_NAME, flags);
	if (fifo_id == -1)
		return FOFC_OPEN_ERROR;
	*to_save = fifo_id;
	return (fifo_cond == -1)? FOFC_FILE_EXIST: FOFC_FILE_CREATED;

}

