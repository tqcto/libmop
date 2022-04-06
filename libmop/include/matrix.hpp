#pragma once
#include "deflate/deflate.hpp"

namespace mop {

	class matrix {

	private:

		bool _empty = true;

		int	_width = 0,
			_height = 0,
			_channel = 0;

	public:

		DLL_EXPORT matrix(void) : _empty(true) {};
		DLL_EXPORT matrix(int w, int h, color_type c);

		DLL_EXPORT inline int width(void);
		DLL_EXPORT inline int height(void);
		DLL_EXPORT inline int channel(void);

		DLL_EXPORT inline bool empty(void);

	};

}
