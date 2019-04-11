// Напишите программу на MPI, в которой операция глобального суммирования элементов вектора
// моделируется схемой сдваивания (каскадная схема) с использованием пересылок данных типа точка-
// точка. Сравнить эффективность такого моделирования с использованием процедуры MPI_Reduce для
// разного числа процессов и разной длины векторов.

// MPI_Reduce
// объединяет элементы входного буфера каждого процесса в группе, используя
// операцию op , и возвращает объединенное значение в выходной буфер процесса с номером root.

// MPI_Reduce(sendbuf, recvbuf, count, datatype, op, root, comm)
// IN sendbuf адрес посылающего буфера
// OUT recvbuf адрес принимающего буфера (используется только корневым процессом)
// IN count количество элементов в посылающем буфере (целое)
// IN datatype тип данных элементов посылающего буфера
// IN op операция редукции
// IN root номер главного процесса (целое)
// IN comm коммуникатор

// All-Reduce
// что результат появляется в буфере приема у всех членов группы

// MPI_Allreduce(sendbuf, recvbuf, count, datatype, op, comm)
// IN sendbuf начальный адрес буфера посылки
// OUT recvbufначальный адрес буфера приема
// IN count количество элементов в буфере посылки (целое)
// IN datatype тип данных элементов буфера посылки
// IN op операция
// IN comm коммуникатор
#include <iostream>
#include <chrono>
#include <mpi.h>
#include "helper.h"

int main(int argc, char** argv) {
	MPI_Init(&argc, &argv);
	MPI_Status status;

	int size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0) {
		printElement("Dimension");
		printElement("Result reduce");
		printElement("Time sum reduce (mc)");
		printElement("Result cascade");
		printElement("Time sum cascade (mc)");
		printNewLine();	
	}


	for (int l = 1; l < argc; ++l) {
		int N = std::atol(argv[l]);
		double *arr = new double[N];
		for (int i = 0; i < N; ++i) arr[i] = 1;
		
		int length = N / size;
		int size_piece = length;
		int remain = N % size;
		if (rank == size - 1) { size_piece += remain; }

		int begin = 0;
		if (rank != 0) { begin = rank * length; }

		double local_sum = 0.0;
		double* start_ptr = arr + begin;
		for (int i = 0; i < size_piece; ++i, ++start_ptr) {
			local_sum += *start_ptr;
		}

		double sum_reduce = 0.0;
		auto t1 = std::chrono::high_resolution_clock::now();
		MPI_Reduce(&local_sum, &sum_reduce, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
		auto t2 = std::chrono::high_resolution_clock::now();
		double time_reduce = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

		t1 = std::chrono::high_resolution_clock::now();
		for (int i = 1; i < size; i *= 2) {
			if (rank % (2*i) != 0) {
				MPI_Send(&local_sum, 1, MPI_DOUBLE, rank - i, 0, MPI_COMM_WORLD);
				break;
			} else if (rank + i < size) {
				double tmp = 0.0;
				MPI_Recv(&tmp, 1, MPI_DOUBLE, rank + i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				local_sum += tmp;
			}
		}
		t2 = std::chrono::high_resolution_clock::now();		
		double time_cascade = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

	
		if (rank == 0) {
			printElement(N);
			printElement(sum_reduce);
			printElement(time_reduce);
			printElement(local_sum);
			printElement(time_cascade);
			printNewLine();
		}
	
		delete[] arr;
	}


    MPI_Finalize();
	return 0;
}