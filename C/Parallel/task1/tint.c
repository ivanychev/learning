/*
	Integral calculation via MPI

	Author: 	Sergey Ivanychev
	Group:		376
	Revision:	1
**/

#include <stdio.h>
#include <math.h>
#include <mpi.h>
#include <stdint.h>
#include <stdlib.h>

#define A 2.0

double f(double x)
{
	return sqrt(4.0 - x * x);
}

int32_t get_process_number() {
	int32_t world_size = 0;;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    return world_size;
}

int32_t get_rank() {
	int32_t rank = 0;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	return rank;
}

void print_answer(double sum, int32_t world) {
	int32_t i = 0;
	double buffer = 0;
	for (i = 1; i < world; ++i) {
		MPI_Recv(&buffer, 1, MPI_DOUBLE, i, MPI_ANY_TAG,
               MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		sum += buffer;
	}
	printf("%f", sum);
	return;
}

void send_answer(double sum) {
	MPI_Send(&sum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
	return;
}

int32_t main(int32_t argc, char *argv[])
{
	if (argc < 2) {
		printf("Usage: %s num_intervals.\n", argv[0]);
		return 1;
	}
	MPI_Init(&argc, &argv);
	int32_t rank = get_rank();
	int32_t world = get_process_number();
	int32_t i = 0;
	int32_t intervals = (int32_t)atoi(argv[1]);
	double h = A / intervals;
	double sum = 0.0;
	for (i = rank; i < intervals; i += world) {
		sum += h * (f(h * i) + f(h * (i + 1))) / 2.0;
	}
	if (rank == 0) {
		print_answer(sum, world);
	}
	else {
		send_answer(sum);
	}
	MPI_Finalize();
	return 0;
}
