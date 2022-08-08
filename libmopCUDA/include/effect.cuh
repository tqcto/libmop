#pragma once
#include "libmop_cuda.h"

namespace mop_cuda {

	DLL_EXPORT void Blur(matrix* src, matrix* dst, int amount);
	DLL_EXPORT void Blur(uchar** src, uchar** dst, int w, int h, int c, int amount);
	DLL_EXPORT void Test();

}
