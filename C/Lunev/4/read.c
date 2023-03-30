#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
  FILE *input = fopen("output.bin", "rb");

  double arr[4] = {};

  fread(arr, sizeof(double), 4, input);

  for (int i = 0; i < 4; ++i)
    printf("%lg ", arr[i]);

  getchar();
  return 0;
}