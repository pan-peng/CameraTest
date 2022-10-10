#ifndef ISP_H
#define ISP_H

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>


class Isp
{
public:
    Isp();
    ~Isp();

public:
    cv::Mat whiteBalance(cv::Mat mat);
};

#endif // ISP_H
