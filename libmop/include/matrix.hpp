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
		DLL_EXPORT matrix(matrix* src);
		DLL_EXPORT matrix(int width, int height, int channels);

		DLL_EXPORT ~matrix(void);

		#pragma region memory setup
		DLL_EXPORT int data_malloc(int width, int height, int channels);
		DLL_EXPORT void data_free(void);
		#pragma endregion

		DLL_EXPORT uchar* ac(int x, int y, int c);

		#pragma region matrix op
		DLL_EXPORT void Resize(double size_w, double size_h);
		#pragma endregion

		DLL_EXPORT int encode(const char* filename, int quality = 50);

		#pragma region getter
		DLL_EXPORT inline int width(void) const;
		DLL_EXPORT inline int height(void) const;
		DLL_EXPORT inline int channel(void) const;
		DLL_EXPORT inline uchar* data(void) const;
		DLL_EXPORT inline int empty(void) const;
		#pragma endregion

	};

}
