#ifndef VIDEOCONVERTER_H
#define VIDEOCONVERTER_H



#define CLIP(color) static_cast<unsigned char>(((color) > 0xFF) ? 0xff : (((color) < 0) ? 0 : (color)))


class VideoConverter
{
public:
    VideoConverter();
    ~VideoConverter();


public:
    void yuyv_to_bgr24(const unsigned char *src, unsigned char *dest,
            int width, int height, int stride);
    void yuyv_to_rgb24(const unsigned char *src, unsigned char *dest,
            int width, int height, int stride);

};

#endif // VIDEOCONVERTER_H
