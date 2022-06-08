#pragma once

#include "define.h"

namespace mop {

	typedef unsigned char	uchar;
	typedef unsigned short	ushort;
	typedef unsigned int	uint;

	#pragma region vector define

	template <typename T>
	struct _vector2 {

		T x;
		T y;

		_vector2(void) {
			x = 0;
			y = 0;
		}
		_vector2(T _x, T _y) {
			x = _x;
			y = _y;
		}

	};

	template <typename T>
	struct _vector3 {

		T x;
		T y;
		T z;

		_vector3(void) {
			x = 0;
			y = 0;
			z = 0;
		}
		_vector3(T _x, T _y, T _z) {
			x = _x;
			y = _y;
			z = _z;
		}

	};

	typedef _vector2<int> vector2;
	typedef _vector2<float> vector2f;
	typedef _vector2<double> vector2d;

	typedef _vector3<int> vector3;
	typedef _vector3<float> vector3f;
	typedef _vector3<double> vector3d;

#pragma endregion

	#pragma region pixel define

	enum {

		RED = 0,
		GREEN,
		BLUE,
		//ALPHA

	};

	typedef enum {

		GRAY = 1,
		RGB = 3,
		RGBA,

	}color_number;

	typedef enum {

		U8 = 8,
		U16 = 16,
		U32 = 32,

	}color_bit;

	/**
	* @enum repeat_mode
	* 画像データのリピート方式を指定します。
	*/
	typedef enum {

		repeat_none,
		repeat_normal,
		repeat_mirror

	}repeat_mode;

	///*
	template <typename T> struct _pixel;
	template <>	struct _pixel<uchar> {

		uchar red;
		uchar green;
		uchar blue;
		uchar alpha;

		_pixel(void) {
			red = 0x00;
			green = 0x00;
			blue = 0x00;
			alpha = 0x00;
		}
		_pixel(uchar r, uchar g, uchar b, uchar a) {
			red = r;
			green = g;
			blue = b;
			alpha = a;
		}

	};
	template <>	struct _pixel<ushort> {

		ushort red;
		ushort green;
		ushort blue;
		ushort alpha;

		_pixel(void) {
			red = 0x00;
			green = 0x00;
			blue = 0x00;
			alpha = 0x00;
		}
		_pixel(ushort r, ushort g, ushort b, ushort a) {
			red = r;
			green = g;
			blue = b;
			alpha = a;
		}

	};
	template <>	struct _pixel<float> {

		float red;
		float green;
		float blue;
		float alpha;

		_pixel(void) {
			red = 0x00;
			green = 0x00;
			blue = 0x00;
			alpha = 0x00;
		}
		_pixel(float r, float g, float b, float a) {
			red = r;
			green = g;
			blue = b;
			alpha = a;
		}

	};

	typedef _pixel<uchar> pixel8;
	typedef _pixel<ushort> pixel16;
	typedef _pixel<float> pixel32;
	//*/

	typedef struct rgb {

		uchar r;
		uchar g;
		uchar b;

	}rgb;
	typedef struct hsv {

		uchar h;
		uchar s;
		uchar v;

	}hsv;

	#pragma region libjpeg

	typedef struct bmp_t {

		uchar*	data;
		uint	width;
		uint	height;
		uint	ch;

		bmp_t(void) {
			data = nullptr;
			width	= 0;
			height	= 0;
			ch		= 0;
		}

	}BITMAPDATA_t;

	#pragma endregion

#pragma endregion

}
