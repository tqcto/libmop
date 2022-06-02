#include "deflate/define.h"
#include "deflate/deflate.hpp"

using namespace mop;

DLL_EXPORT int decodeJPG(BITMAPDATA_t* bmp, const char* filename);
DLL_EXPORT int encodeJPG(BITMAPDATA_t* bmp, const char* filename, int quality = 50);
DLL_EXPORT int freeBMP(BITMAPDATA_t* bmp);
