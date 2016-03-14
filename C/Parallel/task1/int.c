#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define A 2.0

double f(double x)
{
	return sqrt(4.0 - x * x);
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Usage: %s num_intervals.\n", argv[0]);
		return 1;
	}
	int i;
	int N = atoi(argv[1]);
	double h = A / N;
	double S = 0.0;
	for (i = 0; i < N; i++) {
		S += h * (f(h * i) + f(h * (i + 1))) / 2.0;
	}
	printf("%f\n", S);
	return 0;
}
