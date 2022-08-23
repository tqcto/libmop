﻿///*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <iostream>

#include "libmop.h"
#include "libmop_cuda.h"

#define MOP_LOG_SHOW

#define BMP_FILE "F:\\SS\\画像171.jpg"
//#define BMP_FILE "F:\\映像素材\\sketches\\wood.jpg"
#define ENCODE_F "F:\\SS\\encode171.jpg"

using namespace mop;
using namespace mop::device;

using namespace mop_cuda;

int main(void) {

    platformProperties* props;
    int num = 0;
    GetPlatform(&props, &num);

    matrix src(BMP_FILE);
    matrix dst(src.width(), src.height(), 1);

    dst = src;

    dst.encode(ENCODE_F);

    src.Free();
    dst.Free();

    return 0;

}

//*/
/*
#include <amp.h>
#include <amp_graphics.h>
#include <assert.h>
#include <iostream>
#include <fstream>
//#include <cstdlib>
#include <string>
#include <vector>
#include <pshpack2.h>
using namespace std;
using namespace concurrency;
using namespace concurrency::graphics;
struct BitmapHeader
{
    unsigned short bfType;
    unsigned long bfSize;
    unsigned short bfReserved1;
    unsigned short bfReserved2;
    unsigned long bfOffBits;
    unsigned int biSize;
    int biWidth;
    int biHeight;
    unsigned short biPlanes;
    unsigned short biBitCount;
    unsigned int biCompression;
    unsigned int biSizeImage;
    int biXPixPerMeter;
    int biYPixPerMeter;
    unsigned int biClrUsed;
    unsigned int biClrImporant;
};
#include <poppack.h>

int ToBitmapStep(int step)
{
    int paddings[] = { 0, 3, 2, 1 };
    return step + paddings[step % 4];
}
void LoadBitmap24(std::string path, int* width, int* height, std::vector<unsigned char>* pixels)
{
    std::ifstream file(path, std::ios::binary);
    assert(file.is_open());

    BitmapHeader header;
    file.read((char*)&header, sizeof(header));
    int w = header.biWidth;
    int h = header.biHeight;
    int step = ToBitmapStep(3 * w);

    std::vector<unsigned char> originalPixels(step * h);
    file.read((char*)originalPixels.data(), originalPixels.size());

    pixels->resize(3 * w * h);
    for (int i = 0; i < h; ++i)
        memcpy(pixels->data() + i * 3 * w, originalPixels.data() + i * step, 3 * w);

    *width = w;
    *height = h;
}
void SaveBitmap24(std::string path, int width, int height, const unsigned char* pixels)
{
    std::ofstream file(path, std::ios::binary);
    assert(file.is_open());

    int step = ToBitmapStep(3 * width);

    BitmapHeader header;
    header.bfType = 0x4d42; // "BM"
    header.bfSize = step * height + 54;
    header.bfReserved1 = 0;
    header.bfReserved2 = 0;
    header.bfOffBits = 54;
    header.biSize = 40;
    header.biWidth = width;
    header.biHeight = height;
    header.biPlanes = 1;
    header.biBitCount = 24;
    header.biCompression = 0;
    header.biSizeImage = 0;
    header.biXPixPerMeter = 0;
    header.biYPixPerMeter = 0;
    header.biClrUsed = 0;
    header.biClrImporant = 0;
    file.write((char*)&header, sizeof(header));

    std::vector<unsigned char> bmpPixels(step * height);
    for (int i = 0; i < height; ++i)
        memcpy(bmpPixels.data() + i * step, pixels + i * 3 * width, 3 * width);
    file.write((char*)bmpPixels.data(), bmpPixels.size());
}

int main()
{
    int width, height;
    std::vector<byte> srcPixels;
    LoadBitmap24("画像171.bmp", &width, &height, &srcPixels);

    // bits_per_scalar_elementに8Uを指定した場合、texture_view<const int>経由でアクセスしないとエラーになります。
    concurrency::graphics::texture<int, 2> srcTexture(height, 3 * width, srcPixels.data(), srcPixels.size(), 8U);
    concurrency::graphics::texture_view<const int, 2> srcView(srcTexture);

    concurrency::graphics::texture<int, 2> dstTexture(height, 3 * width, 8U);

    concurrency::extent<2> extent(height, width);
    concurrency::parallel_for_each(extent, [&, srcView](concurrency::index<2> idx) restrict(amp) {
        concurrency::index<2> idx1(idx[0], 3 * idx[1]);
        concurrency::index<2> idx2(idx[0], 3 * idx[1] + 1);
        concurrency::index<2> idx3(idx[0], 3 * idx[1] + 2);
        dstTexture.set(idx1, srcView[idx3]);
        dstTexture.set(idx2, srcView[idx2]);
        dstTexture.set(idx3, srcView[idx1]);
        });

    std::vector<byte> dstPixels(width * height * 3);
    concurrency::graphics::copy(dstTexture, dstPixels.data(), dstPixels.size());

    SaveBitmap24("Parrots2.bmp", width, height, dstPixels.data());

    return 0;
}
*/