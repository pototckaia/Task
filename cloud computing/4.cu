// Сложение двух чисел с одним блоком и N-тредов

__global__ void add(int *a, int *b, int *c) 
{
	c[threadIdx.x] = a[threadIdx.x] + b[threadIdx.x];
	// blockIdx.x blockIdx.x blockIdx.x
}

#define N 512

int main(void) 
{
	//host копии a, b, c
	int *a, *b, *c; 
	//device копии of a, b, c
	int *dev_a, *dev_b, *dev_c;
	
	int size = N * sizeof(int);
	//выделяем память для копий a, b, c
	cudaMalloc((void**)&dev_a, size);
	cudaMalloc((void**)&dev_b, size);
	cudaMalloc((void**)&dev_c, size);

	a = (int*)malloc(size);
	b = (int*)malloc(size);
	c = (int*)malloc(size);
	random_ints(a, N);
	random_ints(b, N);

	// копируем ввод device
	cudaMemcpy(dev_a, a, size, cudaMemcpyHostToDevice);
	cudaMemcpy(dev_b, b, size, cudaMemcpyHostToDevice);
	
	// запускаем на выполнение add() kernel с N тредами в блоке
	add<<< 1, N >>>(dev_a, dev_b, dev_c);

	// копируем результат работы device обратно на host (копия c)
	cudaMemcpy(c, dev_c, size, cudaMemcpyDeviceToHost);

	free(a); free(b); free(c);
	cudaFree(dev_a); cudaFree(dev_b); cudaFree(dev_c);

	return 0;
}