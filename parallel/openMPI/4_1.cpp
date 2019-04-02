#include <iostream>
#include "mpi.h"

#define NTIMES 100

// Подробно разобрать пример ниже, запустить и объяснить.
// Определите время выполнения программы из предыдущего задания.
int main(int argc, char **argv) {
	MPI_Init(&argc, &argv);
	
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	char *name = new char;
	int len;
	MPI_Get_processor_name(name, &len);

	double time_start = MPI_Wtime();
	double time_finish;
	for (int i = 0; i < NTIMES; ++i)
		time_finish = MPI_Wtime();

	std::cout << "processor " << name << ", process " << rank 
		 << "time = " << (time_finish - time_start) / NTIMES << std::endl;
	MPI_Finalize();
	return 0;
}