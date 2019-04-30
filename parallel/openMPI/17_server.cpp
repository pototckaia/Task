// Имя порта
// Ожидание клиента...
// Клиент подключился
// Сервер отправил значение: 25 
// Сервер получил значение: 42 

#include <iostream>
#include <string>
#include "mpi.h"

void writePortName(char* portName) {
	std::string fileName = "file17PortName.txt";
	MPI_File fh;
	MPI_File_open(MPI_COMM_WORLD, fileName.c_str(), 
			MPI_MODE_CREATE | MPI_MODE_WRONLY, MPI_INFO_NULL, &fh);
	MPI_File_set_view(fh, 0, MPI_CHAR, MPI_CHAR, "native", MPI_INFO_NULL);

	MPI_Status status;
	MPI_File_write(fh, portName, strlen(portName), MPI_CHAR, &status);
	MPI_File_close(&fh);
}

int main(int argc, char **argv) {
	MPI_Init(&argc, &argv);

	char port_name[MPI_MAX_PORT_NAME];
	MPI_Open_port(MPI_INFO_NULL, port_name);
	
	std::cout << "Portname: " << port_name << std::endl;
	writePortName(port_name);
	std::cout << "Wait client" << std::endl;

	MPI_Comm intercomm;
	MPI_Comm_accept(port_name, MPI_INFO_NULL, 0, MPI_COMM_SELF, &intercomm);
	std::cout << "Client connected" << std::endl;
	
	int r = 42;
	MPI_Status status;

	std::cout << "Server send: " << r << std::endl;
	MPI_Send(&r, 1, MPI_INT, 0, 0, intercomm);

	MPI_Recv(&r, 1, MPI_INT, 0, 0, intercomm, &status);
	std::cout << "Server receive: " << r << std::endl;

	MPI_Comm_free(&intercomm);
	MPI_Close_port(port_name);
	
	MPI_Finalize();	
	return 0;
}

// MPI_Open_port(MPI_Info info, char *port_name)
// Устанавливает порт для сервера, по которому клиент может получить к нему доступ.
// Входные параметры
// info - информация о том, как установить порт для MPI_Comm_accept (по умолчанию MPI_INFO_NULL).
// Выходные параметры
// port_name - Новый установленный порт (строка). Имя порта — это сетевой адрес. Он является уникальным
// для коммуникационного пространства, к которому он относится (определяется реализацией) и может
// использоваться любым клиентом коммуникационного пространства.
// MPI_Open_port устанавливает сетевой адрес, копируя его в строку port_name, по которому сервер в
// состоянии принимать соединения от клиентов. port_name поддерживается системой, возможно используя
// информацию аргумента info.
// MPI копирует имя порта, поддерживаемое системой, в port_name. Аргумент port_name определяет вновь
// открываемый порт и может использоваться клиентом для контакта с сервером. С помощью
// MPI_MAX_PORT_NAME (MPI::MAX_PORT_NAME в С++) определяется максимальный размер строки, которая
// может поддерживаться системой.
// Имя порта может использоваться повторно после его освобождения через MPI_CLOSE_PORT и
// освобождения системой.

// MPI_Comm_accept(char *port_name, MPI_Info info, int root, MPI_Comm comm, MPI_Comm *newcomm)
// для приема соединения с клиентом.
// IN port_name Имя порта (строка, используется только root)
// IN info Информация, зависящая от реализации (дескриптор, используется только root)
// IN root Ранг в comm для узла root (целое)
// IN comm Интракоммуникатор, внутри которого выполняется коллективный вызов (дескриптор)
// OUT newcomm Интеркоммуникатор с клиентом в качестве удаленной группы (дескриптор)
// MPI_COMM_ACCEPT устанавливает соединение с клиентом. Это коллективная операция посредством
// вызывающего коммуникатора. Она возвращает интеркоммуникатор, позволяющий установить связь с
// клиентом.
// port_name должно быть установлено через вызов MPI_OPEN_PORT.
// Аргумент info является строкой, определяемой реализацией, позволяющей точный контроль над вызовом
// MPI_COMM_ACCEPT.
// MPI_COMM_ACCEPT является блокирующим вызовом. Пользователь может реализовать неблокирующий
// доступ, помещая MPI_COMM_ACCEPT в отдельный поток.

// MPI_Comm_free(MPI_Comm *comm)
// Функция уничтожения коммуникатора

// MPI_Close_port(char *port_name)
// Эта функция освобождает сетевой адрес, представленный port_name.