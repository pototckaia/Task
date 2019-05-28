#include <iostream>
#include <string>
#include "mpi.h"

#include "StateSeaBattle.h"
#include "MPIConfig.h"

std::string readPortName() {
  std::string fileName = config::filePortName;

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
  MPI_Status status;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  auto portName = readPortName();

  std::cout << "Portname: " << portName << std::endl;
  std::cout << "Attempt to connect" << std::endl;
  MPI_Comm intercomm;
  MPI_Comm_connect(portName.c_str(), MPI_INFO_NULL, 0, MPI_COMM_SELF, &intercomm);
  std::cout << "Connection to server" << std::endl;
  std::cout << "Start game" << std::endl;

  StateSeBattle s;
  s.prepare();

  while (!s.isFinish()) {
    unsigned x, y;
    MPI_Recv(&x, 1, MPI_UNSIGNED, 0, config::tag_x, intercomm, &status);
    MPI_Recv(&y, 1, MPI_UNSIGNED, 0, config::tag_y, intercomm, &status);

    Shoot result_attack = s.attack(std::make_pair(x, y));
    MPI_Send(&result_attack, 1, MPI_INT, 0, config::tag_result, intercomm);

    if (s.isFinish()) break;

    auto p = s.fire();
    MPI_Send(&p.first, 1, MPI_UNSIGNED, 0, config::tag_x, intercomm);
    MPI_Send(&p.second, 1, MPI_UNSIGNED, 0, config::tag_y, intercomm);

    MPI_Recv(&result_attack, 1, MPI_INT, 0, config::tag_result, intercomm, &status);
    s.result_fire(result_attack);
  }


  MPI_Finalize();
  return 0;
}