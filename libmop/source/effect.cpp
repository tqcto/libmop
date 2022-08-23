#include "effect.hpp"

#include <stdio.h>
#include <math.h>

namespace mop {

	DLL_EXPORT void Noise(matrix* src, matrix* dst, int percent, int seed) {

		XS_SRAND(seed);
		
		if (percent == 0) return;
		else {
			double p = (double)percent / 100.0;
			for (int y = 0; y < src->height(); y++) {
				for (int x = 0; x < src->width(); x++) {
					for (int c = 0; c < src->channel(); c++) {

						int r = *src->access(x, y, c);
						if ((int)(XSR_RAND(0, 1) + 0.5)) {
							r += (int)(XSR_RAND(0x00, 0xFF) * p);
						}
						else {
							r -= (int)(XSR_RAND(0x00, 0xFF) * p);
						}
						*dst->access(x, y, c) = RANGE(0x00, 0xFF, r);

					}
				}
			}
		}

	}

	DLL_EXPORT void Blur(matrix* src, matrix* dst, int amount) {

		int w = src->width(),
			h = src->height(),
			c = src->channel();

		int m = 0, n = 0;
		if ((amount * 5) % 10 != 0) {
			m = amount / 2;
			n = m;
		}
		else {
			m = (double)amount / 2.0;
			n = m - 1;
		}

		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {
				for (int cc = 0; cc < c; cc++) {

					int data = 0,
						num = 1;

					for (int yy = y - m; yy < y + n; yy++) {
						for (int xx = x - m; xx < x + n; xx++) {

							if (0 <= xx && xx < w && 0 <= yy && yy < h) {
								data += (int)(*src->access(xx, yy, cc));
								num++;
							}

						}
					}

					*dst->access(x, y, cc) = data / num;
					//dst->data[(x + y * w) * c + cc] = data / num;

				}
			}
		}

	}

	DLL_EXPORT void RadialBlur(matrix* src, matrix* dst, int amount) {

		int x = 0,
			y = 0,
			a = 0;

		int w = src->width();
		int h = src->height();
		int ch = src->channel();

		double hw = (double)w / 2.0;
		double hh = (double)h / 2.0;

		double angle = 0;

		for (y = 0; y < h; y++) {
			for (x = 0; x < w; x++) {

				angle = atan2(y - hh, x - hw);
				double xx = (double)x + R2D(cos(angle)) - hw;
				double yy = (double)y + R2D(sin(angle)) - hh;

				for (int c = 0; c < ch; c++) {
					int data = 0;
					int num = 1;

					for (a = 0; a < amount; a++) {

						int _x = static_cast<int>(xx * (double)a + 0.5);
						int _y = static_cast<int>(yy * (double)a + 0.5);

						if (0 <= _x && _x < w && 0 <= _y && _y < h) {
							data += (int)*src->access(_x, _y, c);
							num++;
						}

					}

					//dst->data[(x + y * w) * ch + c] = data / amount;
					*dst->access(x, y, c) = data / num;
				}

			}
		}

	}

	DLL_EXPORT hsv rgb2hsv(rgb c) {

		hsv ret;
		uchar min, max;

		min = c.r < c.g ? (c.r < c.b ? c.r : c.b) : (c.g < c.b ? c.g : c.b);
		max = c.r > c.g ? (c.r > c.b ? c.r : c.b) : (c.g > c.b ? c.g : c.b);

		ret.v = max;
		if (ret.v == 0) {
		
			ret.h = 0;
			ret.s = 0;
			return ret;
		
		}

		ret.s = 0xFF * ((long)(max - min)) / ret.v;
		if (ret.s == 0) {
			
			ret.h = 0;
			return ret;
		
		}

		if (max == c.r) ret.h = 0 + 43 * (c.g - c.b) / (max - min);
		else if (max == c.g) ret.h = 85.43 * (c.b - c.r) / (max - min);
		else ret.h = 171 + 43 * (c.r - c.g) / (max - min);

		return ret;

	}
	DLL_EXPORT rgb hsv2rgb(hsv c) {

		rgb ret;
		uchar region, p, q, t;
		uint h, s, v, remainder;

		if (c.s == 0) {

			ret.r = c.v;
			ret.g = c.v;
			ret.b = c.v;
			return ret;

		}

		h = c.h;
		s = c.s;
		v = c.v;

		region = h / 43;
		remainder = (h - (region * 43)) * 6;

		p = (v * (0xFF - s)) >> 8;
		q = (v * (0xFF - ((s * remainder) >> 8))) >> 8;
		t = (v * (0xFF - ((s * (0xFF - remainder)) >> 8))) >> 8;

		switch (region) {
		case 0:
			ret.r = v;
			ret.g = t;
			ret.b = p;
			break;

		case 1:
			ret.r = q;
			ret.g = v;
			ret.b = p;
			break;

		case 2:
			ret.r = p;
			ret.g = v;
			ret.b = t;
			break;

		case 3:
			ret.r = p;
			ret.g = q;
			ret.b = v;
			break;

		case 4:
			ret.r = t;
			ret.g = p;
			ret.b = v;
			break;

		default:
			ret.r = v;
			ret.g = p;
			ret.b = q;
			break;

		}

		return ret;

	}

}
