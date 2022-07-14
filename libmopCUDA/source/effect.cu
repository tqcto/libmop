#include "../include/effect.cuh"

#include <stdio.h>

#include <cuda_runtime.h>
#include <device_launch_parameters.h>

#include <curand.h>
#include <curand_kernel.h>

using namespace mop;

namespace mop_cuda {

	__host__ __device__ __forceinline__ int divUp(int total, int grain) {
		return (total + grain - 1) / grain;
	}

	__device__ void random(int* data, int max, int seed) {

		curandState_t state;
		curand_init(seed, 0, 0, &state);
		*data = curand(&state) % max;

	}

	__global__ void NoiseDevice(uchar* src, uchar* dst, int w, int h, int c) {

		int x = blockIdx.x * blockDim.x + threadIdx.x;
		int y = blockIdx.y * blockDim.y + threadIdx.y;



	}

	DLL_EXPORT void Noise(matrix* src, matrix* dst, int percent, int seed) {


		int w = src->width(),
			h = src->height(),
			c = src->channel();

		uchar *input, *output;
		int size = sizeof(uchar) * w * h * c;

		cudaMalloc((void**)&input, size);
		cudaMalloc((void**)&output, size);

		cudaMemcpy(input, src->data, size, cudaMemcpyHostToDevice);

		*dst = matrix(w, h, c);

		const dim3 block(w / 125, h / 125);
		const dim3 grid(divUp(w, block.x), divUp(h, block.y));

		NoiseDevice << <grid, block >> > (input, output, w, h, c);

		cudaMemcpy(
			(void*)dst->data,
			(void*)output,
			size,
			cudaMemcpyDeviceToHost
		);

		cudaFree(input);
		cudaFree(output);

	}

}
