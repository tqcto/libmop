#include "deflate/deflate.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace mop {

	DLL_EXPORT int struct_malloc(void** ptr, int size) {

		*ptr = (void**)malloc(size);

		return !*ptr;

	}

	DLL_EXPORT void struct_cpy(void** src, void** dst, int size) {

		memcpy(*dst, *src, size);

	}

	DLL_EXPORT void struct_free(void** ptr) {

		if (*ptr != NULL) {
			free(*ptr);
		}

	}

}
