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

	/* @fn
	* @brief .cl�t�@�C�����R���p�C�����܂��B
	* @param source_code �\�[�X�R�[�h
	* @param code_size �\�[�X�R�[�h�̃T�C�Y
	* @param device_context �g�p����f�o�C�X�̃R���e�L�X�g
	* @param device_id �g�p����f�o�C�XID
	* @return cl_program�\����
	*/
	DLL_EXPORT void* CompileCLProgram(char* source_code, int code_size, deviceProperties* device);

}
}
