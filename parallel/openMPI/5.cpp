// Подробно разобрать пример ниже, запустить и объяснить его.
 // Преобразовать программу, используя в  условии поле MPI_TAG структуры status.

#include <iostream>
#include <mpi.h>

int main(int argc, char **argv) {
	MPI_Init(&argc, &argv);
	MPI_Status status;
	// MPI_Source (номер процесса отправителя)
	// MPI_Tag (идентификатор сообщения)
	// MPI_Error (код ошибки)
	
	int size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	int ibuf = 12333;
	float rbuf = 1232.322;

	if (rank == 1) 
		MPI_Send(&ibuf, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
	
	if (rank == 2)
		MPI_Send(&rbuf, 1, MPI_FLOAT, 0, 2, MPI_COMM_WORLD);

	if (rank == 0) {
		// номер процесса-отправителя или MPI_ANY_SOURCE
		// идентификатор ожидаемого сообщения или MPI_ANY_TAG
		// идентификатор группы

		// структуре ожидаемого сообщения с блокировкой
		// определяет только факт прихода сообщения
		for (int i = 1; i < 2; ++i) {
			MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			if(status.MPI_TAG == 1) {
				MPI_Recv(&ibuf, 1, MPI_INT, MPI_ANY_SOURCE, status.MPI_TAG, MPI_COMM_WORLD, &status);
				std::cout << "Process 0 recv " << ibuf << std::endl;
			} else if(status.MPI_TAG == 2) {
				MPI_Recv(&rbuf, 1, MPI_FLOAT, MPI_ANY_SOURCE, status.MPI_TAG, MPI_COMM_WORLD, &status);
				std::cout << "Process 0 recv " << rbuf << std::endl;
			}

		}

	}

	MPI_Finalize();
	return 0;
}