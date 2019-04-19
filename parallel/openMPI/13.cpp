// MPI. Операции с коммуникаторами. Разбиение коммуникатора.

// Разобраться с новыми функциями, объяснить выполнение программы.

#include <iostream>
#include "mpi.h"


int main(int argc, char **argv) {
	MPI_Init(&argc, &argv);
	
	int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	MPI_Group group;
	// Функция создания группы с помощью коммуникатора
	// Функция создает группу group для множества процессов, входящи
	MPI_Comm_group(MPI_COMM_WORLD, &group);
	
	int ranks[128];
	for(int i = 0; i < size/2; ++i) 
		ranks[i] = i;

	MPI_Group new_group;
	if(rank < size/2) 
// создает новую группу, которая состоит из процессов существующей группы, 
// перечисленных в массиве ranks. Процесс с номером i в новой группе есть процесс
// с номером ranks[i] в существующей группе. 
// Каждый элемент в массиве ranks должен иметь корректный номер в группе group,
// и среди этих элементов не должно быть совпадающих.
		MPI_Group_incl(group, size/2, ranks, &new_group);
	else 
// создает новую группу из тех процессов group, которые не перечислены в массиве ranks. 
// Процессы упорядочиваются как в группе group. 
// Каждый элемент в массиве ranks должен иметь корректный номер в группе group,
// и среди них не должно быть совпадающих.
		MPI_Group_excl(group, size/2, ranks, &new_group);

	MPI_Comm new_comm;
// Эта функция создает коммуникатор для группы group.
// Для процессов, которые не являются членами группы, возвращается значение MPI_COMM_NULL. 
// Функция возвращает код ошибки, если группа group не является подгруппой родительского коммуникатора.
	MPI_Comm_create(MPI_COMM_WORLD, new_group, &new_comm);

	int rbuf;
// с сохранением результата в адресном пространстве всех процессов
	MPI_Allreduce(&rank, &rbuf, 1, MPI_INT, MPI_SUM, new_comm);

	int new_rank;
// Функция MPI_Group_rank возвращает номер в группе процесса, вызвавшего функцию.
// Если процесс не является членом группы, то возвращается значение MPI_UNDEFINED.
	MPI_Group_rank(new_group, &new_rank);

	std::cout << "rank = " << rank << " "
			  << "new rank = " << new_rank << " "
			  << "rbuf = " << rbuf << std::endl;

	MPI_Finalize();
}