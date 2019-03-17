#include <iostream>
#include <omp.h>
#include <stack>

int n(int n) {
  std::cout << std::endl;
  std::cout << "Часть " << n << std::endl;
}

int main() {

  n(1);
#ifdef _OPENMP
  std::cout << "OpenMP is supported!" << std::endl;
#endif

  n(2);
  std::cout << "Последовательная область начало" << std::endl;
#pragma omp parallel
  {
    std::cout << "Параллельная область" << std::endl;
  };
  std::cout << "Последовательная область конец" << std::endl;

  int count, num;
  std::stack<int> thread;
#pragma omp parallel
  {
    count = omp_get_num_threads();
#pragma omp critical
    {
      num = omp_get_thread_num();
      thread.push(num);
      std::cout << "Номер нити: " << num << std::endl;
    };
  };
  std::cout << "Всего нитей: " << count << std::endl;

  n(3);
  std::cout << "Обратный порядок номеров нитей" << std::endl;
  for (int i = thread.size(); i != 0; --i) {
    std::cout << thread.top() << std::endl;
    thread.pop();
  }

  n(4);
  omp_set_num_threads(2);
  std::cout << "Колличество потоков 3" << std::endl;
#pragma omp parallel num_threads(3)
  {
    std::cout <<  "Параллельная область 1" << std::endl;
  }
  std::cout << "Колличество потоков 2" << std::endl;
  #pragma omp parallel
  {
    std::cout <<  "Параллельная область 2" << std::endl;
  }

  return 0;
}