#include <mpi.h>

#include <iostream>
#include <vector>
#include <chrono>	
#include "helper.h"

using Iter = std::vector<double>::iterator;
using Vec = std::vector<double>;

double dot(Iter x, Iter y, int n) {
	double prod = 0.0;
	for (int i = 0; i < n; ++i) {
		prod += (*x)*(*y);
		++x; ++y;
	}
	return prod;
}

int main(int argc, char **argv) {
	MPI_Init(&argc, &argv);
	MPI_Status status;

	int size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	for (int l = 1; l < argc; ++l) {

		long N = std::atol(argv[l]);;	
		Vec A(N, 1.0), B(N, 1.0);
		if (rank == 0) {
			printElement("Rank");
			printElement("Duration (ms)");
			printNewLine();			
		}

		auto t1 = std::chrono::high_resolution_clock::now();
		
		int length = N / size;
		int size_piece = length;
		int remain = N % size;
		if (rank == size - 1) { size_piece += remain; }

		int begin = 0;
		if (rank != 0) { begin = rank * length; }

		double local_dot = dot(A.begin() + begin, A.begin() + begin, size_piece);

		double dot = 0.0;
		MPI_Reduce(&local_dot, &dot, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
		
		auto t2 = std::chrono::high_resolution_clock::now();
		double duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

		if (rank == 0) {
			std::cout << "Dimension: " << N << std::endl;
			std::cout << "Result: " << dot << std::endl;
		}

		printElement(rank);
		printElement(duration);
		printNewLine();
	}

	MPI_Finalize();
	return 0;
}
