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
		/**
		* @fn
		* @brief 画像データのメモリを確保します。
		* @param width 列数
		* @param height 行数
		* @param channels 色素数
		* @return メモリが確保できた場合は0、できなかった場合は-1以下を返します。
		*/
		DLL_EXPORT int data_malloc(int width, int height, int channels);
		/**
		* @fn
		* @brief 画像データのメモリを解放します。
		*/
		DLL_EXPORT void data_free(void);
		#pragma endregion

		/**
		* @fn
		* @brief 指定した座標の画素データを取得します。
		* @param x 列番号
		* @param y 行番号
		* @param c 色素番号
		* @return 画素データのポインタを返します。
		*/
		DLL_EXPORT uchar* access(int x, int y, int c);

		#pragma region matrix op
		/**
		* @fn
		* @brief 画像データをサイズ変更します。
		* @param size_w(%) 列サイズ
		* @param size_h(%) 行サイズ
		*/
		DLL_EXPORT void Resize(double size_w, double size_h);
		/**
		* @fn
		* @brief 画像データを回転します。
		* @param angle 回転角度
		* @param mode 外部点のラッピング補完方法指定
		* @param cx 列方向の中心軸
		* @param cy 行方向の中心軸
		*/
		DLL_EXPORT void Rotate(double angle, repeat_mode mode = repeat_none, int cx = 0, int cy = 0);
		#pragma endregion

		/**
		* @fn
		* @brief 画像データを保存します。
		* @param filename 保存ファイルパス
		* @param quality 保存する解像度
		* @return 保存が成功した場合は0、できなかった場合はそれ以外を返します。
		*/
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
