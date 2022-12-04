#include "wrap.h"

DLL_EXPORT inline int tile(int value, int max) {

	if (max <= value) {
		value -= max;
		value = tile(value, max);
	}
	else if (value < 0) {
		value = max - value * -1;
		value = tile(value, max);
	}

	return value;

}

DLL_EXPORT inline int mirror(int value, int max) {

	int max_1 = max - 1;
	int a = abs(value) / max_1;
	int p = a % 2;

	return p ? max_1 - abs(value) % max_1 : abs(value) % max_1;

}
