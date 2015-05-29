/**
 * @brief 	Parallel matrix determinant calculating
 * @details 	Testing results (300x300):
 * 		1  core -	49.55
 * 		2  cores - 	25.85
 * 		4  cores - 	13.29
 * 		8  cores - 	 7.42
 * 		16 cores - 	 4.29
 */


#include "../include/ivmatrix.h"
#include "../include/iv_standard.h"

//#define DEBUG

#undef  F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE return -1;


//======================================================================================


#undef  F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE return -1;

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



int get_matrix(const char* filename, matrix* this) 
{
	CHECKN(filename != NULL, IV_PTRNULL);
	CHECKN(this 	!= NULL, IV_PTRNULL);

	char* buf = NULL;
	size_t filesize = 0;
	int cond = iv_allocbuffer_copy(filename, &buf, &filesize);


	CHECK(cond == 0, "Failed to copy file to buffer");

	uint32_t size  = 0;
	uint32_t shift = 0;
	uint32_t arrow = 0;
    	uint32_t i = 0;

	cond = sscanf(buf, "%"SCNu32"%n", &size, &arrow);

	CHECK(cond == 1, "Failed to get matrix size number, that must first in matrix definition");
	CHECK((uint64_t)size * (uint64_t)size < (uint64_t)UINT32_MAX,
		"Too big size of matrix");
	this->data = calloc(size * size, sizeof(double));
	CHECKN(this->data, IV_ALLOCFAIL);

	uint32_t nelems = size * size;
	for (i = 0; i < nelems; ++i){
		double temp = 0;
		cond = sscanf(buf + arrow, "%lg%n", &temp, &shift);
		arrow += shift;
		CHECK(cond == 1, "Failed to read element");
		((double*)(this->data))[i] = temp;
	}
	this->size = size;
	free(buf);
	return 0;
}

//======================================================================================

#undef  F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE return NULL;

pthread_t* get_threads( const matrix* this, 
			long amount, 
			double* results, 
			struct thread_meta** info_save, 
			int semid)
{
	CHECK(amount > 0, "Invalid amount of expected threads");
	pthread_t* array = (pthread_t*)calloc(amount, sizeof(pthread_t));
	CHECKN(array, IV_ALLOCFAIL);

#undef  F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE free(array); return NULL;

	CHECKN(info_save, IV_PTRNULL);

	int cond = 0;

#undef  F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE /*semctl(*semid, 0, IPC_RMID);*/ free(array); return NULL;


	struct thread_meta* info= (struct thread_meta*)calloc(amount, 
							      sizeof(struct thread_meta));
	CHECKN(info, IV_ALLOCFAIL);

#undef F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE free(info); /*semctl(*semid, 0, IPC_RMID);*/ free(array); return NULL;

// experimenting with stack size
		// pthread_attr_t default_attr;
		// cond = pthread_attr_init(&default_attr);
		// CHECK(cond == 0, "Failed to set thread attribute");
		// cond = pthread_attr_setstacksize(&default_attr, MB);
		// CHECK(cond == 0, "Failed to set stack size of pthread");

// experimenting with CPU affinity
	cpu_set_t mask;
	cpu_set_t all_cores;
    	long i = 0;
	CPU_ZERO(&mask);
	cond = sched_getaffinity(0, sizeof(cpu_set_t), &all_cores);
	CHECK(cond == 0, "Failed to get CPU mask");	
	int cores = CPU_COUNT(&all_cores);
	int cur_core = 0;
	for (i = 0; i < amount; ++i)
	{
		info[i].ptr   	 	= this;
		info[i].minor_index 	= i;
		info[i].threads_num 	= amount;
		info[i].to_save 	= results + i;
		info[i].semid 		= semid;

		cur_core = i % cores;
		CHECK(CPU_ISSET(cur_core, &all_cores), "Core is not in the set");
		CPU_ZERO(&mask);
		CPU_SET(cur_core, &mask);

		cond = pthread_create(&(array[i]), NULL/*&default_attr*/, thread_routine, (void*)(info + i));
		CHECK(cond == 0, "Failed to create thread");
		cond = pthread_setaffinity_np(array[i], sizeof(mask), &mask);
		CHECK(cond == 0, "Failed to set affinity");
	}
	*info_save = info;
	return array;
}

#undef  F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE return -1;

//============================================================================================

