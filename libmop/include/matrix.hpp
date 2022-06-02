#pragma once
#include "deflate/define.h"
#include "deflate/deflate.hpp"

namespace mop {

	class matrix {

	private:

		BITMAPDATA_t	bmp;
		bool			_empty;

	public:

		DLL_EXPORT matrix(void) : _empty(1) {};
		DLL_EXPORT matrix(const char* filename);

		DLL_EXPORT ~matrix(void);

		DLL_EXPORT int encode(const char* filename, int quality = 50);

		#pragma region getter
		DLL_EXPORT inline int width(void) const;
		DLL_EXPORT inline int height(void) const;
		DLL_EXPORT inline int empty(void) const;
		#pragma endregion

	};

}
