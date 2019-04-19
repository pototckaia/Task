// MPI. Упаковка данных. Пересылка упакованных данных
// Разобраться с новыми функциями, объяснить выполнение программы.
// Вывести на экран значения номера процесса и массивов a[i], b[i], до упаковки и рассылки, и после.
// Посмотреть, как работает широковещательная рассылка.

#include <iostream>
#include "mpi.h"

void printf_(float* a, char* b, int rank, int n) {
	std::cout << "rank = " << rank << " ";
	for (int i = 0; i < n; ++i)	{
		std::cout << "a[" << i << "]=" << a[i] << " "
				  << "b[" << i << "]=" << b[i] << " "
				  << std::endl;
	}
}

int main(int argc, char **argv) {
	MPI_Init(&argc, &argv);
	
	int size, rank;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	float a[10];
	char b[10];
	for (int i = 0; i < 10; ++i)	{
		a[i] = rank + 1.0;
		if (rank == 0) 
			b[i] = 'a';
		else
			b[i] = 'b';
	}
	printf_(a, b, rank, 10);

	int position = 0;
	char buf[100];
	if(rank == 0) {
// Функция MPI_Pack упаковывает элементы предопределенного или производного типа MPI, 
// помещая их побайтное представление в выходной буфер.
// На выходе из подпрограммы значение position увеличивается на число упакованных байт, 
// указывая на первый свободный байт. 
		MPI_Pack(a, 10, MPI_FLOAT, buf, 100, &position, MPI_COMM_WORLD);
		MPI_Pack(b, 10, MPI_CHAR, buf, 100, &position, MPI_COMM_WORLD);

// рассылка информации от одного процесса всем остальным членам некоторой области связи
// Процесс с номером root рассылает сообщение из своего буфера передачи всем процессам области связи 
// коммуникатора comm.
// void* buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm 
		MPI_Bcast(buf, 100, MPI_PACKED, 0, MPI_COMM_WORLD);
	} else {
		MPI_Bcast(buf, 100, MPI_PACKED, 0, MPI_COMM_WORLD);
		position = 0;

// извлекает заданное число элементов некоторого типа из побайтного представления элементов во входном массиве.
// Результат распаковки помещается в область памяти с начальным адресом outbuf.
		MPI_Unpack(buf, 100, &position, a, 10, MPI_FLOAT, MPI_COMM_WORLD);
		MPI_Unpack(buf, 100, &position, b, 10, MPI_CHAR, MPI_COMM_WORLD);
	}

	if (rank != 0) {
		printf_(a, b, rank, 10);
	}

	MPI_Finalize();
}