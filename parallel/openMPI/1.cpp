#include <mpi.h>
#include <iostream>

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
        std::cout << "Number of processes " << world_size << std::endl;
        std::cout << "Hello from process " << world_rank << std::endl;
        for (int i = 1; i < world_size; ++ i) {
            int message;
            MPI_Status status;
            std::cout << "Wait " << i << std::endl;
            MPI_Recv(&message, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            std::cout << "Hello from processor " << message << std::endl;
        }
    } else {
        MPI_Send(&world_rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();

    return 0;
}