// MPI. Коллективные взаимодействия процессов. Барьер.
// Пример работы MPI_Barrier().
// Выяснить какой процесс быстрее выполнит перемножение двух квадратных матриц размером 500x500.

#include <iostream>
#include <chrono>
#include <vector>
#include "mpi.h"


int main(int argc, char **argv) {
	MPI_Init(&argc, &argv);
	MPI_Status status;
	
	int size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int n = 500, m = 500;
	std::vector<double> A(n*m, 0), B(n*m, 0), C(n*m, 0);
	for (int i = 0; i < A.size(); ++i) {
		A[i] = B[i] = i;
	}

	MPI_Barrier(MPI_COMM_WORLD); //барьерная синхронизация процессов

	//начало замера времени для каждого процесса
	auto t1 = std::chrono::high_resolution_clock::now();

	//перемножение матриц
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			for (int k = 0; k < m; ++k) {
				C[i*n + j] += A[i*n + k] * B[k*n + j]; 
			}
		}
	}
	
	//конец замера времени
	auto t2 = std::chrono::high_resolution_clock::now();
	double duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

	//вывод время выполнения перемножения матриц на каждом процессе
	std::cout << "Duration on process " << rank
			  << " in ms " << duration << std::endl;
 
	MPI_Finalize();
}