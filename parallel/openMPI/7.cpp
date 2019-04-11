// Напишите программу на MPI, в которой два процесса обмениваются сообщениями, замеряется время
// на одну итерацию обмена, 
// определяется зависимость времени обмена от длины сообщения.
// Определите латентность и 
// максимально достижимую пропускную способность коммуникационной сети.

#include <iostream>
#include <chrono>
#include <mpi.h>
#include "helper.h"


int main(int argc, char **argv) {
	MPI_Init(&argc, &argv);
	MPI_Status status;

	int worl;
	MPI_Comm_size(MPI_COMM_WORLD, &worl);
	
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	const int N = 100;

	if (rank == 0) {
		printElement("Count element");
		printElement("Time (ms)");
		printElement("Bandwidth (Mbyte in c)");
		printElement("Latency");
		printNewLine();	
	}

	// for (int l = 1; l < argc; ++l)	{
		MPI_Barrier(MPI_COMM_WORLD); 

		long size = std::atol(argv[1]);
		long L = size * sizeof(int);

		long time = 0;
		long time_l = 0; 

		int* buf = new int[size];

		for (int i = 0; i < N; ++i) {
			if (rank == 0) {
				auto t1 = std::chrono::high_resolution_clock::now();
				MPI_Send(buf, size, MPI_INT, 1, 12, MPI_COMM_WORLD);
				MPI_Recv(buf, size, MPI_INT, 1, 14, MPI_COMM_WORLD, &status);
				auto t2 = std::chrono::high_resolution_clock::now();
				double duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
				time += duration / N;

				t1 = std::chrono::high_resolution_clock::now();
				MPI_Send(buf, 0, MPI_INT, 1, 15, MPI_COMM_WORLD);
				MPI_Recv(buf, 0, MPI_INT, 1, 16, MPI_COMM_WORLD, &status);
				t2 = std::chrono::high_resolution_clock::now();
				duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
				time_l += duration / N;

			} else 	if (rank == 1) {
				MPI_Recv(buf, size, MPI_INT, 0, 12, MPI_COMM_WORLD, &status);
				MPI_Send(buf, size, MPI_INT, 0, 14, MPI_COMM_WORLD);

				MPI_Recv(buf, 0, MPI_INT, 0, 15, MPI_COMM_WORLD, &status);
				MPI_Send(buf, 0, MPI_INT, 0, 16, MPI_COMM_WORLD);
			}
		}

		if (rank == 0) {
			printElement(size);
			printElement(time);
			// byte in mc
			double bandwidth = 2 * N * L / time;
			// Mbyte in c
			bandwidth = bandwidth * 0.001;
			printElement(bandwidth);
			double latency = time_l / 2 / N; 
			printElement(latency);
			printNewLine();
		}

		delete[] buf;
	// }
	
	MPI_Finalize();
	return 0;
}