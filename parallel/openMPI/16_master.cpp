// MPI. Динамическое управление процессами. Порождение процессов

// Для выполнения задания необходимо создать и скомпилировать две программы: Master (мастер) и Slave
// (рабочий). Мастер должен запускать рабочего, поэтому будьте внимательны с именами выполняемых
// файлов.
// Мастер запускать через команду mpiexec для одного процесса.
// Пример запуска: mpiexec -n 1 ./master

// Разобраться с новыми функциями, объяснить выполнение программы.
// Добавить третий процесс, который будет передавать от рабочего мастеру число запущенных процессов,
// мастер должен принять и вывести на экран.

// Код программы Master
#include "mpi.h"
#include <iostream>

int main(int argc, char **argv) {
	MPI_Init(&argc, &argv);
	
	int size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	MPI_Comm child;
	
	char slave[15] ="./16_slave";
// Spawn up to maxprocs instances of a single MPI application
//   char *command,  char *argv[], int maxprocs, MPI_Info info,int root, MPI_Comm comm, MPI_Comm *intercomm, int array_of_errcodes[]	
	
// MPI_COMM_SPAWN пытается запустить maxprocs одинаковых копий программы MPI, определяемой command, устанавливая с ними соединение и возвращая интеркоммуникатор. 
// Порожденные процессы называются потомками, а процессы, их породившие, родителями. Потомки имеют свой собственный MPI_COMM_WORLD, отдельный от родителей. 
// Процедура MPI_COMM_SPAWN является коллективной для comm, и не завершается, пока в потомках не вызовется MPI_INIT. 
// Подобным образом, MPI_INIT в потомках не завершается, пока все родители не вызовут MPI_COMM_SPAWN. 
// В этом смысле, MPI_COMM_SPAWN в родителях и MPI_INIT в потомках формируют коллективную операцию над объединением родительских и дочерних процессов. 
// Интеркоммуникатор, возвращаемый MPI_COMM_SPAWN, содержит родительские процессы в локальной группе и процессы-потомки в удаленной группе. 
// Порядок процессов в локальной и удаленной группах такой же, как и порядок группы comm для родителей и MPI_COMM_WORLD для потомков. 
// Этот интеркоммуникатор может быть получен в потомке через функцию MPI_COMM_GET_PARENT.
	MPI_Comm_spawn(slave, MPI_ARGV_NULL, 3, MPI_INFO_NULL, 0, MPI_COMM_SELF, &child, MPI_ERRCODES_IGNORE);

	int rank1, rank2;
	MPI_Status status;
	MPI_Recv(&rank1, 1, MPI_INT, 0, 0, child, &status);
	MPI_Recv(&rank2, 1, MPI_INT, 1, 1, child, &status);
	int size_child;
	MPI_Recv(&size_child, 1, MPI_INT, 2, 2, child, &status);
	
	std::cout << "Size slaves: " << size_child << std::endl;
	std::cout << "Slaves " << rank1 << " and " << rank2 << " are working" << std::endl;
	
	MPI_Finalize();
	return 0;
}
