#include "..\include\reader.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>

DLL_EXPORT int decodeJPG(BITMAPDATA_t* bmp, const char* filename) {

	struct jpeg_decompress_struct jpeg;
	struct jpeg_error_mgr err;

	FILE* file;
	JSAMPLE* tmp;

	int w, h, c;

	jpeg.err = jpeg_std_error(&err);

	file = fopen(filename, "rb");
	if (file == NULL) {
		printf("can't open fiile : %s\n", filename);
		fclose(file);
		return -1;
	}

	jpeg_create_decompress(&jpeg);
	jpeg_stdio_src(&jpeg, file);
	jpeg_read_header(&jpeg, TRUE);
	jpeg_start_decompress(&jpeg);

	w = jpeg.output_width;
	h = jpeg.output_height;
	c = jpeg.out_color_components;

	//printf("width: %d, height: %d, channel: %d\n", w, h, c);

	bmp->data = (unsigned char*)malloc(sizeof(unsigned char) * w * h * c);
	if (bmp->data == NULL) {
		printf("data malloc error\n");
		fclose(file);
		jpeg_destroy_decompress(&jpeg);
		return -2;
	}

	for (int y = 0; y < h; y++) {
		tmp = bmp->data + y * c * w;
		jpeg_read_scanlines(&jpeg, &tmp, 1);
	}

	bmp->width	= w;
	bmp->height	= h;
	bmp->ch		= c;

	jpeg_finish_decompress(&jpeg);
	jpeg_destroy_decompress(&jpeg);

	fclose(file);

	return 0;

}

DLL_EXPORT int encodeJPG(BITMAPDATA_t* bmp, const char* filename, int quality) {

	struct jpeg_compress_struct jpeg;
	struct jpeg_error_mgr err;
	
	FILE* file;
	JSAMPLE* address;

	int w, h, c;

	jpeg.err = jpeg_std_error(&err);
	jpeg_create_compress(&jpeg);

	file = fopen(filename, "wb");
	if (file == NULL) {
		printf("can't open file : %s\n", filename);
		jpeg_destroy_compress(&jpeg);
		fclose(file);
		return -1;
	}

	jpeg_stdio_dest(&jpeg, file);

	w = bmp->width;
	h = bmp->height;
	c = bmp->ch;

	jpeg.image_width		= w;
	jpeg.image_height		= h;
	jpeg.input_components	= c;
	jpeg.in_color_space = JCS_RGB;
	jpeg_set_defaults(&jpeg);

	jpeg_set_quality(&jpeg, quality, TRUE);

	jpeg_start_compress(&jpeg, TRUE);

	for (int y = 0; y < h; y++) {
		address = bmp->data + (y * w * c);
		jpeg_write_scanlines(&jpeg, &address, 1);
	}

	jpeg_finish_compress(&jpeg);
	jpeg_destroy_compress(&jpeg);

	fclose(file);

	return 0;

}

DLL_EXPORT int freeBMP(BITMAPDATA_t* bmp) {

	if (bmp->data != NULL) free(bmp->data);

	bmp->width	= 0;
	bmp->height	= 0;
	bmp->ch		= 0;

	return 0;
}
