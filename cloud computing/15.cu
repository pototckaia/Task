#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/* 
Каждый поток получает ровно одно значение 
в несортированном массиве 
*/
#define THREADS 512 // 2^9
#define BLOCKS 32768 // 2^15
#define NUM_VALS (THREADS*BLOCKS)

/* 
Функция печати результата выполнения программы
*/
void print_elapsed(clock_t start, clock_t stop)
{
	double elapsed = ((double) (stop - start)) / CLOCKS_PER_SEC;
	printf("Elapsed time: %.3fs\n", elapsed);
}

/* Генерация случайных чисел массива */
float random_float()
{
	return (float)rand()/(float)RAND_MAX;
}

/* Печать массива */
void array_print(float *arr [], int length)
{
	for (int i = 0; i < length; ++i) {
		printf("%1.3f", arr[i]);
	}
	printf("\n");
}

/* Заполнение массива */
void array_fill(float *arr, int length)
{
	srand(time(NULL));
	for (int i = 0; i < length; ++i) {
		arr[i] = random_float();
	}
}

__global__ void bitonic_sort_step(float *dev_values, int j, int k)
{
	/* Сортировка i и ixj */
	unsigned int i = threadIdx.x + blockDim.x * blockIdx.x;
	unsigned int ixj = i^j;

	/* Нити с наименьшими идентификаторами сортируют массив. */
	if (ixj > i) 
	{
		if (i & k == 0) 
		{
		/* Сортировка по возрастанию */
			if (dev_values[i] > dev_values[ixj]) 
			{
			/* обмен(i,ixj) */
				float temp = dev_values[i];
				dev_values[i] = dev_values[ixj];
				dev_values[ixj] = temp;
			}
		}
		if (i & k != 0) 
		{
			/* Сортировка по убыванию */
			if (dev_values[i] < dev_values[ixj]) 
			{
				/* обмен(i,ixj); */
				float temp = dev_values[i];
				dev_values[i] = dev_values[ixj];
				dev_values[ixj] = temp;
			}
		}
	}
}

/**
* Битонная сортировка на CUDA.
*/
void bitonic_sort(float *values)
{
	size_t size = NUM_VALS * sizeof(float);
	float *dev_values;
	cudaMalloc((void**)&dev_values, size);
	cudaMemcpy(dev_values, values, size, cudaMemcpyHostToDevice);

	dim3 blocks(BLOCKS, 1); /* Количество блоков */
	dim3 threads(THREADS,1); /* Количество тредов */

	/* Основной шаг выполнения сортировки */
	for (int k = 2; k <= NUM_VALS; k <<= 1) 
	{
		/* Второстепенный шаг выполнения сортировки */
		for (int j = k>>1; j > 0; j = j>>1) 
		{
			bitonic_sort_step<<<blocks, threads>>>(dev_values, j, k);
		}
	}
	cudaMemcpy(values, dev_values, size, cudaMemcpyDeviceToHost);
	cudaFree(dev_values);
}

int main(void)
{
	clock_t start, stop;
	float *values = (float*) malloc(NUM_VALS * sizeof(float));
	array_fill(values, NUM_VALS);
	start = clock();
	bitonic_sort(values);
	stop = clock();
	print_elapsed(start, stop);
}