#pragma once
#include "deflate/deflate.hpp"
#include "gpu_calc.cuh"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <amp.h>
#include <ppl.h>

namespace mop {

	template <class T>
	class matrix {

	private:

		bool _empty = true;

		int	_width = 0,
			_height = 0,
			_channel = 0;

		color_channel _color;
		//color_bit _bit;

		int inline sizeof_bit(void) const { return sizeof(T); }//{ return this->_bit >> 3; }

		void global_init(int w, int h, color_channel c) {

			if (w <= 0 || h <= 0) return;

			this->_empty = false;

			this->_width = w;
			this->_height = h;
			this->_color = c;

			switch (c) {

			case color_channel::GRAY:
				this->_channel = 1;
				break;

			case color_channel::RGB:
				this->_channel = 3;
				break;

			case color_channel::RGBA:
				this->_channel = 4;
				break;

			}

			//this->_bit = c.bit;

		}
		
		template <typename U> void data_init(void);
		template <> void data_init<uchar>(void) {
			initialize_uchar(&this->data, this->_width, this->_height, this->_channel);
			printf("uchar init.\n");
		}
		template <> void data_init<ushort>(void) {
			initialize_ushort(&this->data, this->_width, this->_height, this->_channel);
			printf("ushort init.\n");
		}
		template <> void data_init<float>(void) {
			initialize_float(&this->data, this->_width, this->_height, this->_channel);
			printf("float init.\n");
		}

	public:
		T* data;

		DLL_EXPORT matrix(void) : _empty(true) {};
		DLL_EXPORT matrix(int w, int h, color_channel c) {

			global_init(w, h, c);

			int data_size = w * h * this->_channel;

			this->data = (T*)malloc(sizeof(T) * data_size);
			data_init<T>();

			/*
			concurrency::parallel_for(0, h, [&](int y){
				init_loop_x(y);
			});
			*/

		}

		#pragma region getter
		DLL_EXPORT inline bool empty(void) const { return this->_empty; }
		DLL_EXPORT inline int width(void) const { return this->_width; }
		DLL_EXPORT inline int height(void) const { return this->_height; }
		DLL_EXPORT inline int channel(void) const { return this->_channel; }
		DLL_EXPORT inline int bit(void) const { return sizeof(T); }
		//DLL_EXPORT inline color_bit bit(void) const { return this->_bit; }
		#pragma endregion

		#pragma region calc to get
		DLL_EXPORT inline int rowbytes(void) const { return sizeof_bit() * this->_channel; }
		#pragma endregion

		T* access(int x, int y) const {

			return &this->data[y * this->_width + x];

		}

	};

}
