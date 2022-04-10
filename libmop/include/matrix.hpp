#pragma once
#include "deflate/deflate.hpp"
#include "gpu_calc.cuh"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <amp.h>
#include <ppl.h>

namespace mop {

	class matrix {

	private:

		bool _empty = true;

		int	_width = 0,
			_height = 0,
			_channel = 0;

		color_type _color;

	public:
		uchar* data;

		DLL_EXPORT matrix(void) : _empty(true) {};
		DLL_EXPORT matrix(int w, int h, color_type c) {

			if (w <= 0 || h <= 0) return;

			this->_empty = false;

			this->_width = w;
			this->_height = h;
			this->_color = c;

			switch (c) {

			case color_type::GRAY:
				this->_channel = 1;
				break;

			case color_type::RGB:
				this->_channel = 3;
				break;

			case color_type::RGBA:
				this->_channel = 4;
				break;

			}

			int data_size = w * h * this->_channel;

			this->data = (uchar*)malloc(sizeof(uchar) * data_size);

			initialize(&this->data, this->_width, this->_height, this->_channel);

			/*
			concurrency::parallel_for(0, h, [&](int y){
				init_loop_x(y);
			});
			*/

		}

		#pragma region getter
		DLL_EXPORT inline int width(void) const { return this->_width; }
		DLL_EXPORT inline int height(void) const { return this->_height; }
		//DLL_EXPORT inline int channel(void) { return this->_channel; }

		DLL_EXPORT inline bool empty(void) const { return this->_empty; }
		#pragma endregion

		uchar* access(int x, int y) const {

			return &this->data[y * this->_width + x];

		}

	};

}
