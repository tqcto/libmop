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

	value *= (0 > value ? -1 : 1);

	if (max <= value) {
		value -= max;
		value = max - mirror(value, max);
	}

	return value;

}
