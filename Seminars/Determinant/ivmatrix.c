/**
 * @brief 	Parallel matrix determinant calculating
 * @details 	Testing results (300x300):
 * 		1  core -	49.55
 * 		2  cores - 	25.85
 * 		4  cores - 	13.29
 * 		8  cores - 	 7.42
 * 		16 cores - 	 4.29
 */


//#define DEBUG
#define PAGESIZE (4096)
#define MB (1024*1024)
#define MAX_FILENAME 100

#include "ivmatrix.h"
#include "iv_standard.h"

#undef  F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE return -1;
#define TEMP_FILE ".temp"

uint64_t GLOBAL_COUNTER = 0;

void print_diff(struct timeval begin, struct timeval end);

//======================================================================================

int proceed_arguments(int argc, char const* argv[], char* name, long* nthreads)
{
	CHECK(argc == 3, "Invalid number of arguments. Need name of a file AND number of threads\n");
	
	const char* filename    = argv[1];

	*nthreads = 0;
	int cond = get_long(nthreads, argv[2]);

	CHECK(cond == 0, "Failed to get number from second argument");
	CHECK(*nthreads > 0, "Invalid number of expecting threads to be created");

	int filelen = strlen(argv[1]);
	CHECK(filelen <= MAX_FILENAME, "Too long filename");
	strcpy(name, argv[1]);
	return 0;
}

//======================================================================================


int main(int argc, char const *argv[]) 
{
	struct timeval begin;
	struct timeval end;


	char* filename[MAX_FILENAME + 1] = {};
	long nthreads = 0;
	int cond = proceed_arguments(argc, argv, filename, &nthreads);

#undef  F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE fclose(fd); return -1;

	CHECK(cond == 0, "Failed to get arguments");
	matrix current = {
		.size = 0,
		.data = NULL
	};
	cond = get_matrix(filename, &current);

	gettimeofday(&begin, NULL);

#undef  F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE fclose(fd); matrix_kill(&current); return -1;

	CHECK(cond != -1, "Failed to read matrix from file\n");
	double determinant = 0;
	cond = get_matrix_determinant(&current, nthreads, &determinant);
	CHECK(cond == 0, "Failed to calculate matrix determinant");
	printf("Determinant is %lg\n", determinant);

	fclose(fd);
	matrix_kill(&current);
	gettimeofday(&end, NULL);

	print_diff(begin, end);
	return 0;
}

#undef  F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE return -1;


int get_long(long* save, const char* str)
{
	assert(save);
	int base = 10;
	char* endptr = NULL;

	long val = strtol(str, &endptr, base);


	if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
	       || (errno != 0 && val == 0)
	       || (void*)endptr == (void*)str) {
	   	return -1;
	}



	*save = val;
	return 0; 
}


//======================================================================================

void matrix_kill(matrix* this)
{
	if (this == NULL)
		return;
	if (this->data)
	{
		free(this->data);
		this->data = NULL;
	}
	this->size = 0;
}

//======================================================================================

int readfile(const char* filename, char** buf)
{
	assert(filename);
	assert(buf);

	
}

int get_matrix(const char* filename, matrix* this) 
{
	CHECKN(filename != NULL, IVPTRNULL);
	CHECKN(this 	!= NULL, IVPTRNULL);

	char* buf = NULL;
	int cond = readfile(filename, &buf)

	uint32_t size = 0;
	cond = fscanf(fd, "%"SCNu32, &size);
	CHECK(cond == 1, "Failed to get matrix size number, that must first in matrix definition");
	CHECK((uint64_t)size * (uint64_t)size < (uint64_t)UINT32_MAX,
		"Too big size of matrix");
	this->data = calloc(size * size, sizeof(double));
	CHECKN(this->data, IVALLOCFAIL);

	uint32_t nelems = size * size;
	for (uint32_t i = 0; i < nelems; ++i){
		double temp = 0;
		cond = fscanf(fd, "%lg", &temp);
		CHECK(cond == 1, "Failed to read element");
		((double*)(this->data))[i] = temp;
	}
	this->size = size;
	return 0;
}

//======================================================================================

#undef  F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE return NULL;

