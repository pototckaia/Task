// MPI. Передача и прием сообщений без блокировки. Обмен по кольцевой топологии при помощи
// неблокирующих операций.


// Неблокирующая функция чтения параметров полученного сообщения MPI_Iprobe
// int MPI_Iprobe (
	// int source, int tag, MPI_Comm comm, int *flag, MPI_Status *status)
// Если flag=true, то операция завершилась, и в переменной status находятся атрибуты этого сообщения.


// Функция ожидания завершения неблокирующей операции MPI_Wait
// int MPI_Wait(MPI_Request *request, MPI_Status *status)

// Функция проверки завершения неблокирующей операции MPI_Test
// int MPI_Test(MPI_Request *request, int *flag, MPI_Status *status)



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
	
	// int MPI_Irecv(void* buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request)
	MPI_Irecv(&buf[0], 1, MPI_INT, prev, 5, MPI_COMM_WORLD, &reqs[0]);
	MPI_Irecv(&buf[1], 1, MPI_INT, next, 6, MPI_COMM_WORLD, &reqs[1]);
	
	// void* buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request
	MPI_Isend(&rank, 1, MPI_INT, prev, 6, MPI_COMM_WORLD, &reqs[2]);
	MPI_Isend(&rank, 1, MPI_INT, next, 5, MPI_COMM_WORLD, &reqs[3]);

	MPI_Waitall(4, reqs, stats);

	// Здесь необходимо вывести на экран номер текущего процесса, и что он получает от предыдущего и
	// следующего процессов.	
	std::cout << "Process " << rank 
			  << " get " << buf[0] << " and " << buf[1] << std::endl;
	
	MPI_Finalize();
}