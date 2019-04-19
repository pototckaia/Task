// MPI. Отложенные запросы на взаимодействие. 
// Схема итерационного метода с обменом по кольцевой
// топологии при помощи отложенных запросов.

// Найти и исправить ошибки, дописать цикл for. В sbuf[0] и sbuf[1] могут храниться любые значения.
// В каких случаях необходимо использовать цикл?

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
	

	float rbuf[2], sbuf[2];

// создает персистентный запрос для операции приема. 
// Аргумент buf маркируется как OUT, поскольку пользователь разрешает запись в приемный буфер, 
// передавая аргумент MPI_RECV_INIT.
	MPI_Recv_init(rbuf, 1, MPI_FLOAT, prev, 5, MPI_COMM_WORLD, reqs);
	MPI_Recv_init(rbuf + 1, 1, MPI_FLOAT, next, 6, MPI_COMM_WORLD, reqs + 1);

// создает персистентный коммуникационный запрос для операции передачи стандартного режима
// и связывает для этого все аргументы операции передачи.	
	MPI_Send_init(sbuf, 1, MPI_FLOAT, prev, 6, MPI_COMM_WORLD, reqs + 2);
	MPI_Send_init(sbuf + 1, 1, MPI_FLOAT, next, 5, MPI_COMM_WORLD, reqs + 3);
	
// с одним и тем же набором аргументов повторно выполняется во внутреннем цикле параллельных вычислений.
// однократного включения списка аргументов в персистентный (persistent) коммуникационный запрос и 
// повторного использования этого запроса для инициации и завершения обмена.
// коммуникационный порт или ``полуканал''
// уменьшить накладные расходы на коммуникацию между процессом и коммуникационным контроллером

// Персистентный запрос после создания не активен - никакого активного обмена не подключено к запросу.
	for(int i= 0; i < 3; ++i) {
		sbuf[0] = i;
		sbuf[1] = 2*i;
		MPI_Startall(4, reqs);
		MPI_Waitall(4, reqs, stats);
		std::cout << "Process " << rank 
				  << " recvive " << rbuf[0] << " " 
				  << rbuf[1] << std::endl; 
	}

	MPI_Request_free(reqs);
	MPI_Request_free(reqs + 1);
	MPI_Request_free(reqs + 2);
	MPI_Request_free(reqs + 3);
	
	MPI_Finalize();
}




