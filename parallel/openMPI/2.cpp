#include <mpi.h>
#include <iostream>

// Процесс 1 отправляет сообщение процессу 2, процесс 2 отправляет сообщение процессу 3, и т.д.,
// последний процесс в группе из n процессов принимает сообщение от процесса с номером n-1 и
// отправляет сообщение рутовому процессу, которое последний выводит на консоль.

// Введение
// Атрибуты сообщения -  MPI_Status
// номер процесса-отправителя, 
// номер процесса-получателя
// идентификатор сообщения
// MPI_Source (номер процесса отправителя),
//  MPI_Tag (идентификатор сообщения),
// MPI_Error (код ошибки);

// Процессы объединяются в группы, могут быть вложенные группы. 
// Внутри группы все процессы перенумерованы. С каждой группой ассоциирован свой коммуникатор.
// Поэтому при осуществлении пересылки необходимо указать идентификатор группы,
// внутри которой производится эта пересылка. Все процессы содержатся в группе с
// предопределенным идентификатором MPI_COMM_WORLD.

// Блокирующая посылка сообщения 
// гарантирует корректность повторного использования всех параметров после возврата из подпрограммы
// int MPI_Send(void* buf, int count, MPI_Datatype datatype, int dest, int msgtag,
// MPI_Comm comm)
//  buf - адрес начала буфера посылки сообщения
//  count - число передаваемых элементов в сообщении
//  datatype - тип передаваемых элементов
//  dest - номер процесса-получателя
//  msgtag - идентификатор сообщения
//  comm - идентификатор группы

// int MPI_Recv(void* buf, int count, MPI_Datatype datatype, int source, int msgtag,
// MPI_Comm comm, MPI_Status *status)
//  OUT buf - адрес начала буфера приема сообщения
//  count - максимальное число элементов в принимаемом сообщении
//  datatype - тип элементов принимаемого сообщения
//  source - номер процесса-отправителя
//  msgtag - идентификатор принимаемого сообщения
//  comm - идентификатор группы
//  OUT status - параметры принятого сообщения
// Если нужно узнать точное число элементов в сообщении, то можно воспользоваться
// подпрограммой MPI_Probe

// Если процесс посылает два сообщения другому процессу и оба эти сообщения
// соответствуют одному и тому же вызову MPI_Recv, то первым будет принято то сообщение,
// которое было отправлено раньше.

int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    std::cout << "Hello from process " << world_rank << std::endl;

    int message = 123;
    MPI_Status status;

    int master_rank = 0;
    int recive_rank = world_rank - 1;
    int send_rank = (world_rank == world_size - 1) ? master_rank : world_rank + 1;
    	

    if (world_rank == master_rank) {
        std::cout << "Wait message from " << world_size - 1 << std::endl;
        MPI_Recv(&message, 1, MPI_INT, world_size - 1, 0, MPI_COMM_WORLD, &status);
        std::cout << "Recive number " << message <<  " on master" << std::endl;    
    } else {
    	if (world_rank != 1) {
    		std::cout << "Process " << world_rank << " wait message from " << recive_rank << std::endl;
        	MPI_Recv(&message, 1, MPI_INT, recive_rank, world_rank, MPI_COMM_WORLD, &status);
        	std::cout << "Process " << world_rank << " recive number " << message << " from " << recive_rank << std::endl;
    	}

        std::cout << "Process " << world_rank << " send message to " << send_rank << std::endl;
        MPI_Send(&message, 1, MPI_INT, send_rank, send_rank, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}