#pragma once
#include "deflate/define.h"
#include "deflate/deflate.hpp"

namespace mop {
namespace device {

	/* @fn
	* @brief 演算プラットフォームを取得します。
	* @param result プラットフォームの取得ポインタ
	* @param number プラットフォーム数
	*/
	DLL_EXPORT void GetPlatform(platformProperties** result, int* number);

}
}
