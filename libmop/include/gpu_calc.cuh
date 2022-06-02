#pragma once
#include <cuda_runtime.h>
#include "vector_types.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include "../include/xorshift_rng.cuh"

#include "deflate/define.h"

DLL_EXPORT __host__ void initialize_uchar(unsigned char** data, int w, int h, int c);
DLL_EXPORT __host__ void initialize_ushort(unsigned short** data, int w, int h, int c);
DLL_EXPORT __host__ void initialize_float(float** data, int w, int h, int c);

__global__ void data_init_gpu_uchar(unsigned char* dst);
__global__ void data_init_gpu_ushort(unsigned short* dst);
__global__ void data_init_gpu_float(float* dst);
