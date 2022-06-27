#include "..\include\matrix.hpp"

#include "..\include\libmop.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
			Free();
			this->_empty = true;
		}

		int w = src->width();
		int h = src->height();
		int c = src->channel();

		if (Malloc(w, h, c)) return;

		this->bmp.width		= w;
		this->bmp.height	= h;
		this->bmp.ch		= c;

		memcpy(this->bmp.data, src->data(), w * h * c);

	}
	DLL_EXPORT matrix::matrix(int width, int height, int channels) {

		if (!this->_empty) {
			Free();
			this->_empty = true;
		}

		if (Malloc(width, height, channels)) return;

		this->bmp.width		= width;
		this->bmp.height	= height;
		this->bmp.ch		= channels;

	}

	DLL_EXPORT matrix::~matrix(void) {

		Free();

	}

	DLL_EXPORT int matrix::Malloc(int width, int height, int channels) {

		if (!this->_empty) {
			Free();
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
	DLL_EXPORT int matrix::Memcpy(uchar* data, int width, int height, int channels) {

		freeBMP(&this->bmp);

		int size = sizeof(uchar) * width * height * channels;
		this->bmp.data = (uchar*)malloc(size);
		memcpy(this->bmp.data, data, size);

		return 0;

	}
	DLL_EXPORT void matrix::Free(void) {

		freeBMP(&this->bmp);
		this->_empty = true;

	}

	DLL_EXPORT uchar* matrix::access(int x, int y, int c) {

		return &this->bmp.data[(x + y * this->bmp.width) * this->bmp.ch + c];

	}
	DLL_EXPORT rgbp matrix::access(int x, int y) {

		return rgbp(
			&this->bmp.data[(x + y * this->bmp.width) * this->bmp.ch],
			&this->bmp.data[(x + y * this->bmp.width) * this->bmp.ch + 1],
			&this->bmp.data[(x + y * this->bmp.width) * this->bmp.ch + 2]
		);

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
						*access(x, y, c) =
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
	DLL_EXPORT void matrix::Rotate(double angle, repeat_mode mode, int cx, int cy) {

		int w = this->bmp.width,
			h = this->bmp.height;

		int hw = round((double)w / 2.0),
			hh = round((double)h / 2.0);

		double ox, oy;
		int x0, y0;

		int min_x = 0, min_y = 0, max_x = 0, max_y = 0;

		angle = angle * M_PI / 180.0;

		for (int y = 0; y < h; y += (h - 1)) {
			for (int x = 0; x < w; x += (w - 1)) {
				ox =  ((cx + x) - hw) * cos(angle) + ((cy + y) - hh) * sin(angle) + hw;
				oy = -((cx + x) - hw) * sin(angle) + ((cy + y) - hh) * cos(angle) + hh;
				min_x = ox < min_x ? ox : min_x;
				min_y = oy < min_y ? oy : min_y;
				max_x = max_x < ox ? ox : max_x;
				max_y = max_y < oy ? oy : max_y;
			}
		}

		int aw = abs(min_x) + max_x,
			ah = abs(min_y) + max_y;

		uchar* src = (uchar*)malloc(sizeof(uchar) * w * h * this->bmp.ch);
		memcpy(src, this->bmp.data, w * h * this->bmp.ch);

		free(this->bmp.data);
		this->bmp.data = (uchar*)malloc(sizeof(uchar) * w * h * this->bmp.ch);
		//this->bmp.data = (uchar*)malloc(sizeof(uchar) * aw * ah * this->bmp.ch);
		//this->bmp.width		= aw;
		//this->bmp.height	= ah;

		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {

				ox =  ((cx + x) - hw) * cos(angle) + ((cy + y) - hh) * sin(angle) + hw;
				oy = -((cx + x) - hw) * sin(angle) + ((cy + y) - hh) * cos(angle) + hh;

				x0 = ox + 0.5;
				y0 = oy + 0.5;

				switch (mode) {
				case repeat_mode::repeat_none:
					if (0 <= x0 && x0 < w && 0 <= y0 && y0 < h) {
						for (int c = 0; c < this->bmp.ch; c++) {
							*access(x, y, c) = src[this->bmp.ch * (x0 + y0 * w) + c];
						}
					}
					else {
						for (int c = 0; c < this->bmp.ch; c++) {
							*access(x, y, c) = 0x00;
						}
					}
					break;
				case repeat_mode::repeat_tile:
					x0 = tile(x0, w - 1);
					y0 = tile(y0, h - 1);
					for (int c = 0; c < this->bmp.ch; c++) {
						*access(x, y, c) = src[this->bmp.ch * (x0 + y0 * w) + c];
					}
					break;
				case repeat_mode::repeat_mirror:
					x0 = mirror(x0, w - 1);
					y0 = mirror(y0, h - 1);
					for (int c = 0; c < this->bmp.ch; c++) {
						*access(x, y, c) = src[this->bmp.ch * (x0 + y0 * w) + c];
					}
					break;
				}				

			}
		}

		free(src);

	}

	DLL_EXPORT void matrix::HSV(int h, int s, int v) {

		rgb c1;
		hsv c2;

		int _h, _s, _v;

		for (int y = 0; y < this->height(); y++) {
			for (int x = 0; x < this->width(); x++) {

				c1 = { *this->access(x, y, 0), *this->access(x, y, 1), *this->access(x, y, 2) };
				c2 = rgb2hsv(c1);

				_h = (int)c2.h + h;
				_s = (int)c2.s + s;
				_v = (int)c2.v + v;

				c2.h = RANGE(0x00, 0xFF, _h);
				c2.s = RANGE(0x00, 0xFF, _s);
				c2.v = RANGE(0x00, 0xFF, _v);

				c1 = hsv2rgb(c2);
				
				*this->access(x, y, 0) = c1.r;
				*this->access(x, y, 1) = c1.g;
				*this->access(x, y, 2) = c1.b;

			}
		}

	}

	DLL_EXPORT int matrix::encode(const char* filename, int quality) {

		return encodeJPG(&this->bmp, filename, quality);

	}

	DLL_EXPORT inline int matrix::width(void) const noexcept {
		return this->bmp.width;
	}
	DLL_EXPORT inline int matrix::height(void) const noexcept {
		return this->bmp.height;
	}
	DLL_EXPORT inline int matrix::channel(void) const noexcept {
		return this->bmp.ch;
	}
	DLL_EXPORT inline uchar* matrix::data(void) const noexcept {
		return this->bmp.data;
	}
	DLL_EXPORT inline uchar* const* matrix::data_ptr(void) const noexcept {
		return &this->bmp.data;
	}
	DLL_EXPORT inline int matrix::empty(void) const noexcept {
		return this->_empty;
	}

}
