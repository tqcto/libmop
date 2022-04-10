/*
#include <cuda_runtime.h>
#include "vector_types.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
*/
#include <stdio.h>
#include <math.h>

#include <iostream>

#include "cuda.cuh"
#include "math_constants.h"

__global__ void gpu_func(float* dx, float* dy) {

	int i = blockIdx.x * blockDim.x + threadIdx.x;
	dy[i] = sin(dx[i]) * sin(dx[i]) + cos(dx[i]) * cos(dx[i]);

}

__host__ void test(void) {

    int N = 1000000;
    float* host_x, * host_y, * dev_x, * dev_y;
    host_x = (float*)malloc(N * sizeof(float));
    host_y = (float*)malloc(N * sizeof(float));

    for (int i = 0; i < N; i++) {
        host_x[i] = rand();
    }

    cudaMalloc(&dev_x, N * sizeof(float));
    cudaMalloc(&dev_y, N * sizeof(float));

    cudaMemcpy(dev_x, host_x, N * sizeof(float), cudaMemcpyHostToDevice);

    gpu_func << <(N + 255) / 256, 256 >> > (dev_x, dev_y);

    cudaMemcpy(host_y, dev_y, N * sizeof(float), cudaMemcpyDeviceToHost);

    float sum = 0.0f;
    for (int j = 0; j < N; j++) {
        sum += host_y[j];
    }
    std::cout << sum << std::endl;

}
