#include <iostream>
#include <cmath>
/*
Ryan McDonald
CSUF Spring 2021
CPSC 479 - Dr. Bein
*/

__global__ 
void squareMatrix(int* matrix, int* result, int N) {
	int row = blockIdx.y * blockDim.y + threadIdx.y;
	int col = blockIdx.x * blockDim.x + threadIdx.x;
	int sum = 0;

	if (row < N && col < N)
	{
		for (int i = 0; i < N; i++)
		{
			sum += matrix[row * N + i] * matrix[i * N + col];
		}
		result[row * N + col] = sum;
	}
}

__global__ void findLowestVal(int* matrix, int* lowestVal, int N) {

	__shared__ int c[256];

	int index = blockIdx.x * blockDim.x + threadIdx.x;
	int stride = blockDim.x * gridDim.x;
	int offset = 0;
	int temporary = matrix[0];

	while (index + offset < N)
	{
		temporary = min(temporary, matrix[index + offset]);
		offset += stride;
	}
	c[threadIdx.x] = temporary;

	 int u = blockDim.x / 2;
	while (u != 0) {
		if (threadIdx.x < u) {
			c[threadIdx.x] = min(c[threadIdx.x], c[threadIdx.x + u]);
		}
		__syncthreads();
		u = u/2;
	}

	if (threadIdx.x == 0)
	{
		*lowestVal = min(*lowestVal, c[0]);
	}

}

//Function to fill matrix with random values
void fill_matrix(int* matrix, int N) {
	for (int i = 0; i < N; i++)
	{
		matrix[i] = rand() % 100;
	}
}

int main(int argc, char* argv[]) {
	//Set size of matrix [16x16] Square Matrix
	int N = 16 * 16;
	int* myMatrix;
	int* myMatrixSquared;
	int* lowestVal;

	// Allocate Unified Memory – accessible from CPU or GPU
	cudaMallocManaged(&lowestVal, sizeof(int));
	cudaMallocManaged(&myMatrix, N * sizeof(int));
	cudaMallocManaged(&myMatrixSquared, N * sizeof(int));

	//Populate Matrix with random values
	fill_matrix(myMatrix, N);

	int blockSize = 16;
	int numBlocks = (N + blockSize - 1) / blockSize;

	findLowestVal <<<numBlocks, blockSize >>> (myMatrix, lowestVal, N);

	dim3 threadsPerBlock(blockSize, blockSize);
	dim3 blocksPerGrid(numBlocks, numBlocks);

	squareMatrix<<<blocksPerGrid, threadsPerBlock >>> (myMatrix, myMatrixSquared, N);

	//Waits for GPU to finish before accessing data on the host
	cudaDeviceSynchronize();

	//Free memory
	cudaFree(lowestVal);
	cudaFree(myMatrix);
	cudaFree(myMatrixSquared);

	return 0;
}