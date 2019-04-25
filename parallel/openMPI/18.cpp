// MPI. Параллельный ввод/вывод. Работа с файлами. Доступ к данным. Буферизованное чтение из файла

// Написать функцию, которая будет создавать файл "file.txt" со случайным содержимым (либо с
// определенным текстом). Функция должна выполняться до считывания содержимого файла программой. +++
// Программу запускать на одном процессе. Проверить, правильно ли выводится содержимое файла. Добавить
// опцию, которая будет удалять файл при закрытии.

#include <iostream>
#include <string>
#include "mpi.h"
#define BUFSIZE 200

void create_file(std::string& fileName) {
	MPI_File fh;
	MPI_File_open(MPI_COMM_WORLD, fileName.c_str(), MPI_MODE_CREATE | MPI_MODE_WRONLY, 
			MPI_INFO_NULL, &fh);
	MPI_File_set_view(fh, 0, MPI_CHAR, MPI_CHAR, "native", MPI_INFO_NULL);

	std::string text = 
		"Two roads diverged in a yellow wood,\n"
		"And sorry I could not travel both\n"
		"And be one traveler, long I stood\n"
		"And looked down one as far as I could\n"
		"\n"
		"To where it bent in the undergrowth.\n"
		"Then took the other, as just as fair,\n"
		"And having perhaps the better claim,\n"
		"Because it was grassy and wanted wear;\n"
		"Though as for that the passing there\n"
		"Had worn them really about the same.\n";
		
	MPI_Status status;
	MPI_File_write(fh, text.c_str(), text.size(), MPI_CHAR, &status);

	MPI_File_close(&fh);
}

int main(int argc, char **argv) {
	MPI_Init(&argc, &argv);

	std::string fileName = "file18.txt";
	
	create_file(fileName);
	
	MPI_File fh;
	MPI_File_open(MPI_COMM_WORLD, fileName.c_str(), MPI_MODE_RDONLY, 
			MPI_INFO_NULL, &fh);
	

// fh, disp - смещение, etype - элементарный тип данных, 
// filetype -  тип файла, datarep - представление данных 
// info - информационнный объект	
	MPI_File_set_view(fh, 0, MPI_CHAR, MPI_CHAR, "native", MPI_INFO_NULL);

	int sum = 0, num;
	MPI_Status status;
	char buf[BUFSIZE];
	do{
// дескриптор, начальный адрес буфера, количество элементов, тип данных, объект состояния
		MPI_File_read(fh, buf, BUFSIZE, MPI_CHAR, &status);
		MPI_Get_count(&status, MPI_CHAR, &num);
	
		std::cout << "buf= " << buf << std::endl;
	
		sum += num;
	} while(num >= BUFSIZE);
	

	MPI_File_close(&fh);

	std::cout << "Size read symbol " << sum << std::endl;

	if (argc == 2) {
		std::string first_arge = argv[1];
		if (first_arge == "d") {
			std::cout << "Delete file.txt" << std::endl;
			MPI_File_delete(fileName.c_str(), MPI_INFO_NULL);
		}
	} 
	
	MPI_Finalize();
}


// MPI_File_write
// fh, buf, count, datatype, status

// MPI_File_seek
// fh, offset, whehence
// дескриптор, смещение, тип обновления
// изменение индивидуального файлового указателя относительно аргумента whence