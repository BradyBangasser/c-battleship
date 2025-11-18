#include <omp.h>
#include <stdio.h>

int main() {
  int x[32] = {};

  for (int i = 0; i < sizeof(x) / sizeof(*x); i++) {
    x[i] *= 2;
  }

  printf("CPU\n");
#pragma omp target map(tofrom : x)
  for (int i = 0; i < sizeof(x) / sizeof(*x); i++) {
    x[i] *= 2;
  }
}
