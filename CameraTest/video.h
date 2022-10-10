#ifndef VIDEO_H
#define VIDEO_H


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>
#include <sys/mman.h>
#include <string.h>
#include <linux/fb.h>
#include <memory.h>
#include <errno.h>


class Video
{
public:
    Video();
    Video(unsigned int n);
    ~Video();

private:
    int fd;
    unsigned int count;
    unsigned char **pMem;
    unsigned int *pLength;

public:
    int Open(const char *dev, unsigned int width, unsigned int height, unsigned int pixel_format);
    int Start(void);
    int Stop(void);
    int Capture(unsigned char *pBuf, unsigned int frame_size);
    int Close(void);
    int Xioctl(int fd, unsigned long int request, void *arg);
    int SetGain(int gain);
    int SetExposure(int exposure);
    int SetFrameRate(unsigned int frame_rate);

};


#endif // VIDEO_H
