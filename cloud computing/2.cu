#include<iostream>

__global__ void add(int *a, int *b, int *c )
{
	*c = *a+*b;
}

int main(void )
{
	int a, b, c;
	int *dev_a, *dev_b, *dev_c;
	int size = sizeof( int );
	cudaMalloc( (void**)&dev_a, size );
	cudaMalloc( (void**)&dev_b, size );
	cudaMalloc( (void**)&dev_c, size );
	a = 5;
	b = 10;
	cudaMemcpy(dev_a, &a,size,cudaMemcpyHostToDevice);
	cudaMemcpy(dev_b, &b, size, cudaMemcpyHostToDevice);
	
	add<<<1,1>>>(dev_a, dev_b, dev_c);
	cudaMemcpy(&c,dev_c,size,cudaMemcpyDeviceToHost);
	cudaFree(dev_a);
	cudaFree(dev_b);
	cudaFree(dev_c);
	std::cout<<a<<" "<<b<<" "<<c<<std::endl;
	return 0;
}
