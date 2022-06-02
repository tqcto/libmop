#include "..\include\matrix.hpp"

#include "..\include\reader.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>

namespace mop {

	DLL_EXPORT matrix::matrix(const char* filename) {

		if (decodeJPG(&this->bmp, filename)) {

			this->bmp		= BITMAPDATA_t();
			this->_empty	= true;

			return;

		}

		this->_empty = false;

	}

	DLL_EXPORT matrix::~matrix(void) {

		freeBMP(&this->bmp);

	}

	DLL_EXPORT int matrix::encode(const char* filename, int quality) {

		return encodeJPG(&this->bmp, filename, quality);

	}

	DLL_EXPORT inline int matrix::empty(void) const {
		return this->_empty;
	}

}
