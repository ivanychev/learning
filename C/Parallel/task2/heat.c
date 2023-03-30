#include <stdio.h>
#include <stdlib.h>

#define L 1.0
#define C 1.0
#define T1 1.0
#define T2 2.0

int main(int argc, char **argv) {
  if (argc < 3) {
    printf("Usage: %s N T\n", argv[0]);
    return 1;
  }
  int N = atoi(argv[1]);
  double T = atof(argv[2]);
  double *u[2];
  double h = L / (N - 1);
  double dt = 0.3 * h * h / C;
  int steps = T / dt;
  int i, j, un = 1;

  /* Выделение памяти. */
  u[0] = (double *)calloc(N, sizeof(double));
  u[1] = (double *)calloc(N, sizeof(double));

  /* Граничные условия. */
  u[0][0] = u[1][0] = T1;
  u[0][N - 1] = u[1][N - 1] = T2;

  /* Цикл интегрирования. */
  for (i = 0; i < steps; i++) {
    for (j = 1; j < N - 1; j++) {
      u[!un][j] =
          u[un][j] + 0.3 * (u[un][j - 1] - 2.0 * u[un][j] + u[un][j + 1]);
    }
    un = !un;
  }

  /* Вывод на экран. */
  for (i = 0; i < N; i++) {
    printf("%f %f\n", h * i, u[un][i]);
  }
  free(u[0]);
  free(u[1]);
  return 0;
}
