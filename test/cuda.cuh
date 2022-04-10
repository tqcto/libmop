#pragma once

#include <cuda_runtime.h>
#include "vector_types.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

__global__ void gpu_func(float* dx, float* dy);
__host__ void test(void);