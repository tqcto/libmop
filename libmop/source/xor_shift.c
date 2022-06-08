#include "..\include\xor_shift.h"

static unsigned int seed128[4];

DLL_EXPORT unsigned int xorShift(void) {

	unsigned int t = (seed128[0] ^ (seed128[0] << 11));

	seed128[0] = seed128[1];
	seed128[1] = seed128[2];
	seed128[2] = seed128[3];

	unsigned int ret = (seed128[3] = (seed128[3] ^ (seed128[3] >> 19)) ^ (t ^ (t >> 8)));
	ret = (ret >> 16) & 0x7FFF;

	return ret;

}

DLL_EXPORT double xorShiftDouble(void) {

	unsigned int t = (seed128[0] ^ (seed128[0] << 11));

	seed128[0] = seed128[1];
	seed128[1] = seed128[2];
	seed128[2] = seed128[3];

	unsigned int ret = (seed128[3] = (seed128[3] ^ (seed128[3] >> 19)) ^ (t ^ (t >> 8)));
	ret = ret & 0x7FFFFFFF;

	return (double)ret / 0x7FFFFFFF;

}

DLL_EXPORT void init_xorShift(unsigned int s) {

	unsigned int ss = s + 100;
	for (unsigned int i = 1; i <= 4; i++) {
		seed128[i - 1] = ss = 1812433253U * (ss ^ (ss >> 30)) + i;
	}

}
