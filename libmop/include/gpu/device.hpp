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

	/* @fn
	* @brief .clファイルをコンパイルします。
	* @param source_code ソースコード
	* @param code_size ソースコードのサイズ
	* @param device_context 使用するデバイスのコンテキスト
	* @param device_id 使用するデバイスID
	* @return cl_program構造体
	*/
	DLL_EXPORT void* CompileCLProgram(char* source_code, int code_size, deviceProperties* device);

}
}
