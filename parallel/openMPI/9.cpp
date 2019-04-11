// MPI. Передача и прием сообщений без блокировки. Обмен по кольцевой топологии при помощи
// неблокирующих операций.


#include <iostream>
#include "mpi.h"

int main(int argc, char **argv) {
	MPI_Init(&argc,&argv);

	MPI_Request reqs[4];
	MPI_Status stats[4];
	
	int size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	int prev = rank - 1;
	int next = rank + 1;
	if(rank == 0) prev = size - 1;
	if(rank == size - 1) next = 0;
	
	int buf[2];
	MPI_Irecv(&buf[0], 1, MPI_INT, prev, 5, MPI_COMM_WORLD, &reqs[0]);
	MPI_Irecv(&buf[1], 1, MPI_INT, next, 6, MPI_COMM_WORLD, &reqs[1]);
	
	MPI_Isend(&rank, 1, MPI_INT, prev, 6, MPI_COMM_WORLD, &reqs[2]);
	MPI_Isend(&rank, 1, MPI_INT, next, 5, MPI_COMM_WORLD, &reqs[3]);

	MPI_Waitall(4, reqs, stats);
	
	// Здесь необходимо вывести на экран номер текущего процесса, и что он получает от предыдущего и
	// следующего процессов.
	
	MPI_Finalize();
}