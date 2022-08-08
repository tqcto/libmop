#pragma once
#include "libmop.h"

namespace mop {

	/**
	* @fn
	* @brief �摜�f�[�^�ɂ̃m�C�Y��t�����܂��B
	* @param src �m�C�Y��t������摜�f�[�^
	* @param percent �t���x
	* @param seed �����_���V�[�h�l
	*/
	DLL_EXPORT void Noise(matrix* src, matrix* dst, int percent, int seed = 0);

	DLL_EXPORT void Blur(matrix* src, matrix* dst, int amount);

	DLL_EXPORT void RadialBlur(matrix* src, matrix* dst, int amount);

	/**
	* @fn
	* @brief rgb�f�[�^��hsv�f�[�^�ɕϊ����܂��B
	* @param c rgb�f�[�^
	* @return hsv�f�[�^��Ԃ��܂��B
	*/
	DLL_EXPORT hsv rgb2hsv(rgb c);
	/**
	* @fn
	* @brief hsv�f�[�^��rgb�f�[�^�ɕϊ����܂��B
	* @param c hsv�f�[�^
	* @return rgb�f�[�^��Ԃ��܂��B
	*/
	DLL_EXPORT rgb hsv2rgb(hsv c);

}
