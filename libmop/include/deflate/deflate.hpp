#pragma once

#include "define.h"

namespace mop {

	typedef unsigned char uchar;
	typedef unsigned short ushort;

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
		ALPHA

	};

	typedef enum {

		GRAY = 0,
		RGB,
		RGBA,
		BGR,
		BGRA

	}color_type;

	template <typename T>
	struct _pixel {

		T red;
		T green;
		T blue;
		T alpha;

		_pixel(void) {
			red = 0x00;
			green = 0x00;
			blue = 0x00;
			alpha = 0x00;
		}
		_pixel(T r, T g, T b, T a) {
			red = r;
			green = g;
			blue = b;
			alpha = a;
		}

	};

	typedef _pixel<uchar> pixel8;
	typedef _pixel<ushort> pixel16;
	typedef _pixel<float> pixel32;

#pragma endregion

}
