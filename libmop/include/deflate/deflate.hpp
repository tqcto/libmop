#pragma once

#include "define.h"

typedef unsigned char uchar;
typedef unsigned short ushort;

#pragma region vector define

template <typename T>
struct _mop_vector2 {

	T x;
	T y;

	_mop_vector2(T _x, T _y) {
		x = _x;
		y = _y;
	}

};

template <typename T>
struct _mop_vector3 {

	T x;
	T y;
	T z;

	_mop_vector3(T _x, T _y, T _z) {
		x = _x;
		y = _y;
		z = _z;
	}

};

typedef _mop_vector2<int> mop_vector2;
typedef _mop_vector2<float> mop_vector2f;
typedef _mop_vector2<double> mop_vector2d;

typedef _mop_vector3<int> mop_vector3;
typedef _mop_vector3<float> mop_vector3f;
typedef _mop_vector3<double> mop_vector3d;

#pragma endregion

#pragma region pixel define

template <typename T>
struct _mop_pixel {

	T red;
	T green;
	T blue;
	T alpha;

	_mop_pixel(T r, T g, T b, T a) {
		red = r;
		green = g;
		blue = b;
		alpha = a;
	}

};

typedef _mop_pixel<uchar> mop_pixel8;
typedef _mop_pixel<ushort> mop_pixel16;
typedef _mop_pixel<float> mop_pixel32;

#pragma endregion
