// Сложение двух векторов 

#include <cstdlib>
#include <iostream>
#include <cuda_runtime.h>

using namespace std;

__global__ 
void vecAdd_kernel(const float *a, const float *b, float *result, int n) 
{
	// обозначающую размерность блоков и грида - одномерная
	int i = blockIdx.x * blockDim.x + threadIdx.x;
	if (i < n)
		result[i] = a[i] + b[i];
}

int main() 
{	
	int n = 100;
	float *a = new float[n], *a_gpu;
	cudaMalloc((void**)&a_gpu, n*sizeof(float));

	float *b = new float[n], *b_gpu;
	cudaMalloc((void**)&b_gpu, n*sizeof(float));

	float *result = new float[n], *result_gpu;
	cudaMalloc((void**)&result_gpu, n*sizeof(float));

	for (size_t i = 0; i < n; ++i)
		a[i] = b[i] = i;

	// Далее происходит копирование данных из памяти CPU в память GPU
	cudaMemcpy(a_gpu, a, n*sizeof(float), cudaMemcpyHostToDevice);
	cudaMemcpy(b_gpu, b, n*sizeof(float), cudaMemcpyHostToDevice);

	const int block_size = 256;
	int num_blockds = (n + block_size - 1) / block_size;

	vecAdd_kernel<<< num_blockds, block_size >>> (a_gpu, b_gpu, result_gpu, n);

	cudaMemcpy(result, result_gpu, n*sizeof(float), cudaMemcpyDeviceToHost);

	for (size_t x = 0; x < 10; ++x)	
		cout << result[x] << endl;


	delete[] a, delete[] b, delete[] result;
	cudaFree(a_gpu); cudaFree(b_gpu); cudaFree(result_gpu);

	return 0; 
}