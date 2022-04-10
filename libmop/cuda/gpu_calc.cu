#include "../include/gpu_calc.cuh"

DLL_EXPORT __host__ void initialize(unsigned char** data, int w, int h, int c) {

	unsigned char* dst;

	int size = w * h * c;

	cudaMalloc((void**)&dst, sizeof(unsigned char) * size);

	data_init_gpu << <size, c >> > (dst);

	cudaMemcpy(data, dst, sizeof(unsigned char) * size, cudaMemcpyDeviceToHost);

}

__global__ void data_init_gpu(unsigned char* dst) {

	int ID = blockIdx.x * blockDim.x + threadIdx.x;
	dst[ID] = 0x00;

}