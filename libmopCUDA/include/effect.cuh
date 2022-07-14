#pragma once
#include "libmop_cuda.h"

namespace mop_cuda {

	DLL_EXPORT void Noise(matrix* src, matrix* dst, int percent, int seed = 0);

}
