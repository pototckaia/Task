// Попытка подключения
// Соединение с сервером
// Клиент отправил значение: 42
// Клиент получил значение: 25


#include <iostream>
#include <string>
#include "mpi.h"

std::string readPortName() {
	std::string fileName = "file17PortName.txt";
	MPI_File fh;
	MPI_File_open(MPI_COMM_WORLD, fileName.c_str(), 
			MPI_MODE_RDONLY, MPI_INFO_NULL, &fh);
	MPI_File_set_view(fh, 0, MPI_CHAR, MPI_CHAR, "native", MPI_INFO_NULL);

	MPI_Offset fileSize;
	MPI_File_get_size(fh, &fileSize);	

	MPI_Status status;
	char port_name[MPI_MAX_PORT_NAME];
	MPI_File_read(fh, port_name, fileSize, MPI_CHAR, &status);
	MPI_File_close(&fh);
	
	std::string portName = port_name;
	return portName;
}


int main(int argc, char **argv) {
	MPI_Init(&argc, &argv);

	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	std::cout << "start read file" << std::endl;
	auto portName = readPortName();

	std::cout << "Portname: " << portName << std::endl;
	std::cout << "Attempt to connect" << std::endl;
	MPI_Comm intercomm;
	MPI_Comm_connect(portName.c_str(), MPI_INFO_NULL, 0, MPI_COMM_SELF, &intercomm);
	std::cout << "Connection to server" << std::endl;

	int r;
	MPI_Status status;
	MPI_Recv(&r, 1, MPI_INT, 0, 0, intercomm, &status);
	std::cout << "Client receive: " << r << std::endl;

	int s = 199;
	std::cout << "Client send: " << s << std::endl;
	MPI_Send(&s, 1, MPI_INT, 0, 0, intercomm);
	
	
	
	MPI_Finalize();
	return 0;
}