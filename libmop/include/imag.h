#pragma once
#include "deflate/define.h"

typedef struct _complex {

	int r;
	int i;

	_complex(void) {
		r = 0;
		i = 0;
	}
	_complex(int real, int imag) {
		r = real;
		i = imag;
	}

}complex;
