// Сложение двух чисел с использованием N-блоков по одному треду

__global__ void add(int *a, int *b, int *c) 
{
	c[blockIdx.x] = a[blockIdx.x] + b[blockIdx.x];
}

#define N 512

int main(void) 
{
	 // host копии a, b, c
	int *a, *b, *c;
	// device копии a, b, c
	int *dev_a, *dev_b, *dev_c; 
	
	int size = N * sizeof(int);

	//выделяем память для device копий a, b, c
	cudaMalloc((void**)&dev_a, size);
	cudaMalloc((void**)&dev_b, size);
	cudaMalloc((void**)&dev_c, size);

	a = (int*)malloc(size);
	b = (int*)malloc(size);
	c = (int*)malloc(size);

	random_ints(a, N);
	random_ints(b, N);

	// копируем ввод на device
	cudaMemcpy(dev_a, a, size, cudaMemcpyHostToDevice);
	cudaMemcpy(dev_b, b, size, cudaMemcpyHostToDevice);
	
	// launch add() kernel with N parallel blocks
	add<<< N, 1 >>>(dev_a, dev_b, dev_c);

	// копируем результат работы device обратно на host – копию c
	cudaMemcpy(c, dev_c, size, cudaMemcpyDeviceToHost);

	free(a); free(b); free(c);
	cudaFree(dev_a); cudaFree(dev_b); cudaFree(dev_c);
	
	return 0;
}