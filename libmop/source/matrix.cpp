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
	DLL_EXPORT matrix::matrix(int width, int height, color_number channels) {

		if (!this->_empty) {
			data_free();
			this->_empty = true;
		}

		if (data_malloc(width, height, channels)) {
			return;
		}

		this->bmp.width		= width;
		this->bmp.height	= height;
		this->bmp.ch		= channels;

	}

	DLL_EXPORT matrix::~matrix(void) {

		data_free();

	}

	DLL_EXPORT int matrix::data_malloc(int width, int height, color_number channels) {

		if (!this->_empty) {
			data_free();
		}

		this->bmp.data = (uchar*)malloc(sizeof(uchar) * width * height * channels);
		if (this->bmp.data == NULL) {
			this->_empty = true;
			printf("data malloc error.\n");
			return -1;
		}

		this->_empty = false;

		return 0;

	}
	DLL_EXPORT void matrix::data_free(void) {

		freeBMP(&this->bmp);
		this->_empty = true;

	}

	DLL_EXPORT uchar* matrix::ac(int x, int y, int c) {

		return &this->bmp.data[this->bmp.ch * (x + y * this->bmp.width) + c];

	}

	DLL_EXPORT int matrix::encode(const char* filename, int quality) {

		return encodeJPG(&this->bmp, filename, quality);

	}

	DLL_EXPORT inline int matrix::width(void) const {
		return this->bmp.width;
	}
	DLL_EXPORT inline int matrix::height(void) const {
		return this->bmp.height;
	}
	DLL_EXPORT inline int matrix::channel(void) const {
		return this->bmp.ch;
	}
	DLL_EXPORT inline int matrix::empty(void) const {
		return this->_empty;
	}

}
