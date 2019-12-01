// Перемножение двух матриц

#include <stdio.h>

#define BLOCK_SIZE 16 // submatrix size
#define N 1024 // matrix size is N*N

__global__ void matMult (float *a, float *b, int n, float *c)
{
	int bx = blockIdx.x;
	// block index
	int by = blockIdx.y;
	int tx = threadIdx.x;
	int ty = threadIdx.y;
	float sum = 0.0f;
	// computed subelement
	// a [i][0]
	int ia = n * BLOCK_SIZE * by + n * ty;
	int ib = BLOCK_SIZE * bx + tx;
	// Multiply the two matrices together;
	for (int k = 0; k < n; ++k)
		sum += a[ia + k] * b[ib + k*n];
	// Write the block sub-matrix to global memory;
	// each thread writes one element
	int ic = n * BLOCK_SIZE * by + BLOCK_SIZE * bx;

	c[ic + n * ty + tx] = sum;
}

int main (int argc, char *argv[])
{
	int numBytes = N * N * sizeof(float);
	
	// выделение памяти на хосте
	float *a = new float [N*N];
	float *b = new float [N*N];
	float *c = new float [N*N];
	
	for (int i = 0; i < N; ++i)
		for ( int j = 0; j < N; ++j)
		{
			int k = N*i + j;
			a[k] = 0.0f;
			b[k] = 1.0f;
		}
	
	// выделение памяти на девайсе
	float *adev = NULL;
	float *bdev = NULL;
	float *cdev = NULL;
	cudaMalloc((void**)&adev, numBytes);
	cudaMalloc((void**)&cdev, numBytes);
	cudaMalloc((void**)&bdev, numBytes);

	// Установка конфигурации запуска ядра
	dim3 threads(BLOCK_SIZE, BLOCK_SIZE);
	dim3 blocks(N / threads.x, N / threads.y);
	
	// Создание обработчика событий CUDA
	cudaEvent_t start, stop;
	float gpuTime = 0.0f;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);

	// асинхронно выдаваем работу на GPU (все в поток 0)
	cudaEventRecord(start, 0 );
	cudaMemcpy(adev, a, numBytes, cudaMemcpyHostToDevice);
	cudaMemcpy(bdev, b, numBytes, cudaMemcpyHostToDevice);
	matMult<<<blocks, threads>>>(adev, bdev, N, cdev);
	cudaMemcpy(c, cdev, numBytes, cudaMemcpyDeviceToHost );
	cudaEventRecord(stop, 0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&gpuTime, start, stop);
	
	// Печатаем время работы на GPU и CPU
	printf("time spent executing by the GPU: %.2f millseconds\n", gpuTime);
	
	// Освобождение ресурсов
	cudaEventDestroy (start); cudaEventDestroy(stop);
	cudaFree(adev); cudaFree(bdev); cudaFree(cdev);

	delete a; delete b; delete c;
	
	return 0;
}