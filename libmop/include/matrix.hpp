#pragma once
#include "deflate/define.h"
#include "deflate/deflate.hpp"

namespace mop {

	class matrix {

	private:

		BITMAPDATA_t	bmp;
		bool			_empty;

	public:

		/**
		* @fn
		* @brief 空のクラスを作成するコンストラクタです。これを使用した場合メモリが確保されないので、data_malloc 関数を利用するなどしてメモリを確保する必要があります。
		*/
		DLL_EXPORT matrix(void) noexcept : _empty(1) {};
		/**
		* @fn
		* @brief 画像ファイルを読み込みます。
		* @param filename 画像ファイルパス
		*/
		DLL_EXPORT matrix(const char* filename);
		/**
		* @fn
		* @brief 既存の画像クラスをコピーします。
		* @param src 画像クラスのポインタ
		*/
		DLL_EXPORT matrix(matrix* src);
		/**
		* @fn
		* @brief サイズを指定して画像データを作成します。
		* @param width 行数
		* @param height 列数
		* @param channels 色素数
		*/
		DLL_EXPORT matrix(int width, int height, int channels);

		/**
		* @fn
		* @brief デストラクタです。画像データのメモリの解放などを行います。
		*/
		DLL_EXPORT ~matrix(void);

		#pragma region memory setup
		/**
		* @fn
		* @brief 画像データのメモリを確保します。
		* @param width 行数
		* @param height 列数
		* @param channels 色素数
		* @return メモリが確保できた場合は0、できなかった場合は-1以下を返します。
		*/
		DLL_EXPORT int Malloc(int width, int height, int channels);
		/**
		* @fn
		* @brief 画像データのメモリを解放します。
		*/
		DLL_EXPORT void Free(void);
		DLL_EXPORT int Memcpy(uchar* data, int width, int height, int channels);
		#pragma endregion

		/**
		* @fn
		* @brief 指定した座標の画素データを取得します。
		* @param x 行番号
		* @param y 列番号
		* @param c 色素番号
		* @return 画素データのポインタを返します。
		*/
		DLL_EXPORT uchar* access(int x, int y, int c);

		#pragma region matrix op
		/**
		* @fn
		* @brief 画像データをサイズ変更します。
		* @param size_w(%) 行サイズ
		* @param size_h(%) 列サイズ
		*/
		DLL_EXPORT void Resize(double size_w, double size_h);
		/**
		* @fn
		* @brief 画像データを回転します。
		* @param angle 回転角度
		* @param mode 外部点のラッピング補完方法指定
		* @param cx 行方向の中心軸
		* @param cy 列方向の中心軸
		*/
		DLL_EXPORT void Rotate(double angle, repeat_mode mode = repeat_none, int cx = 0, int cy = 0);
		#pragma endregion

		#pragma region color variation
		/**
		* @fn
		* @brief 画像データをHSV色空間に変換して 色相、 彩度、 明度 を変更します。
		* @param h 色相
		* @param s 彩度
		* @param v 明度
		*/
		DLL_EXPORT void HSV(int h, int s, int v);
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
		/**
		* @fn
		* @brief 行の長さを取得します。
		*/
		DLL_EXPORT inline int width(void) const noexcept;
		/**
		* @fn
		* @brief 列の長さを取得します。
		*/
		DLL_EXPORT inline int height(void) const noexcept;
		/**
		* @fn
		* @brief 画素数を取得します。
		*/
		DLL_EXPORT inline int channel(void) const noexcept;
		/**
		* @fn
		* @brief 画像データを取得します。
		*/
		DLL_EXPORT inline uchar* data(void) const noexcept;
		DLL_EXPORT inline uchar* const* data_ptr(void) const noexcept;
		/**
		* @fn
		* @brief 画像データが空かどうかを取得します。
		*/
		DLL_EXPORT inline int empty(void) const noexcept;
		#pragma endregion

	};

}
