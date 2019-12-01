// Генерация псевдослучайных чисел с использованием CuRand

#include <stdio.h>
#include <curand.h>
#include <curand_kernel.h>

#define MAX 100

/*
эта функция ядра GPU вычисляет случайное число 
и сохраняет его в памяти
*/
__global__ void random(unsigned int seed, int *result) 
{
	/* 
	Библиотека случайных чисел CUDA использует curandState_t 
	для отслеживания начального значения
	мы будем хранить случайное состояние для каждого потока
	*/
	curandState_t state;
	/* инициализация состояния*/
	/* seed контролирует последовательность значений, которые
	генерируются*/
	/* порядковый номер важен только с несколькими ядрами*/
	curand_init(seed, 0, 0, &state);

	/* curand работает как rand – 
	за исключением того, что он принимает состояние как параметр*/
	*result = curand(&state) % MAX;
}

int main() 
{
	/* выделить память int на GPU*/
	int *gpu_x;
	cudaMalloc((void**) &gpu_x, sizeof(int));

	/* вызывать GPU для инициализации всех случайных состояний*/
	random<<<1, 1>>>(time(NULL), gpu_x);
	/* скопировать случайное число на CPU*/

	int x;
	cudaMemcpy(&x, gpu_x, sizeof(int), cudaMemcpyDeviceToHost);

	printf("Random number = %d.\n", x);

	/* освобождение памяти */
	cudaFree(gpu_x);

	return 0;
}