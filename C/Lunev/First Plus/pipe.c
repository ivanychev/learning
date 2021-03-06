#include "pipe.h"
#include "onefile.c"

/**
 * @brief 	Tough sending file via pipe
 * @mainpage
 * 
 * @author	Sergey Ivanychev, DCAM MIPT 376 group
 *
 * @version	v0.3
 * 
 * @par		Changelog v0.2
 * 		-- Added forced_fifo_open() function. Purifying code
 *
 *		Changelog v0.3
 *		-- Added new verification method 
 *		-- Some big and copy-paste function reimplemented
 */

//================================================================================================
//================================================================================================

#define PAGESIZE getpagesize()
#define BIGSIZE  PAGESIZE * 16

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


//================================================================================================
//================================================================================================

#undef  F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE			\
	close(send_flag);			\
	unlink(SENDER_FLAG);			\

int send(char const *filename)
{
	int send_flag = 0;
	int is_cur_sender = is_sender(&send_flag);
	if (is_cur_sender == 0)
	{
		OUT("Already working...\n");
		return 0;
	}
	CHECK(is_cur_sender != -1, "Failed to create SENDER flag in /tmp");


	int fifo_id = 0;
	int fifo_cond = forced_open_fifo(FIFO_NAME, 0600, O_WRONLY, &fifo_id);
	CHECK(fifo_cond != FOFC_OPEN_ERROR, "Failed to open FIFO for writing");

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
	if (send_flag)
		close(send_flag);

	int unlink_flag = unlink(SENDER_FLAG);

	return 0;
}


//================================================================================================
//================================================================================================


#undef  F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE			\
	close(receive_flag);			\
	unlink(RECEIVE_FLAG);			\
	

int receive()
{
	int receive_flag = 0;
	int is_cur_receiver = is_receiver(&receive_flag);


	if (is_cur_receiver == 0)
	{
		OUT("Already working...\n");
		return 0;
	}

	CHECK(is_cur_receiver != -1, "Failed to create RECEIVER in /tmp");

	int fifo_id = 0;
	int fifo_cond = forced_open_fifo(FIFO_NAME, 0600, O_RDONLY, &fifo_id);
	CHECK(fifo_cond != FOFC_OPEN_ERROR, "Failed to open FIFO for reading");

	int read_sz    = 0;
	int write_cond = 0;
	char buf[BUF_SIZE] = {};

	while ((read_sz = reading(fifo_id, buf, BUF_SIZE)) != 0)
	{
			write_cond = write(STDOUT_FILENO, buf, read_sz);
			CHECK(write_cond == read_sz, "Printed ammound isn't equal to")
	}

	close(fifo_id);

	
	int unlink_cond = unlink(FIFO_NAME);
	CHECK(unlink_cond != -1, "Failed to unlink fifo");

	
	close(receive_flag);
	int unlink_flag = unlink(RECEIVE_FLAG);

	
	return 0;
}

//================================================================================================
//================================================================================================

#undef  F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE


int is_receiver(int* flag_save)
{
	return is_it(flag_save, RECEIVE_FLAG);
}

int is_sender(int* flag_save)
{
	return is_it(flag_save, SENDER_FLAG);
}

int is_it(int* flag_save, const char* name)
{
	CHECK(flag_save != NULL, "Argumented pointer is NULL");
	char* FLAG_PAINT = (char*)calloc(PAGESIZE + 1, sizeof(char));


	int flag_fifo 	 = mkfifo (name, 0600);
	int flag_fifo_id = open   (name, O_RDWR|O_NONBLOCK);

	OUT1("ORIGIN:  Pipe size = %d\n", fcntl(flag_fifo_id, F_GETPIPE_SZ));
	CHECK(flag_fifo_id != -1, "Failed to open flag fifo");
	
	if (fcntl(flag_fifo_id, F_GETPIPE_SZ) != PAGESIZE)
	{
		OUT1("BEFORE: Pipe size = %d\n", fcntl(flag_fifo_id, F_GETPIPE_SZ));
		int check_ctl = fcntl(	flag_fifo_id,
					F_SETPIPE_SZ, 
					PAGESIZE);
		OUT1("AFTER:  Pipe size = %d\n", fcntl(flag_fifo_id, F_GETPIPE_SZ));
		CHECK(fcntl(flag_fifo_id, F_GETPIPE_SZ) == PAGESIZE, "Unsuccessfully tried to reduce pipe size to page size");
	}

	int is_flag_up = write(flag_fifo_id, FLAG_PAINT, PAGESIZE);
	LOC_OUT2("Written %d bytes to flag fifo [%d]\n", is_flag_up, flag_fifo_id);
	

	OUT1("FINALLY: Pipe size = %d\n", fcntl(flag_fifo_id, F_GETPIPE_SZ));

	*flag_save = flag_fifo_id;

	free(FLAG_PAINT);
	if (is_flag_up == -1)
		return 0;

	return 1;
}


//================================================================================================
//================================================================================================


#undef  F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE

int forced_open_fifo(const char* name, mode_t mode, int flags, int* to_save)
{
	CHECK(to_save != NULL, "Argumented pointer is NULL");
	int fifo_cond = mkfifo(name, mode);	
	if (fifo_cond == -1 && errno == EEXIST)
		OUT("FIFO file has been found...\n");

	int fifo_id = open(name, flags);
	if (fifo_id == -1)
		return FOFC_OPEN_ERROR;
	*to_save = fifo_id;
	return (fifo_cond == -1)? FOFC_FILE_EXIST: 
				  FOFC_FILE_CREATED;

}


//================================================================================================
//================================================================================================
