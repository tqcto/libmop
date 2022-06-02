#pragma once
#include <cuda_runtime.h>
#include "vector_types.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include "deflate/define.h"

DLL_EXPORT __device__ unsigned long xor128(void);
DLL_EXPORT __device__ long Xorshift128(long l, long h);
DLL_EXPORT __device__ float XorFrand(float l, float h);
