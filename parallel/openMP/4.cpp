#include <cstdlib>
#include <vector>
#include <iostream>
#include <omp.h>
#include <chrono>
#include <iomanip>
#include "helper.h"
#include <climits>

long max_parallel(long N, int thread) {
  std::vector<long> A(N, 1);
  A[1] = N;
  long max_val = 0;

#pragma omp parallel for num_threads(thread) reduction(max:max_val)
    for (int i = 0; i < N; ++i) {
      max_val = std::max(A[i], max_val);
    }

  return max_val;
}

int main(int argc, char* argv[]) {
  for (int i = 1; i < argc; ++i) {
    long N = std::atol(argv[i]);
    std::cout << "Dimension " << N << std::endl;
    printHeader();

    for (int j = 1;  j <= 8; ++j) {
      auto t1 = std::chrono::high_resolution_clock::now();
      long max = max_parallel(N, j);
      auto t2 = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
      printLine(j, max, duration);
    }
  }

}