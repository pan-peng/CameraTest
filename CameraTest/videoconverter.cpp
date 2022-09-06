#include "videoconverter.h"
#include <cstring>


VideoConverter::VideoConverter()
{

}

VideoConverter::~VideoConverter()
{

}


void VideoConverter::yuyv_to_bgr24(const unsigned char *src, unsigned char *dest,
        int width, int height, int stride)
{
    int j;

    while (--height >= 0) {
        for (j = 0; j + 1 < width; j += 2) {
            int u = src[1];
            int v = src[3];
            int u1 = (((u - 128) << 7) +  (u - 128)) >> 6;
            int rg = (((u - 128) << 1) +  (u - 128) +
                    ((v - 128) << 2) + ((v - 128) << 1)) >> 3;
            int v1 = (((v - 128) << 1) +  (v - 128)) >> 1;

            *dest++ = CLIP(src[0] + u1);
            *dest++ = CLIP(src[0] - rg);
            *dest++ = CLIP(src[0] + v1);

            *dest++ = CLIP(src[2] + u1);
            *dest++ = CLIP(src[2] - rg);
            *dest++ = CLIP(src[2] + v1);
            src += 4;
        }
        src += stride - width * 2;
    }
}

void VideoConverter::yuyv_to_rgb24(const unsigned char *src, unsigned char *dest,
        int width, int height, int stride)
{
    int j;

    while (--height >= 0) {
        for (j = 0; j + 1 < width; j += 2) {
            int u = src[1];
            int v = src[3];
            int u1 = (((u - 128) << 7) +  (u - 128)) >> 6;
            int rg = (((u - 128) << 1) +  (u - 128) +
                    ((v - 128) << 2) + ((v - 128) << 1)) >> 3;
            int v1 = (((v - 128) << 1) +  (v - 128)) >> 1;

            *dest++ = CLIP(src[0] + v1);
            *dest++ = CLIP(src[0] - rg);
            *dest++ = CLIP(src[0] + u1);

            *dest++ = CLIP(src[2] + v1);
            *dest++ = CLIP(src[2] - rg);
            *dest++ = CLIP(src[2] + u1);
            src += 4;
        }
        src += stride - (width * 2);
    }
}