pthread_t* get_threads(const matrix* this, long amount, double* results, struct thread_meta** info_save)
{
	CHECK(amount > 0, "Invalid amount of expected threads");
	pthread_t* array = (pthread_t*)calloc(amount, sizeof(pthread_t));
	CHECKN(array, IVALLOCFAIL);
	CHECKN(info_save, IVPTRNULL);

#undef  F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE free(array); return NULL;

	int cond = 0;

#undef  F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE /*semctl(*semid, 0, IPC_RMID);*/ free(array); return NULL;


	struct thread_meta* info= (struct thread_meta*)calloc(amount, 
							      sizeof(struct thread_meta));
	CHECKN(info, IVALLOCFAIL);

#undef F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE free(info); /*semctl(*semid, 0, IPC_RMID);*/ free(array); return NULL;

// experimenting with stack size
		pthread_attr_t default_attr;
		cond = pthread_attr_init(&default_attr);
		CHECK(cond == 0, "Failed to set thread attribute");
		cond = pthread_attr_setstacksize(&default_attr, MB);
		CHECK(cond == 0, "Failed to set stack size of pthread");

	for (long i = 0; i < amount; ++i)
	{
		info[i].ptr   	 	= this;
		info[i].minor_index 	= i;
		info[i].threads_num 	= amount;
		info[i].to_save 	= results + i;

		cond = pthread_create(&(array[i]), &default_attr, thread_routine_debug, (void*)(info + i));
		CHECK(cond == 0, "Failed to create thread");
	}
	*info_save = info;
	return array;
}

#undef  F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE return -1;

//============================================================================================

int get_matrix_determinant(const matrix* this, long nthreads, double* ret)
{
	CHECKN(this != NULL, IVPTRNULL);
	CHECK(this->data != NULL, "Invalid Matrix: no data");
//	int semid = 0;
	double* results = (double*)calloc(nthreads, sizeof(double));
	CHECKN(results, IVALLOCFAIL);


#undef  F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE free(results); return -1;

	struct thread_meta* info = NULL;
	pthread_t* threads = get_threads(this, nthreads, results, &info);
	CHECK(threads != NULL, "Failed to create threads");

#undef  F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE free(results); free(info); return -1;

	for (long i = 0; i < nthreads; i++) {
		pthread_join(threads[i], NULL);
		fprintf(stderr, "caught\n");
	}
	double result = 0.0;
	for (long i = 0; i < nthreads; i++)
	{
		result += results[i];
	}

	free(results);
	free(threads);
	free(info);
	*ret = result;
	return 0;

}

#undef  F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE return (void*)-1;

//============================================================================================

matrix matrix_copy(const matrix* copied)
{
	matrix copy;
	copy.size = copied -> size;
	copy.data = (double*)calloc(copy.size * copy.size, sizeof(double));
	memmove(copy.data, copied->data, copy.size * copy.size * sizeof(double));
	return copy;
}

//============================================================================================

void* thread_routine_debug(void* info_ptr)
{
	uint32_t size   = ((struct thread_meta*)info_ptr)->ptr->size;
	uint32_t factor = ((struct thread_meta*)info_ptr)->threads_num;

	uint64_t big_number = 1;
	for (; size > 0; --size)
		big_number *= 10;

	for (; big_number > 0; big_number -= factor);

	pthread_exit(NULL);
}

void* thread_routine(void* info_ptr)
{
	assert(info_ptr);
	struct thread_meta info = *((struct thread_meta*)info_ptr);

	uint32_t size   	= info.ptr->size;
	uint32_t factor 	= info.threads_num;
	double result 		= 0;
	double temp_result 	= 0;
	matrix* minor 		= NULL;
	matrix copy 		= matrix_copy(info.ptr);

#undef  F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE matrix_kill(&copy); return (void*)-1;
	int cond = 0;
	for (uint32_t i = info.minor_index; i < size; i += factor)
	{
		minor = get_minor(&copy, 0, i);
		CHECK(minor != NULL, "Failed to get minor");

#undef  F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE matrix_kill(minor); matrix_kill(&copy); return (void*)-1;

		cond = gauss(minor, &temp_result);
		CHECK(cond == 0, "Failed to convert matrix");
		double delta_result = ELEM(&copy, 0, i)*temp_result * ((i % 2 == 0)? 1.0 : -1.0);
		result += delta_result;
		matrix_kill(minor);
		free(minor);
	}
	*(info.to_save) = result;
	matrix_kill(&copy);

	pthread_exit(NULL);
}

