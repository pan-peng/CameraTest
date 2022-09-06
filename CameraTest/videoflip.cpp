#include "videoflip.h"
#include <cstring>


VideoFlip::VideoFlip()
{

}

VideoFlip::~VideoFlip()
{

}

void VideoFlip::rotate90_rgbbgr24(const unsigned char *src,
        unsigned char *dst, int destwidth, int destheight)
{
    int x, y;
#define srcwidth destheight
#define srcheight destwidth

    for (y = 0; y < destheight; y++)
        for (x = 0; x < destwidth; x++) {
            int offset = ((srcheight - x - 1) * srcwidth + y) * 3;
            *dst++ = src[offset++];
            *dst++ = src[offset++];
            *dst++ = src[offset];
        }
}

void VideoFlip::rotate180_rgbbgr24(const unsigned char *src,
        unsigned char *dst, int width, int height)
{
    int i;

    src += 3 * width * height - 3;

    for (i = 0; i < width * height; i++) {
        dst[0] = src[0];
        dst[1] = src[1];
        dst[2] = src[2];
        dst += 3;
        src -= 3;
    }
}

void VideoFlip::hflip_rgbbgr24(unsigned char *src, unsigned char *dest,
        int width, int height, int stride)
{
    int x, y;

    for (y = 0; y < height; y++) {
        src += width * 3;
        for (x = 0; x < width; x++) {
            src -= 3;
            dest[0] = src[0];
            dest[1] = src[1];
            dest[2] = src[2];
            dest += 3;
        }
        src += stride;
    }
}

void VideoFlip::vflip_rgbbgr24(const unsigned char *src, unsigned char *dest,
        int width, int height, int stride)
{
    int y;

    src += height * stride;
    for (y = 0; y < height; y++) {
        src -= stride;
        memcpy(dest, src, width * 3);
        dest += width * 3;
    }
}

