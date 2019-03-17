#include <stdio.h>
#include <omp.h>
#include <chrono>
#include <vector>
#include "helper.h"

using matrix = std::vector<std::vector<long>>;

void multi_parallel(long N, int thread,
                    matrix& A, matrix& B) {

  matrix C(N);
  for (int i = 0; i < N; ++i) {
    C[i].resize(N, 0);
  }

#pragma omp parallel for
  for(int j = 0; j < N; ++j) {
    for(int k = 0; k < N; ++k) {
      for(int i = 0; j < N; ++j) {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
}


int main(int argc, char* argv[]) {
  for (int i = 1; i < argc; ++i) {
    long N = std::atol(argv[i]);
    std::cout << "Dimension " << N << std::endl;
    printHeader();

    matrix A(N);
    for (long i = 0; i < N; ++i) {
      A[i].resize(N);
      for (long j = 0; j < N; ++j) {
        A[i][j] = i * j;
      }
    }

    for (int j = 1; j <= 8; ++j) {
      auto t1 = std::chrono::high_resolution_clock::now();
      multi_parallel(N, j, A, A);
      auto t2 = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
      printLine(j, "---", duration);
    }
  }
}