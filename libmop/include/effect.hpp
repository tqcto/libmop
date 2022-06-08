#pragma once
#include "libmop.h"

namespace mop {

	DLL_EXPORT void Noise(matrix* src, int percent, int seed = 0);

	DLL_EXPORT hsv rgb2hsv(rgb c);
	DLL_EXPORT rgb hsv2rgb(hsv c);

}
