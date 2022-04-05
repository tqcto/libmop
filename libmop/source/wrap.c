#include "../include/wrap.h"

DLL_EXPORT inline int mirror(int value, int max) {

	value *= (0 > value ? -1 : 1);

	if (max <= value) {
		value -= max;
		value = max - mirror(value, max);
	}

	return value;

}
