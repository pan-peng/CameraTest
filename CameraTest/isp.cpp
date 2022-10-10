#include "isp.h"

Isp::Isp()
{

}

Isp::~Isp()
{

}


cv::Mat Isp::whiteBalance(cv::Mat mat)
{
    std::vector <cv::Mat> imageRGB;
    cv::Mat image;
    double R, G, B;
    double KR, KG, KB;

    cv::split(mat, imageRGB);

    B = cv::mean(imageRGB[0])[0];
    G = cv::mean(imageRGB[1])[0];
    R = cv::mean(imageRGB[2])[0];

    KB = (R + G + B) / (3 * B);
    KG = (R + G + B) / (3 * G);
    KR = (R + G + B) / (3 * R);

    imageRGB[0] = imageRGB[0] * KB;
    imageRGB[1] = imageRGB[0] * KG;
    imageRGB[2] = imageRGB[0] * KR;

    cv::merge(imageRGB, image);

    return image;
}
