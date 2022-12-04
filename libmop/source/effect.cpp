#include "effect.hpp"

#include <stdio.h>
#include <string.h>
#include <math.h>

#include <CL/cl.h>

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

		platformProperties* pp;
		int pp_num;
		device::GetPlatform(&pp, &pp_num);

		/*
		FILE* fp;
		fp = fopen("effect.cl", "r");
		if (fp == NULL) {
			printf("%s load failed\n", "effect.cl");
			return;
		}

		fseek(fp, 0, SEEK_END);
		const int filesize = ftell(fp);

		fseek(fp, 0, 0);
		char* source_code = (char*)malloc(filesize);
		size_t sourceSize = fread(source_code, sizeof(char), filesize, fp);
		fclose(fp);
		free(source_code);
		*/
		///*
		#define OCL_EXTERNAL_INCLUDE(x) #x
		const char sourcecode[] =
		#include "effect.cl"
		;
		//*/
		size_t sourceSize = 842;
		//printf("sourceSize:%d\n", sourceSize);
		cl_program program = (cl_program)(device::CompileCLProgram(
			(char*)sourcecode,
			sourceSize,
			&(pp[0].devices[0])
		));

		cl_int er;
		cl_kernel kernel = clCreateKernel(program, "Blur", &er);
		printf("kernel : %x, err : %d\n", kernel, er);

		int mem_size = sizeof(unsigned char) * src->width() * src->height() * src->channel();
		cl_mem cl_src = clCreateBuffer((cl_context)pp[0].devices[0].device_context, CL_MEM_READ_WRITE, mem_size, NULL, NULL);
		cl_mem cl_dst = clCreateBuffer((cl_context)pp[0].devices[0].device_context, CL_MEM_READ_WRITE, mem_size, NULL, NULL);

		clEnqueueWriteBuffer((cl_command_queue)pp[0].devices[0].device_command_queue, cl_src, CL_TRUE, 0, mem_size, src->data, 0, NULL, NULL);

		cl_int3 size = { src->width(), src->height(), src->channel() };
		int half_amount = static_cast<int>((float)amount / 2.0F + 0.5F);
		clSetKernelArg(kernel, 0, sizeof(cl_mem), &cl_src);
		clSetKernelArg(kernel, 1, sizeof(cl_mem), &cl_dst);
		clSetKernelArg(kernel, 2, sizeof(cl_int3), &size);
		clSetKernelArg(kernel, 3, sizeof(cl_int), &half_amount);

		size_t workSize[2] = { src->width(), src->height() };
		CL_CHECK_ERR(clEnqueueNDRangeKernel((cl_command_queue)pp[0].devices[0].device_command_queue, kernel, 2, NULL, workSize, NULL, 0, NULL, NULL));

		clEnqueueReadBuffer((cl_command_queue)pp[0].devices[0].device_command_queue, cl_dst, CL_TRUE, 0, mem_size, dst->data, 0, NULL, NULL);

		clReleaseMemObject(cl_src);
		clReleaseMemObject(cl_dst);

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
