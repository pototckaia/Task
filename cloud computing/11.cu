// Сложение векторов и сравнение с количеством тредов в памяти

#include <iostream>

#include <cuda.h>

using namespace std;

__global__ void add(float *a, float *b, float *c)
{
	if (a[threadIdx.x] + b[threadIdx.x] < 10)
		c[threadIdx.x] = a[threadIdx.x] + b[threadIdx.x];
	else
		c[threadIdx.x] = 10;
}

//Количество суммирований и сравнений
#define N 64

int main(void) 
{
	float *a, *b, *c; // host копии a, b, c
	float *dev_a, *dev_b, *dev_c; // device копии a, b, c
	int size = N * sizeof(float);

	//выделяем память для device копий a, b, c
	cudaMalloc((void**)&dev_a, size);
	cudaMalloc((void**)&dev_b, size);
	cudaMalloc((void**)&dev_c, size);
	a = (float*) malloc(size);
	b = (float*) malloc(size);
	c = (float*) malloc(size);
	for (int i = 0; i < N; ++i)
		a[i] = (float)rand() / (float)RAND_MAX;
	for (int i = 0; i < N; ++i)
		b[i] = (float)rand() / (float)RAND_MAX;

	// копируем ввод на device
	cudaMemcpy(dev_a, a, size, cudaMemcpyHostToDevice);
	cudaMemcpy(dev_b, b, size, cudaMemcpyHostToDevice);
	// launch add() kernel with N parallel blocks
	//Использование N тредов и 1 блока
	add<<< 1, N >>>(dev_a, dev_b, dev_c);
	//Использование N блоков И 1 тре-
	// Если мы будем использовать N блоков и 1 тред 
	// add<<< N, 1 >>>(dev_a, dev_b, dev_c);
	// то каждый результат с будет равным нулю, кроме первого
	//add<<< N, 1 >>>(dev_a, dev_b, dev_c);

	// копируем результат работы device обратно на host – копию c
	cudaMemcpy(c, dev_c, size, cudaMemcpyDeviceToHost);

	for(int i = 0; i < N; ++i)
		cout<<"c[" << i << "]=" << c[i] << endl;

	free(a); free(b); free(c);
	cudaFree(dev_a);
	cudaFree(dev_b);
	cudaFree(dev_c);

	return 0;
}