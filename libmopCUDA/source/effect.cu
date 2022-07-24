#include "../include/effect.cuh"

#include <stdio.h>

#include <cuda_runtime.h>
#include <device_launch_parameters.h>

#include <curand.h>
#include <curand_kernel.h>

#define N 1 << 20

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
	__device__ void random(double* data, double max, int seed) {

		curandState_t state;
		curand_init(seed, 0, 0, &state);
		*data = (double)(curand(&state) % (int)(max * 10)) / 10.0;

	}

	__global__ void BlurDevice(uchar* src, uchar* dst, int w, int h, int c, int m, int n) {

		int x = blockIdx.x * blockDim.x + threadIdx.x;
		int y = blockIdx.y * blockDim.y + threadIdx.y;

		int data = 0,
			num = 1;

		for (int cc = 0; cc < c; cc++) {

			data = 0;
			num = 1;

			for (int yy = y - m; yy <= y + n; yy++) {
				if (0 <= yy && yy < h) {
					for (int xx = x - m; xx <= x + n; xx++) {
						if (0 <= xx && xx < w) {
							data += src[(xx + yy * w) * c + cc];
							num++;
						}
					}
				}
			}

			dst[(x + y * w) * c + cc] = data / num;

		}

	}

	DLL_EXPORT void Blur(matrix* src, matrix* dst, int amount) {

		int w = src->width(),
			h = src->height(),
			c = src->channel();

		int m = 0, n = 0;
		if ((amount * 5) % 10 != 0) {
			m = amount / 2;
			n = m;
		}
		else {
			m = (double)amount / 2.0;
			n = m - 1;
		}

		uchar* input, * output;
		int size = sizeof(uchar) * w * h * c;

		cudaMalloc((void**)&input, size);
		cudaMalloc((void**)&output, size);

		cudaMemcpy(input, src->data, size, cudaMemcpyHostToDevice);

		*dst = matrix(w, h, c);

		///*
		const dim3 block(w / 125, h / 125);
		const dim3 grid(divUp(w, block.x), divUp(h, block.y));
		//*/
		/*
		int nw = w * 2048;
		int nh = h * 2048;
		const dim3 block(w, h);
		const dim3 grid(nw / block.x, nh / block.y);
		*/
		/*
		const dim3 block(1, 1);
		const dim3 grid(w, h);
		*/

		BlurDevice << <grid, block >> > (input, output, w, h, c, m, n);

		cudaMemcpy(
			dst->data,
			output,
			size,
			cudaMemcpyDeviceToHost
		);

		cudaFree(input);
		cudaFree(output);

	}

	__global__ void Test_gpu(int* src, int* dst, int* grid, int* block, int* thread) {

		/*
		* blockIdx	= block index
		* blockDim	= *grid index* or *block size*
		* threadIdx	= thread index
		*/
		int index = blockIdx.x * blockDim.x + threadIdx.x;
		dst[index] = src[4 - index];

		grid[index] = blockDim.x;
		block[index] = blockIdx.x;
		thread[index] = threadIdx.x;

	}

	DLL_EXPORT void Test() {

		int source[5] = { 0, 1, 2, 3, 4 };
		int grid[5], block[5], thread[5];

		int *src, *dst, *ggrid, * gblock, *gthread;

		cudaMalloc((void**)&src, sizeof(int) * 5);
		cudaMalloc((void**)&dst, sizeof(int) * 5);

		cudaMalloc((void**)&ggrid,		sizeof(int) * 5);
		cudaMalloc((void**)&gblock,		sizeof(int) * 5);
		cudaMalloc((void**)&gthread,	sizeof(int) * 5);

		const dim3 _block(5);
		const dim3 _grid(N / _block.x);

		cudaMemcpy(src, source, sizeof(int) * 5, cudaMemcpyHostToDevice);

		Test_gpu << <_grid, _block >> > (src, dst, ggrid, gblock, gthread);

		cudaMemcpy(source, dst, sizeof(int) * 5, cudaMemcpyDeviceToHost);

		cudaMemcpy(block,	gblock,		sizeof(int) * 5, cudaMemcpyDeviceToHost);
		cudaMemcpy(grid,	ggrid,		sizeof(int) * 5, cudaMemcpyDeviceToHost);
		cudaMemcpy(thread,	gthread,	sizeof(int) * 5, cudaMemcpyDeviceToHost);

		cudaFree(src);
		cudaFree(dst);

		cudaFree(ggrid);
		cudaFree(gblock);
		cudaFree(gthread);

		printf("[source]\n");
		for (int i = 0; i < 5; i++) {
			printf("%d ", source[i]);
		}
		printf("\n");

		printf("\n[grid]");
		for (int i = 0; i < 5; i++) {
			printf(" %d", grid[i]);
		}
		printf("\n[block]");
		for (int i = 0; i < 5; i++) {
			printf(" %d", block[i]);
		}
		printf("\n[thread]");
		for (int i = 0; i < 5; i++) {
			printf(" %d", thread[i]);
		}
		printf("\n");

	}

}
