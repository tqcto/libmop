#pragma once
#include "libmop.h"

namespace mop {

	/**
	* @fn
	* @brief 画像データにのノイズを付加します。
	* @param src ノイズを付加する画像データ
	* @param percent 付加度
	* @param seed ランダムシード値
	*/
	DLL_EXPORT void Noise(matrix* src, int percent, int seed = 0);

	/**
	* @fn
	* @brief rgbデータをhsvデータに変換します。
	* @param c rgbデータ
	* @return hsvデータを返します。
	*/
	DLL_EXPORT hsv rgb2hsv(rgb c);
	/**
	* @fn
	* @brief hsvデータをrgbデータに変換します。
	* @param c hsvデータ
	* @return rgbデータを返します。
	*/
	DLL_EXPORT rgb hsv2rgb(hsv c);

}
