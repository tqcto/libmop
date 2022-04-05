#pragma once

template<typename T>
struct _mop_vector2 {

	T x;
	T y;

	_mop_vector2(T _x, T _y) {
		x = _x;
		y = _y;
	}

};

typedef _mop_vector2<int> mop_vector2;
typedef _mop_vector2<float> mop_vector2f;
typedef _mop_vector2<double> mop_vector2d;
