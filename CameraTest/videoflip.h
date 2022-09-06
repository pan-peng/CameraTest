#ifndef VIDEOFLIP_H
#define VIDEOFLIP_H


class VideoFlip
{
public:
    VideoFlip();
    ~VideoFlip();

public:
    void rotate90_rgbbgr24(const unsigned char *src,
            unsigned char *dst, int destwidth, int destheight);
    void rotate180_rgbbgr24(const unsigned char *src,
            unsigned char *dst, int width, int height);
    void hflip_rgbbgr24(unsigned char *src, unsigned char *dest,
            int width, int height, int stride);
    void vflip_rgbbgr24(const unsigned char *src, unsigned char *dest,
            int width, int height, int stride);
};

#endif // VIDEOFLIP_H