int get_matrix_determinant(const matrix* this, long nthreads, double* ret)
{
	long i = 0;
    	CHECKN(this != NULL, IV_PTRNULL);
	CHECK(this->data != NULL, "Invalid matrix: no data");
//	int semid = 0;
	double* results = (double*)calloc(nthreads, sizeof(double));
	CHECKN(results, IV_ALLOCFAIL);
#undef  F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE free(results); return -1;

	int fileid = creat(TEMP_FILE, 0600);
	CHECK(fileid != -1, "Failed to create temporary file");
	int key = ftok(TEMP_FILE, 1);
	CHECK(key != -1, "Failed to get flag key");
	int semid = semget(key, 1, IPC_CREAT | 0660);
 	CHECK(semid != -1, "Failed to get flag semaphore id");

 	union semun set;
 	set.val = 0;
 	semctl(semid, 0, SETVAL, set);

 	struct sembuf act = {0, (short)nthreads ,0};
 	int cond = semop(semid, &act, 1);

#undef  F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE semctl(semid, 0, IPC_RMID); free(results); return -1;

 	CHECK(cond == 0, "Failed to set semaphore");

	struct thread_meta* info = NULL;
	pthread_t* threads = get_threads(this, nthreads, results, &info, semid);
	CHECK(threads != NULL, "Failed to create threads");

#undef  F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE semctl(semid, 0, IPC_RMID);   \
			  free(results); 		\
			  free(info); 			\
			  return -1;

	struct sembuf wait = {0, 0, 0};
	cond = semop(semid, &wait, 1);
	CHECK(cond == 0, "Failed to wait for threads");

	double result = 0.0;
	for (i = 0; i < nthreads; i++)
	{
		result += results[i];
	}

	free(results);
	free(threads);
	free(info);
	semctl(semid, 0, IPC_RMID);
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
	// struct timeval begin;
	// struct timeval end;

//	gettimeofday(&begin, NULL);

	assert(info_ptr);
	struct thread_meta info = *((struct thread_meta*)info_ptr);

	uint32_t size   	= info.ptr->size;
	uint32_t factor 	= info.threads_num;
	double result 		= 0;
	double temp_result 	= 0;
	matrix* minor 		= NULL;
	matrix copy 		= matrix_copy(info.ptr);
	int semid 		= info.semid;
	uint32_t i 		= 0;
#undef  F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE matrix_kill(&copy); return (void*)-1;
	int cond = 0;
	for (i = info.minor_index; i < size; i += factor)
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
//	gettimeofday(&end, NULL);

//	char thread_name[50];
//	sprintf(thread_name, "%"PRIu32"'th thread time: ", info.minor_index);
//	print_diff(begin, end, thread_name);

	struct sembuf on_exit= {0, -1, 0};
	semop(semid, &on_exit, 1);
//	printf("Finished\n");	
	pthread_exit(NULL);
}

#undef  F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE return -1;

//============================================================================================


int gauss(matrix* this, double* result)
{
	uint32_t i = 0;
	CHECKN(this != NULL, IV_ALLOCFAIL);
	CHECK(this->data != NULL, "Invalid Matrix: no data");

	for (i = 0; i < this->size; ++i)
	{
		if (IS_ZERO(ELEM(this, i, i)))
			search_below_nzero_swap(this, i);
		if (IS_ZERO(ELEM(this, i, i)))
			continue;
		annihilate_below(this, i);
	}

	double output = 1.0;
	for (i = 0; i < this->size; ++i)
		output *= ELEM(this, i, i);
	*result = output;
	return 0;	
}

//======================================================================================

void search_below_nzero_swap(matrix* this, uint32_t index)
{
	uint32_t j = index + 1;
	long i = 0;
	for (; j < this->size; ++j)
		if (!IS_ZERO(ELEM(this, j, index)))
			break;
	if (IS_ZERO(ELEM(this, j, index)))
		return;
	swap_strings(this, j, index);
	for (i = 0; i < this->size; ++i)
		ELEM(this, j, i) *= -1.0;
}

//======================================================================================

inline void swap_strings(matrix* this, uint32_t first, uint32_t second)
{
	uint32_t i = 0;
	for (i = 0; i < this->size; ++i)
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
	uint32_t j = 0;
	for (j = i + 1; j < this->size; ++j)
		add_string(this, i, j, (-1.0)*ELEM(this, j, i)/ELEM(this, i, i));
}

//============================================================================================

inline void add_string(matrix* this, uint32_t added, uint32_t to, double factor)
{
	uint32_t i = 0;
	for (i = 0; i < this->size; ++i)
		ELEM(this, to, i) += ELEM(this, added, i) * factor;
}

#undef  F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE return NULL;

matrix* get_minor(const matrix* this, uint32_t string, uint32_t column)
{
	CHECKN(this != NULL, IV_PTRNULL);
	uint32_t old_amount = this->size * this->size;

	void* new_data = calloc((this->size - 1) * (this->size - 1), sizeof(double));
	CHECKN(new_data != NULL, IV_ALLOCFAIL);
	
	void* old_data = this->data;

#undef  F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE free(new_data); return NULL;

	uint32_t j = 0, i = 0;
	for (i = 0; i < old_amount; ++i)
	{
		if (i % this->size == column || i / this->size == string)
			continue;
		((double*)new_data)[j] = ((double*)old_data)[i];
		j++;
	}

	CHECK(j == (this->size - 1) * (this->size - 1), "Failed to copy numbers to minor");
	matrix* new_matrix = (matrix*)calloc(1, sizeof(matrix));
	CHECKN(new_matrix, IV_ALLOCFAIL);

	new_matrix->size = this->size - 1;
	new_matrix->data = new_data;
	
	return new_matrix;
}

#undef F_CHECK_EXIT_CODE
//============================================================================================

void   print_matrix(const matrix* this)
{
	uint32_t i = 0, j = 0;
	printf("Size = %"PRIu32"\n", this->size);
	for (i = 0; i < this->size; ++i) {
		for (j = 0; j < this->size; ++j)
			printf("%4lg", ELEM(this, i, j));	// sorry for 4 tabs
		putchar('\n');

	}
}

//============================================================================================
