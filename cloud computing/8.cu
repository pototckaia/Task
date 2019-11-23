// Увеличение значений элементов в матрице на единицу

#include <stdio.h>

// каждому треду соответствует один тред, блоки и grid одномерны. 
// Ядро (она же функция incKernel) на вход получает только указатель на массив 
// с данными в глобальной памяти. 
// Задача ядра – по threadIdx и blockIdx определить, какой именно элемент 
// соответствует данному треду, и увеличить именно его.
__global__ void incKernel (float *data)
{
	int idx = blockIdx.x * blockDim.x + threadIdx.x;
	data[idx] = data[idx] + 1.0f;
}

int main (int argc, char *argv[])
{
	int n = 16 * 1024 * 1024;
	int numBytes = n * sizeof(float);

	// выделение памяти на хосте
	float *a = new float[n];
	for (sts::size_t i = 0; i < n; ++i)
		a[i] = 0.0f;

	// выделение памяти на девайсе
	float *dev = NULL;
	cudaMalloc ((void**)&dev, numBytes);

	// Устоновка конфигурации запуска ядра
	dim3 threads = dim3(512, 1);
	dim3 blocks = dim3(n / threads.x, 1);

	// создание обработчиков событий cuda
	cudaEvent_t start, stop;
	float gpuTime = 0.0f;

	cudaEventCreate(&start);
	cudaEventCreate(&stop);

	// асинхронно выдаем работу на GPU (все в поток 0)
	cudaEventRecord(start, 0);
	cudaMemcpy(dev, a, numBytes, cudaMemcpyHostToDevice);

	incKernel<<<blocks, threads>>>(dev);

	cudaMemcpy(a, dev, numBytes, cudaMemcpyDeviceToHost);
	cudaEventRecord(stop, 0);

	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&gpuTime, start, stop);

	// Печатаем время работы на CPU и GPU
	printf("time spent executing by the GPU: %.2f millseconds\n", 
			gpuTime);

	// проверка аутпута на корректность
	printf("--------------------------------------------------------------\n");
	for (size_t i = 0; i < n; ++i)
		if (a[i] != 1.0f) 
		{
			printf("Error in pos %d, %f\n", i, a[i]);
			break;
		}


	cudaEventDestroy(start); cudaEventDestroy(stop);
	cudaFree(dev);
	delete a;

	return 0;
}