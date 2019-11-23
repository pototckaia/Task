// Скалярное произведение с использованием shared-памяти 

#define N 512

__global__ void dot(int *a, int *b, int *c) 
{
	__shared__ int temp[N];
	temp[threadIdx.x] = a[threadIdx.x] * b[threadIdx.x];
	__syncthreads();
	if (0 == threadIdx.x) 
	{
		int sum = 0;
		for(int i = 0; i < N; ++i)
			sum += temp[i];
		*c = sum;
	}
}

int main(void) 
{
	int *a, *b, *c;
	int *dev_a, *dev_b, *dev_c;
	
	int size = N * sizeof( int );
	cudaMalloc( (void**)&dev_a, size );
	cudaMalloc( (void**)&dev_b, size );
	cudaMalloc( (void**)&dev_c, sizeof( int ) );

	a = (int *)malloc( size );
	b = (int *)malloc( size );
	c = (int *)malloc( sizeof( int ) );

	random_ints( a, N );
	random_ints( b, N );

	// копируем ввод на device
	cudaMemcpy( dev_a, a, size, cudaMemcpyHostToDevice );
	cudaMemcpy( dev_b, b, size, cudaMemcpyHostToDevice );

	//запускаем на выполнение dot() kernel с 1 блоком и N тредами
	dot<<< 1, N >>>( dev_a, dev_b, dev_c );

	//копируем результат работы device на host копией c
	cudaMemcpy( c, dev_c, sizeof( int ) , cudaMemcpyDeviceToHost );

	free( a ); free( b ); free( c );
	cudaFree( dev_a ); cudaFree( dev_b ); cudaFree( dev_c );

	return 0;
}