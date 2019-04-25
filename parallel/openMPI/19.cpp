
#include <iostream>
#include "mpi.h"

int main(int argc, char **argv) {
	MPI_Init(&argc, &argv);
	
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	MPI_File fh;
	std::string fileName = "file19.txt";
	MPI_File_open(MPI_COMM_WORLD, fileName.c_str(), MPI_MODE_RDONLY, MPI_INFO_NULL, &fh);

        MPI_Offset gEnd, gStart;

        MPI_Offset fileSize;
        MPI_File_get_size(fh, &fileSize);
        --fileSize;  // eof

        int sizeBuf = fileSize / size;
        gStart = rank * sizeBuf;
        gEnd = gStart + sizeBuf - 1;
        if (rank == size - 1) gEnd = fileSize - 1;

        sizeBuf =  gEnd - gStart + 1;

        char *buf= new char[sizeBuf + 1];

	
        MPI_File_read_at_all(fh, gStart, buf, sizeBuf, MPI_CHAR, MPI_STATUS_IGNORE);
	
	std::cout << "process " << rank << std::endl 
		  << "buf= " << buf << std::endl;
	
	MPI_File_close(&fh);
	MPI_Finalize();
}