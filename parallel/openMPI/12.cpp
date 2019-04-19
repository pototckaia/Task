// MPI. Пользовательские глобальные операции. Пользовательская глобальная функция.

// Разобраться с новыми функциями. Создать свою глобальную функцию поиска максимального элемента,
// сравнить правильность выполнения с операцией MPI_MAX в функции MPI_Reduce().

#include <iostream>	
#include <algorithm>
#include <limits>
#include "mpi.h"

// typedef void MPI_User_function
// (void *invec,  void *inoutvec, int *len, MPI_Datatype *datatype);
void smod5(void *a, void *b, int *l, MPI_Datatype *type) {
	for(int i = 0; i< (*l); ++i)
		((int*)b)[i] = (((int*)a)[i] + ((int*)b)[i]) % 5;
}

void max_double_arr(double *invec, double *inoutvec, int *len, MPI_Datatype *datatype) {
	for (int i = 0; i < (*len); ++i) {
		inoutvec[i] = std::max(invec[i], inoutvec[i]);
	}
}

int main(int argc, char **argv) {
	MPI_Init(&argc, &argv);

	int rank, size, i;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);


	const int n = 100000;
	
	double a[n], b[n], c[n];
	for(int i = 0; i < n; i++) {
		a[i] = i + rank + 1;
		c[i] = b[i] = std::rand()  % 10;
	}

	
	MPI_Op op;
	// Если commute = true, то операция должна быть как коммутативной, так и ассоциативной. 
	// Если commute = false, то порядок операндов фиксирован, операнды располагаются по возрастанию номеров процессов, начиная с нулевого. 
	MPI_Op_create((MPI_User_function *)&max_double_arr, 1, &op);
	
	MPI_Reduce(a, b, n, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
	MPI_Reduce(a, c, n, MPI_DOUBLE, op, 0, MPI_COMM_WORLD);

	MPI_Op_free(&op);
	
	if(rank==0) {
		for (int i = 0; i < n; ++i) {
			if (b[i] != c[i]) {
				std::cout << "Error " << b[i] << " " << c[i] << std::endl;
				break;
			} 
		}
	}
	
	MPI_Finalize();
}