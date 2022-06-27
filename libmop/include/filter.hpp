#pragma once
#include "libmop.h"

namespace mop {

	typedef rgb (*FilterValue)(rgb c);

	template <typename T, int M>
	void Filter(matrix* src, matrix* dst, T filter_kernel[M][M], FilterValue func) {

		int m, n;
		if ((M * 5) % 10 != 0) {
			m = M / 2;
			n = m;
		}
		else {
			m = (double)M / 2.0;
			n = m - 1;
		}

		for (int y = 0; y < src->height(); y++) {
			for (int x = 0; x < src->width(); x++) {

				int r = 0, g = 0, b = 0;

				for (int yy = y - m; yy <= y + n; yy++) {
					for (int xx = x - m; xx <= x + n; xx++) {
						if (0 <= xx && xx < src->width() && 0 <= yy && yy < src->height()) {

							rgb c = { *src->access(xx, yy, 0), *src->access(xx, yy, 1), *src->access(xx, yy, 2) };
							rgb f = func(c);
							int ck = filter_kernel[yy - y - 1][xx - x - 1];

							r += f.r * ck;
							g += f.g * ck;
							b += f.b * ck;

						}
					}
				}

				*dst->access(x, y, 0) = r;
				*dst->access(x, y, 1) = g;
				*dst->access(x, y, 2) = b;

			}
		}

	}

}
