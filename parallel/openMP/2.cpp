

#include <iostream>
#include <omp.h>
#include <vector>

//Суммирование элементов массива

int main() {
  std::vector A(1000, 1);
  int error_sum = 0, sum = 0;
#pragma omp parallel reduction(+: sum)
  {
#pragma omp for
    for (int i = 0; i < A.size(); ++i) {
      error_sum += A[i];
      sum += A[i];
    }
  }
  std::cout << "Сумма не правильная: " << error_sum << std::endl;
  std::cout << "Правильная сумма: " << sum << std::endl;

  sum = 0;
#pragma omp parallel
  {
#pragma omp for
      for (int i = 0; i < A.size(); ++i) {
#pragma omp atomic
        sum += A[i];
      }
  };
  std::cout << "Сумма atomic: " << sum << std::endl;

  sum = 0;
#pragma omp parallel
  {
#pragma omp for
    for(int i = 0; i < A.size(); ++i) {
#pragma omp critical
      {
        sum += A[i];
    };
    }
  };

  std::cout << "Сумма critical: " << sum << std::endl;
}