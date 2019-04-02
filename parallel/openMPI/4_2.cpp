#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include "mpi.h"

#define NTIMES 10

// Подробно разобрать пример ниже, запустить и объяснить.
// Определите время выполнения программы из предыдущего задания.
int main(int argc, char **argv) {
	MPI_Init(&argc, &argv);
	
	int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);


	char *name = new char;
	int len;
	MPI_Get_processor_name(name, &len);

	double time_start = MPI_Wtime();
	double time_finish;
	for (int l = 0; l < NTIMES; ++l) {
		// 3.cpp
	    
	    if (world_rank == 0) {
	        std::vector<int> recv(world_size);
	        for (int i = 1; i < world_size; ++ i) {
	            int message;
	            MPI_Status status;
	            MPI_Recv(&message, 1, MPI_INT, MPI_ANY_SOURCE, l, MPI_COMM_WORLD, &status);
	            recv[i] = message;
	        }
	        for (int i = 2; i < world_size; ++i) {
	            if (recv[i -1] % 2 == 1 && recv[i] % 2 == 1) {
	                std::cout << "Два нечетных числа " << recv[i -1] << " " << recv[i]
	                          << " на процессах " << i - 1 << " и "<< i << std::endl;
	            }
	        }

	    } else {
	        std::srand(unsigned(std::time(0)));
	        int send = std::rand();
	        MPI_Send(&send, 1, MPI_INT, 0, l, MPI_COMM_WORLD);
	    }
		time_finish = MPI_Wtime();

	}

	std::cout << "processor " << name << ", process " << world_rank 
		 << " time = " << (time_finish - time_start) / NTIMES << std::endl;
	MPI_Finalize();
	return 0;
}