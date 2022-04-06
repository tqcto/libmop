#include "../include/matrix.hpp"

namespace mop {

	DLL_EXPORT matrix::matrix(int w, int h, color_type c) {

		if (w <= 0 || h <= 0) return;

		this->_empty = false;

		this->_width	= w;
		this->_height	= h;

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

	DLL_EXPORT inline int matrix::width(void) {
		return this->_width;
	}
	DLL_EXPORT inline int matrix::height(void) {
		return this->_height;
	}
	DLL_EXPORT inline int matrix::channel(void) {
		return this->_channel;
	}

	DLL_EXPORT inline bool matrix::empty(void) {
		return this->_empty;
	}

}
