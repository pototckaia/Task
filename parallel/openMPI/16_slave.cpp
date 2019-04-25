#include "mpi.h"
#include <iostream>

int main(int argc, char **argv) {
	MPI_Init(&argc, &argv);
	
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	MPI_Comm parent;
	MPI_Comm_get_parent(&parent);
	

	if (rank == 2) {
		MPI_Send(&size, 1, MPI_INT, 0, rank, parent);
	} else {
		MPI_Send(&rank, 1, MPI_INT, 0, rank, parent);
	}
	
	MPI_Finalize();
	return 0;
}