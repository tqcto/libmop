#include "../include/gpu_calc.cuh"

DLL_EXPORT __host__ void initialize_uchar(unsigned char** data, int w, int h, int c) {

	unsigned char* dst;

	int size = sizeof(unsigned char) * w * h * c;

	cudaMalloc((void**)&dst, size);

	data_init_gpu_uchar << <w * h, c >> > (dst);

	cudaMemcpy(*data, dst, size, cudaMemcpyDeviceToHost);

}
DLL_EXPORT __host__ void initialize_ushort(unsigned short** data, int w, int h, int c) {

	unsigned short* dst;

	int size = sizeof(unsigned short) * w * h * c;

	cudaMalloc((void**)&dst, size);

	data_init_gpu_ushort << <w * h, c >> > (dst);

	cudaMemcpy(*data, dst, size, cudaMemcpyDeviceToHost);

}
DLL_EXPORT __host__ void initialize_float(float** data, int w, int h, int c) {

	float* dst;

	int size = sizeof(float) * w * h * c;

	cudaMalloc((void**)&dst, size);

	data_init_gpu_float << <w * h, c >> > (dst);

	cudaMemcpy(*data, dst, size, cudaMemcpyDeviceToHost);

}

__global__ void data_init_gpu_uchar(unsigned char* dst) {

	int ID = blockIdx.x * blockDim.x + threadIdx.x;
	dst[ID] = 100;

}
__global__ void data_init_gpu_ushort(unsigned short* dst) {

	int ID = blockIdx.x * blockDim.x + threadIdx.x;
	dst[ID] = 0x8000;

}
__global__ void data_init_gpu_float(float* dst) {

	int ID = blockIdx.x * blockDim.x + threadIdx.x;
	dst[ID] = 200.0f;

}
