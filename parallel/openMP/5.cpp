#include <stdio.h>
#include <omp.h>
#include <chrono>
#include <vector>
#include "helper.h"

typedef std::vector<std::vector<long>> matrix;

matrix createMatrix(long N) {
  matrix C(N);
  for (int i = 0; i < N; ++i) {
    C[i].resize(N, 0);
  }
  return C;
}

std::string checkMulti(matrix& A, matrix& B, matrix& C) {
  bool right = true;
  int N = B.size();

  for(int j = 0; j < N; ++j) {
    for(int i = 0; i < N; ++i) {
      if (i == j) {
        right &= C[i][i] == i * i;
      } else {
        right &= C[i][j] == 0;
      }
    }
  }

  return right ? "+++" : "---";

}

matrix multi_parallel(long N, int thread,
                    matrix& A, matrix& B) {
  auto C = createMatrix(N);

  auto t1 = std::chrono::high_resolution_clock::now();
#pragma omp parallel for num_threads(thread)
  for(int i = 0; i < N; ++i) {
    for(int j = 0; j < N; ++j) {
      for(int k = 0; k < N; ++k) {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
  auto t2 = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
  printLine(thread, "ijk", checkMulti(A, B, C) , duration);

  C = createMatrix(N);
  t1 = std::chrono::high_resolution_clock::now();
#pragma omp parallel for num_threads(thread)
  for(int j = 0; j < N; ++j) {
    for(int k = 0; k < N; ++k) {
      for(int i = 0; i < N; ++i) {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
  t2 = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
  printLine(thread, "jki", checkMulti(A, B, C) , duration);


  C = createMatrix(N);
  t1 = std::chrono::high_resolution_clock::now();
#pragma omp parallel for num_threads(thread)
  for(int k = 0; k < N; ++k) {
    for(int i = 0; i < N; ++i) {
      for(int j = 0; j < N; ++j) {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
  t2 = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
  printLine(thread, "kij", checkMulti(A, B, C) , duration);

  return C;
}


int main(int argc, char* argv[]) {
  for (int i = 1; i < argc; ++i) {
    long N = std::atol(argv[i]);
    std::cout << "Dimension " << N << std::endl;
    printHeader5();

    matrix A(N);
    for (long i = 0; i < N; ++i) {
      A[i].resize(N, 0);
      A[i][i] = i;
    }

    for (int j = 1; j <= 8; ++j) {
      multi_parallel(N, j, A, A);
      printNewLine();
    }
  }
}