#undef  F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE return -1;

//============================================================================================


int gauss(matrix* this, double* result)
{
	CHECKN(this != NULL, IVALLOCFAIL);
	CHECK(this->data != NULL, "Invalid Matrix: no data");

	for (uint32_t i = 0; i < this->size; ++i)
	{
		if (IS_ZERO(ELEM(this, i, i)))
			search_below_nzero_swap(this, i);
		if (IS_ZERO(ELEM(this, i, i)))
			continue;
		annihilate_below(this, i);
	}

	double output = 1.0;
	for (uint32_t i = 0; i < this->size; ++i)
		output *= ELEM(this, i, i);
	*result = output;
	return 0;	
}

//======================================================================================

void search_below_nzero_swap(matrix* this, uint32_t i)
{
	uint32_t j = i + 1;
	for (; j < this->size; ++j)
		if (!IS_ZERO(ELEM(this, j, i)))
			break;
	if (IS_ZERO(ELEM(this, j, i)))
		return;
	swap_strings(this, j, i);
	for (long i = 0; i < this->size; ++i)
		ELEM(this, j, i) *= -1.0;
}

//======================================================================================

inline void swap_strings(matrix* this, uint32_t first, uint32_t second)
{
	for (uint32_t i = 0; i < this->size; ++i)
	{
		double temp = ELEM(this, first, i);
		ELEM(this, first, i) = ELEM(this, second, i);
		ELEM(this, second, i) = temp;
	}
}

/**
 * @brief Annihilates numbers below [i, i] to zero (current is 1)
 * @details 	1  2  3			1  2  3
 * 		0 [3] 7 	-> 	0 [3] 7
 * 		0  4  5 		0  0 (5 - 4*7/3)
 * 
 * @param this current matrix
 * @param i position (1 in description)
 */
inline void annihilate_below(matrix* this, uint32_t i)
{
	for (uint32_t j = i + 1; j < this->size; ++j)
		add_string(this, i, j, (-1.0)*ELEM(this, j, i)/ELEM(this, i, i));
}

//============================================================================================

inline void add_string(matrix* this, uint32_t added, uint32_t to, double factor)
{
	for (uint32_t i = 0; i < this->size; ++i)
		ELEM(this, to, i) += ELEM(this, added, i) * factor;
}

#undef  F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE return NULL;

matrix* get_minor(const matrix* this, uint32_t string, uint32_t column)
{
	CHECKN(this != NULL, IVPTRNULL);
	uint32_t old_amount = this->size * this->size;

	void* new_data = calloc((this->size - 1) * (this->size - 1), sizeof(double));
	CHECKN(new_data != NULL, IVALLOCFAIL);
	
	void* old_data = this->data;

#undef  F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE free(new_data); return NULL;

	uint32_t j = 0;
	for (uint32_t i = 0; i < old_amount; ++i)
	{
		if (i % this->size == column || i / this->size == string)
			continue;
		((double*)new_data)[j] = ((double*)old_data)[i];
		j++;
	}

	CHECK(j == (this->size - 1) * (this->size - 1), "Failed to copy numbers to minor");
	matrix* new_matrix = (matrix*)calloc(1, sizeof(matrix));
	CHECKN(new_matrix, IVALLOCFAIL);

	new_matrix->size = this->size - 1;
	new_matrix->data = new_data;
	
	return new_matrix;
}

#undef F_CHECK_EXIT_CODE
//============================================================================================

void   print_matrix(const matrix* this)
{
	printf("Size = %"PRIu32"\n", this->size);
	for (uint32_t i = 0; i < this->size; ++i) {
		for (uint32_t j = 0; j < this->size; ++j)
			printf("%4lg", ELEM(this, i, j));	// sorry for 4 tabs
		putchar('\n');

	}
}

//============================================================================================

void print_diff(struct timeval begin, struct timeval end)
{
	long long seconds = (long long)end.tv_sec  - (long long)begin.tv_sec;
	long long micros  = (long long)end.tv_usec - (long long)begin.tv_usec;
	if (micros < 0)
	{
		micros += 1000000;
		seconds -= 1;
	}
	printf("%lld.%6lld\n", seconds, micros);
}