#include "video.h"


Video::Video()
{
    count = 5;
    pMem = new unsigned char * [count];
    pLength = new unsigned int [count];
}


Video::Video(unsigned int n)
{
    count = n;
    pMem = new unsigned char * [count];
    pLength = new unsigned int [count];
}


Video::~Video()
{
    delete [] pMem;
    delete [] pLength;
}


int Video::Open(const char *dev, unsigned int width, unsigned int height, unsigned int pixel_format)
{  
    unsigned char *p = nullptr;
    struct v4l2_capability cap;
    struct v4l2_fmtdesc video_info;
    struct v4l2_frmsizeenum supportSizes;
    struct v4l2_format video_fmt;
    struct v4l2_requestbuffers reqbuffer;
    struct v4l2_buffer mapbuffer;
    unsigned int i;
    int ret = 0;

    if ((dev == nullptr) || (width == 0) || (height == 0))
    {
        return -1;
    }

    //Open video
    fd = open(dev, O_RDWR/* | O_NONBLOCK */);
    if (fd < 0)
    {
        perror("Open video failed!\n");
        return -1;
    }

    //Get video cap
    memset(&cap, 0, sizeof(cap));
    ret = Xioctl(fd, VIDIOC_QUERYCAP, &cap);
    if (ret < 0)
    {
        perror("Get video cap failed!\n");
        return -1;
    }
    printf("version:%d,device info:%s\n", cap.version, cap.driver);
    if (cap.capabilities & V4L2_CAP_VIDEO_CAPTURE)
    {
        printf("Video support capture\n");
    }
    if (cap.capabilities & V4L2_CAP_STREAMING)
    {
        printf("Video support steaming capture\n");
    }

    //Get video info
    memset(&video_info, 0, sizeof(video_info));
    memset(&supportSizes, 0, sizeof(supportSizes));
    video_info.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    video_info.index = 0;
    while (Xioctl(fd, VIDIOC_ENUM_FMT, &video_info) != -1)
    {
        supportSizes.pixel_format = video_info.pixelformat;
        supportSizes.index = 0;
        while (Xioctl(fd, VIDIOC_ENUM_FRAMESIZES, &supportSizes) != -1)
        {
            printf("Video index:%d,format:%s,size with:%d,height:%d\n", video_info.index, video_info.description, supportSizes.discrete.width, supportSizes.discrete.height);
            p = static_cast<unsigned char *>(static_cast<void *>(&video_info.pixelformat));
            printf("Video pixelformat:%c%c%c%c\n", p[0], p[1], p[2], p[3]);
            supportSizes.index++;
        }
        video_info.index++;
    }

    //Set video format
    memset(&video_fmt, 0, sizeof(video_fmt));
    video_fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    video_fmt.fmt.pix.width = width;
    video_fmt.fmt.pix.height = height;
    video_fmt.fmt.pix.pixelformat = pixel_format;
    video_fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;
    ret = Xioctl(fd, VIDIOC_S_FMT, &video_fmt);
    if (ret < 0)
    {
        perror("Set video format failed!\n");
        return -1;
    }

    //Require buffer
    reqbuffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    reqbuffer.count = count;
    reqbuffer.memory = V4L2_MEMORY_MMAP;
    ret = Xioctl(fd, VIDIOC_REQBUFS, &reqbuffer);
    if (ret < 0)
    {
        perror("Request video queue buf failed!\n");
        return -1;
    }

    //Remap to user space
    mapbuffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    mapbuffer.memory = V4L2_MEMORY_MMAP;
    for (i = 0; i < count; i++)
    {
        mapbuffer.index = i;
        ret = Xioctl(fd, VIDIOC_QUERYBUF, &mapbuffer);
        if (ret < 0)
        {
            perror("Kernel query buf failed!\n");
            return -1;
        }
        pMem[i] = static_cast<unsigned char *>(mmap(nullptr, mapbuffer.length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, mapbuffer.m.offset));
        pLength[i] = mapbuffer.length;
        ret = Xioctl(fd, VIDIOC_QBUF, &mapbuffer);
        if (ret < 0)
        {
            perror("Video put buffer failed!\n");
            return -1;
        }
    }

    return 0;
}


int Video::Start(void)
{
    int type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    return Xioctl(fd, VIDIOC_STREAMON, &type);
}


int Video::Stop(void)
{
    int type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    return Xioctl(fd, VIDIOC_STREAMOFF, &type);
}


int Video::Capture(unsigned char *pBuf, unsigned int frame_size)
{
    struct v4l2_buffer readbuffer;
    int ret = 0;

    if (pBuf == nullptr)
    {
        return -1;
    }

    readbuffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    ret = Xioctl(fd, VIDIOC_DQBUF, &readbuffer);
    if (ret < 0)
    {
        perror("Video get buffer failed!\n");
        return -1;
    }

    memcpy(pBuf, pMem[readbuffer.index], frame_size);

    ret = Xioctl(fd, VIDIOC_QBUF, &readbuffer);
    if (ret < 0)
    {
        perror("Video put buffer failed!\n");
        return -1;
    }

    return 0;
}


int Video::Close(void)
{
    unsigned int i = 0;

    //Unmap mem
    for (i = 0; i < count; i++)
    {
        munmap(pMem[i], pLength[i]);
    }

    return close(fd);
}

int Video::Xioctl(int fd, unsigned long int request, void *arg)
{
    int r;

    do
    {
        r = ioctl (fd, request, arg);
    }while ((-1 == r) && (EINTR == errno));

    return r;
}

int Video::SetGain(int gain)
{
    struct v4l2_control ctrl;

    memset(&ctrl, 0, sizeof(ctrl));
    ctrl.id = V4L2_CID_GAIN;
    ctrl.value = gain;

    return Xioctl(fd, VIDIOC_S_CTRL, &ctrl);
}


int Video::SetExposure(int exposure)
{
    struct v4l2_control ctrl;

    memset(&ctrl, 0, sizeof(ctrl));
    ctrl.id = V4L2_CID_EXPOSURE;
    ctrl.value = exposure;

    return Xioctl(fd, VIDIOC_S_CTRL, &ctrl);
}


int Video::SetFrameRate(unsigned int frame_rate)
{
    struct v4l2_streamparm stream_param;

    memset(&stream_param, 0, sizeof(stream_param));
    stream_param.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    stream_param.parm.capture.timeperframe.numerator = 1;
    stream_param.parm.capture.timeperframe.denominator = frame_rate;

    return Xioctl(fd, VIDIOC_S_PARM, &stream_param);
}

