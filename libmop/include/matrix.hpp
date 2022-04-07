#pragma once
#include "deflate/deflate.hpp"
#include "accelerator.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <amp.h>
#include <ppl.h>

namespace mop {

	template <typename T>
	class matrix {

	private:

		bool _empty = true;

		int	_width = 0,
			_height = 0;/*,
			_channel = 0;*/

		//concurrency::accelerator* accel;

		void init_loop_x(int y) {
			for (int x = 0; x < this->_width; x++) {
				_pixel<T>* d = &this->data[y * this->_width + x];
				
				d->red = 0x00;
				d->green = 0x00;
				d->blue = 0x00;
				d->alpha = 0x00;
			}
		}

	public:
		_pixel<T>* data;

		DLL_EXPORT matrix(void) : _empty(true) {};
		DLL_EXPORT matrix(int w, int h) {

			if (w <= 0 || h <= 0) return;

			this->_empty = false;

			this->_width = w;
			this->_height = h;

			/*switch (c) {

			case color_type::GRAY:
				this->_channel = 1;
				break;

			case color_type::BGR:
			case color_type::RGB:
				this->_channel = 3;
				break;

			case color_type::RGBA:
			case color_type::BGRA:
				this->_channel = 4;
				break;

			}*/

			int data_size = w * h;

			//*accel = acs[0];

			this->data = (_pixel<T>*)malloc(sizeof(_pixel<T>) * data_size);

			concurrency::parallel_for(0, h, [&](int y){
				init_loop_x(y);
			});

		}

		#pragma region getter
		DLL_EXPORT inline int width(void) const { return this->_width; }
		DLL_EXPORT inline int height(void) const { return this->_height; }
		//DLL_EXPORT inline int channel(void) { return this->_channel; }

		DLL_EXPORT inline bool empty(void) const { return this->_empty; }
		#pragma endregion

		_pixel<T>* access(int x, int y) const {

			return &this->data[y * this->_width + x];

		}

	};

}
