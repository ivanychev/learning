#define DEBUG

#include "ivmatrix.h"
#include "iv_standard.h"

int    	get_matrix(FILE* fd, matrix* this);
double 	get_matrix_determinant(const matrix* this);
void   	print_matrix(const matrix* this);
void  	search_below_nzero_swap(matrix* this, uint32_t i);
void  	annihilate_below 	    (matrix* this, uint32_t i);
void  	swap_strings 	    (matrix* this, uint32_t first, uint32_t second);
void  	add_string 	    (matrix* this, uint32_t added, uint32_t to, double factor);
void  	gauss		    (matrix* this);
void 	matrix_kill 	    (matrix* this);

#undef  F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE return -1;


//======================================================================================

int main(int argc, char const *argv[]) 
{
	printf("%d\n", argc);

	CHECK(argc == 2, "Invalid number of arguments. Need only name of a file\n");

	const char* filename = argv[1];
	FILE* fd = fopen(filename, "r");
	CHECK(fd != NULL, "Failed to open matrix file");


	matrix current = {
		.size = 0,
		.data = NULL
	};
	int cond = get_matrix(fd, &current);

#undef  F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE matrix_kill(&current); return -1;

	CHECK(cond != -1, "Failed to read matrix from file\n");

	print_matrix(&current);
	double determinant = get_matrix_determinant(&current);
	printf("Determinant is %lg\n", determinant);
	return 0;
}

#undef  F_CHECK_EXIT_CODE
#define F_CHECK_EXIT_CODE return -1;


//======================================================================================

void matrix_kill(matrix* this)
{
	if (this->data)
	{
		free(this->data);
		this->data = NULL;
	}
	this->size = 0;
}

int get_matrix(FILE* fd, matrix* this) 
{
	CHECKN(fd   != NULL, IVPTRNULL);
	CHECKN(this != NULL, IVPTRNULL);

	uint32_t size = 0;
	int cond = fscanf(fd, "%"SCNu32, &size);
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

double get_matrix_determinant(const matrix* this)
{
	CHECKN(this != NULL, IVALLOCFAIL);
	CHECK(this->data != NULL, "Invalid Matrix: no data");

	matrix this_copy = *this;
	gauss(&this_copy);
	double result = 1.0;
	for (uint32_t i = 0; i < this_copy.size; ++i)
		result *= ELEM(&this_copy, i, i);
	return result;	
}


void gauss(matrix* this)
{
	for (uint32_t i = 0; i < this->size; ++i)
	{
		if (IS_ZERO(ELEM(this, i, i)))
			search_below_nzero_swap(this, i);
		if (IS_ZERO(ELEM(this, i, i)))
			continue;
		annihilate_below(this, i);
	}
}

void search_below_nzero_swap(matrix* this, uint32_t i)
{
	uint32_t j = i + 1;
	for (; j < this->size; ++j)
		if (!IS_ZERO(ELEM(this, j, i)))
			break;
	if (IS_ZERO(ELEM(this, j, i)))
		return;
	swap_strings(this, j, i);
}

//echo "Installing GetDeb" && sudo dpkg -i getdeb-repository_0.1-1~getdeb1_all.deb
//echo "Installing PlayDeb" &&sudo dpkg -i playdeb_0.3-1~getdeb1_all.deb &&
/*
echo "Deleting Downloads" && rm -f getdeb-repository_0.1-1~getdeb1_all.deb && rm -f playdeb_0.3-1~getdeb1_all.deb
*/

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

	void* new_data = calloc(old_amount, sizeof(double));
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

void   print_matrix(const matrix* this)
{
	printf("Size = %"PRIu32"\n", this->size);
	for (uint32_t i = 0; i < this->size; ++i) {
		for (uint32_t j = 0; j < this->size; ++j)
			printf("%4lg", ELEM(this, i, j));	// sorry for 4 tabs
		putchar('\n');

	}
}