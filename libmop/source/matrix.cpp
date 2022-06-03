#include "..\include\matrix.hpp"

#include "..\include\reader.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	DLL_EXPORT matrix::matrix(matrix* src) {

		if (!this->_empty) {
			data_free();
			this->_empty = true;
		}

		int w = src->width();
		int h = src->height();
		int c = src->channel();

		if (data_malloc(w, h, c)) return;

		this->bmp.width		= w;
		this->bmp.height	= h;
		this->bmp.ch		= c;

		memcpy(this->bmp.data, src->data(), w * h * c);

	}
	DLL_EXPORT matrix::matrix(int width, int height, int channels) {

		if (!this->_empty) {
			data_free();
			this->_empty = true;
		}

		if (data_malloc(width, height, channels)) return;

		this->bmp.width		= width;
		this->bmp.height	= height;
		this->bmp.ch		= channels;

	}

	DLL_EXPORT matrix::~matrix(void) {

		data_free();

	}

	DLL_EXPORT int matrix::data_malloc(int width, int height, int channels) {

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

	DLL_EXPORT void matrix::Resize(double size_w, double size_h) {

		int w = this->bmp.width,
			h = this->bmp.height;

		int aw = (double)w * size_w,
			ah = (double)h * size_h;

		uchar* src = (uchar*)malloc(sizeof(uchar) * w * h * this->bmp.ch);
		memcpy(src, this->bmp.data, w * h * this->bmp.ch);

		this->bmp.width		= aw;
		this->bmp.height	= ah;
		free(this->bmp.data);
		this->bmp.data = (uchar*)malloc(sizeof(uchar) * aw * ah * this->bmp.ch);

		double	ow, oh;
		int		x0, x1, y0, y1, dx, dy;

		for (int y = 0; y < h; y++) {

			oh = (double)y / size_h;
			y0 = MIN(MAX(static_cast<int>(oh), 0), h - 1);
			y1 = MIN(MAX(y0 + 1, 0), h - 1);
			dy = oh - y0;

			for (int x = 0; x < w; x++) {

				ow = (double)x / size_w;
				x0 = MIN(MAX(static_cast<int>(ow), 0), w - 1);
				x1 = MIN(MAX(x0 + 1, 0), w - 1);

				dx = ow - x0;

				for (int c = 0; c < this->bmp.ch; c++) {

					if (x < aw && y < ah) {
						*ac(x, y, c) =
								src[this->bmp.ch * (x1 + y1 * w) + c] * dx * dy
							+	src[this->bmp.ch * (x1 + y0 * w) + c] * dx * (1 - dy)
							+	src[this->bmp.ch * (x0 + y1 * w) + c] * (1 - dx) * dy
							+	src[this->bmp.ch * (x0 + y0 * w) + c] * (1 - dx) * (1 - dy);
					}

				}
			}
		}

		free(src);

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
	DLL_EXPORT inline uchar* matrix::data(void) const {
		return this->bmp.data;
	}
	DLL_EXPORT inline int matrix::empty(void) const {
		return this->_empty;
	}

}
