#include "ivmatrix.h"
#include "iv_standard.h"

int    get_matrix(int fd, matrix* this);
double get_matrix_determinant(matrix* this);
void   print_matrix(const matrix* this);

int main(int argc, char const *argv[]) {
	CHECK(argc == 2, "Invalid number of arguments. Need only name of a file\n");
	char* filename = argv[1];
	FILE* fd = fopen(filename, "r");
	CHECK(fd != NULL, "Failed to open matrix file");


	matrix current = {
		.size = 0,
		.data = NULL
	};
	int cond = get_matrix(fd, &current);
	CHECK(cond == -1, "Failed to read matrix from file\n");
	double determinant = get_matrix_determinant(&current);
	print_matrix(&current);
	printf("Determinant is %lg", determinant);
	return 0;
}

int get_matrix(FILE* fd, matrix* this) {
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
	return 0;
}

double get_matrix_determinant(const matrix* this)
{
	
}