#include <mpi.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
// Рутовый процесс принимает сообщения от дочерних процессов и определяет, содержит ли
// последовательность хотя бы два рядом стоящих нечетных числа.

int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);


    if (world_rank == 0) {
        std::vector<int> recv(world_size);
        for (int i = 1; i < world_size; ++ i) {
            int message;
            MPI_Status status;
            MPI_Recv(&message, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
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
        MPI_Send(&send, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();

    return 0;
}