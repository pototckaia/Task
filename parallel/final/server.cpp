#include <iostream>
#include <string>
#include "mpi.h"

#include "StateSeaBattle.h"
#include "MPIConfig.h"


void writePortName(char* portName) {
	std::string fileName = config::filePortName;

	MPI_File fh;
	MPI_File_open(MPI_COMM_WORLD, fileName.c_str(),
			MPI_MODE_CREATE | MPI_MODE_WRONLY, MPI_INFO_NULL, &fh);
	MPI_File_set_view(fh, 0, MPI_CHAR, MPI_CHAR, "native", MPI_INFO_NULL);

	MPI_Status status;
	MPI_File_write(fh, portName, strlen(portName) - 1, MPI_CHAR, &status);
	MPI_File_close(&fh);
}

int main(int argc, char **argv) {
	MPI_Init(&argc, &argv);

  MPI_Status status;
	char port_name[MPI_MAX_PORT_NAME];
	MPI_Open_port(MPI_INFO_NULL, port_name);

	std::cout << "Portname: " << port_name << std::endl;
	writePortName(port_name);
	std::cout << "Wait client" << std::endl;

	MPI_Comm intercomm;
	MPI_Comm_accept(port_name, MPI_INFO_NULL, 0, MPI_COMM_SELF, &intercomm);
	std::cout << "Client connected" << std::endl;

  StateSeBattle s;
  s.prepare();

  while (!s.isFinish()) {
    auto p = s.fire();
    MPI_Send(&p.first, 1, MPI_UNSIGNED, 0, config::tag_x, intercomm);
    MPI_Send(&p.second, 1, MPI_UNSIGNED, 0, config::tag_y, intercomm);

    Shoot result_attack;
    MPI_Recv(&result_attack, 1, MPI_INT, 0, config::tag_result, intercomm, &status);
    s.result_fire(result_attack);

    if (s.isFinish()) break;

    unsigned x, y;
    MPI_Recv(&x, 1, MPI_UNSIGNED, 0, 0, intercomm, &status);
    MPI_Recv(&y, 1, MPI_UNSIGNED, 0, 1, intercomm, &status);

    result_attack = s.attack(std::make_pair(x, y));
    MPI_Send(&result_attack, 1, MPI_INT, 0, config::tag_result, intercomm);
  }


  MPI_Comm_free(&intercomm);
	MPI_Close_port(port_name);
	MPI_Finalize();
	return 0;
}
