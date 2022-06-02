#pragma once
#include "deflate/define.h"

namespace mop {

	class matrix {

	private:

		int _width, _height;

	public:

		DLL_EXPORT matrix(void);
		DLL_EXPORT matrix(int w, int h);

		#pragma region getter
		DLL_EXPORT inline int width(void) const { return this->_width; }
		DLL_EXPORT inline int height(void) const { return this->_height; }
		#pragma endregion

	};

}
