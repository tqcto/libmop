#pragma once
#include "deflate/define.h"
#include "deflate/deflate.hpp"

namespace mop {
namespace device {

	/* @fn
	* @brief ���Z�v���b�g�t�H�[�����擾���܂��B
	* @param result �v���b�g�t�H�[���̎擾�|�C���^
	* @param number �v���b�g�t�H�[����
	*/
	DLL_EXPORT void GetPlatform(platformProperties** result, int* number);

}
}
