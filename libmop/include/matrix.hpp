#pragma once
#include "deflate/deflate.hpp"

namespace mop {

	template <typename T>
	class matrix {

	private:

		bool _empty = true;

		int	_width = 0,
			_height = 0,
			_channel = 0;

	public:
		//typedef _pixel<T> pix;
		_pixel<T>* data;

		DLL_EXPORT matrix(void) : _empty(true) {};
		DLL_EXPORT matrix(int w, int h, color_type c) {

			if (w <= 0 || h <= 0) return;

			this->_empty = false;

			this->_width = w;
			this->_height = h;

			switch (c) {

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

			}

		}

		DLL_EXPORT inline int width(void) { return this->_width; }
		DLL_EXPORT inline int height(void) { return this->_height; }
		DLL_EXPORT inline int channel(void) { return this->_channel; }

		DLL_EXPORT inline bool empty(void) { return this->_empty; }

	};

}
