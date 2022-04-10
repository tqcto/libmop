#pragma once
#include <cuda_runtime.h>
#include "vector_types.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include "deflate/define.h"

DLL_EXPORT __host__ void initialize(unsigned char** data, int w, int h, int c);
__global__ void data_init_gpu(unsigned char* dst);
