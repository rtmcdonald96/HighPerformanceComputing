#include <iostream>
/*
Ryan McDonald
CSUF Spring 2021
CPSC 479 - Dr. Bein
*/
__global__
void setVal(int n, int* x) {
	int index = blockIdx.x * blockDim.x + threadIdx.x;
	int stride = blockDim.x * gridDim.x;
	for (int i = index; i < n; i += stride)
		x[i]=0;
}

__global__
void addVal(int n, int* x){

	int index = blockIdx.x * blockDim.x + threadIdx.x;
	int stride = blockDim.x * gridDim.x;
	for (int i = index; i < n; i += stride)
		x[i] +=i;
}

int main(int argc, char* argv[])
{
	//Set size of array
	int N = 1024;
	int* x;

	// Allocate Unified Memory – accessible from CPU or GPU
	cudaMallocManaged(&x, N * sizeof(int));

	//Run Kernel on 1024 elements on the GPU
	int blockSize = 256;
	int numBlocks = (N + blockSize - 1) / blockSize;
	
	setVal<<<numBlocks, blockSize>>>(N, x);	
	addVal<<<numBlocks, blockSize>>>(N, x);

	//Waits for GPU to finish before accessing data on the host
	cudaDeviceSynchronize();

	//Optional code to show value at each index. 
	//Used to confirm setVal and addVal function worked.
	/*
	for (int i=0; i<N; i++)
	{
	std::cout << "Index x[" << i << "] has value: "<< x[i] << std::endl;
	}
	*/

	//Free memory
	cudaFree(x);

	return 0;
}
