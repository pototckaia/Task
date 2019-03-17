#include <cstdlib>
#include <vector>
#include <iostream>
#include <omp.h>
#include <chrono>
#include <iomanip>
#include "helper.h"


long dot_parallel(long N, int thread) {
  std::vector<long> A(N, 1), B(N, 1);
  long dot = 0;

#pragma omp parallel num_threads(thread)
#pragma omp for
  for (int i = 0; i < N; ++i) {
#pragma omp atomic
    dot += A[i] * B[i];
  }

  return dot;
}

int main(int argc, char* argv[]) {
  for (int i = 1; i < argc; ++i) {
    long N = std::atol(argv[i]);
    std::cout << "Dimension " << N << std::endl;
    printElement("Thread");
    printElement("Result");
    printElement("Duration (ms)");
    printNewLine();

    for (int j = 1;  j <= 8; ++j) {
      auto t1 = std::chrono::high_resolution_clock::now();
      long dot = dot_parallel(N, j);
      auto t2 = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

      printElement(j);
      printElement(dot);
      printElement(duration);
      printNewLine();
    }
  }

}