#include "videoprocessor.h"
#include <QDebug>
#include "videoconfig.h"
#include <QDateTime>



VideoProcessor::VideoProcessor()
{
    stopped = true;
    paused = false;
    pVideo = new Video();
    pVideoConverter = new VideoConverter();
    pVideoFlip = new VideoFlip();
    pIsp = new Isp();

    frmBayer16.create(VIDEO_OUT_HEIGHT, VIDEO_OUT_WIDTH, CV_16UC1);
    frmRGB16.create(VIDEO_OUT_HEIGHT, VIDEO_OUT_WIDTH, CV_16UC3);
    frmRGB8.create(VIDEO_OUT_HEIGHT, VIDEO_OUT_WIDTH, CV_8UC3);

    pSrcBuf = new unsigned char [VIDEO_IN_WIDTH * VIDEO_IN_HEIGHT * VIDEO_IN_COLOR_DEPTH / 8];
    pDestBuf16 = new unsigned short [VIDEO_OUT_WIDTH * VIDEO_OUT_HEIGHT];
    pDestBuf8 = new unsigned char [VIDEO_OUT_WIDTH * VIDEO_OUT_HEIGHT * 2];

    if (pVideo->Open("/dev/video0", VIDEO_IN_WIDTH, VIDEO_IN_HEIGHT, VIDEO_IN_FMT) != 0)
    {
        qDebug() << "Video open failed!";
    }
}

VideoProcessor::~VideoProcessor()
{
    pVideo->Stop();
    pVideo->Close();

    frmBayer16.release();
    frmRGB16.release();
    frmRGB8.release();

    delete [] pSrcBuf;
    delete [] pDestBuf16;
    delete [] pDestBuf8;
}

void VideoProcessor::startVideo()
{
    double fps_calculated;
    cv::TickMeter ticks;
    unsigned int frameSize;

    frameSize = VIDEO_IN_WIDTH * VIDEO_IN_HEIGHT * VIDEO_IN_COLOR_DEPTH / 8;

    stopped = false;

    pVideo->Start();

    while (!stopped)
    {
        pause.lock();

        ticks.start();
        if (pVideo->Capture(pSrcBuf, frameSize) == 0)
        {
            //Porcess
            dataConvertForYUYV(pSrcBuf, pDestBuf16, frameSize);

            int2Byte(pDestBuf16, pDestBuf8, VIDEO_OUT_WIDTH * VIDEO_OUT_HEIGHT);

            memcpy(frmBayer16.data, pDestBuf8, VIDEO_OUT_WIDTH * VIDEO_OUT_HEIGHT * 2);

            cv::cvtColor(frmBayer16, frmRGB16, cv::COLOR_BayerRG2BGR);  //BGGR
            //cv::demosaicing(frmBayer16, frmRGB16, cv::COLOR_BayerRG2BGR);  //BGGR

            cv::resize(frmRGB16, frmRGB16, cv::Size(VIDEO_OUT_WIDTH, VIDEO_OUT_HEIGHT));

            cv::convertScaleAbs(frmRGB16, frmRGB8, double(1.0 / 256), 0);

            ticks.stop();

            fps_calculated = ticks.getCounter() / ticks.getTimeSec();

            QDateTime time = QDateTime::currentDateTime();

            QString time_str = time.toString("yyyy-MM-dd hh:mm:ss");

            QString text = time_str + QString(" ") + QString::number(fps_calculated, 'f', 1) + QString("FPS");

            cv::putText(frmRGB8, text.toStdString(), cv::Point(10, 20), cv::FONT_HERSHEY_DUPLEX, 0.5, cv::Scalar(0,0,255));

            //Display
            //emit dispay(QPixmap::fromImage(QImage(pSrcBuf, VIDEO_OUT_WIDTH, VIDEO_OUT_HEIGHT, VIDEO_OUT_WIDTH * 3, QImage::Format_RGB888).rgbSwapped()));
            emit dispay(QPixmap::fromImage(QImage(frmRGB8.data, frmRGB8.cols, frmRGB8.rows, static_cast<int>(frmRGB8.step), QImage::Format_RGB888).rgbSwapped()));
        }
        else
        {
            qDebug() << "Capture failed!";
        }
        pause.unlock();
        usleep(1000);  //1ms
    }
}

void VideoProcessor::stopVideo()
{
    stopped = true;
}

bool VideoProcessor::isVideoStopped()
{
    return stopped;
}

bool VideoProcessor::isVideoPaused()
{
    return paused;
}

void VideoProcessor::pauseVideo()
{
    pause.lock();
    paused = true;
}

void VideoProcessor::resumeVideo()
{
    pause.unlock();
    paused = false;
}

void VideoProcessor::dataConvertForYUYV(const unsigned char *pSrcBuf, unsigned short *pDestBuf, unsigned int length)
{
    unsigned int i = 0;

    if ((pSrcBuf == nullptr) || (pDestBuf == nullptr) || (length == 0))
    {
        return ;
    }

    for (i = 0; i < length; i += 5)
    {
        pDestBuf[i * 4 / 5] = static_cast<unsigned short>((pSrcBuf[i] << 2) | (pSrcBuf[i + 4] & 0x03));
        if (pDestBuf[i * 4 / 5] > VIDEO_PIXEL_MAX_VALUE)
        {
            pDestBuf[i * 4 / 5] = VIDEO_PIXEL_MAX_VALUE;
        }
        pDestBuf[i * 4 / 5 + 1] = static_cast<unsigned short>((pSrcBuf[i + 1] << 2) | ((pSrcBuf[i + 4] & 0x0c) >> 2));
        if (pDestBuf[i * 4 / 5 + 1] > VIDEO_PIXEL_MAX_VALUE)
        {
            pDestBuf[i * 4 / 5 + 1] = VIDEO_PIXEL_MAX_VALUE;
        }
        pDestBuf[i * 4 / 5 + 2] = static_cast<unsigned short>((pSrcBuf[i + 2] << 2) | ((pSrcBuf[i + 4] & 0x30) >> 4));
        if (pDestBuf[i * 4 / 5 + 2] > VIDEO_PIXEL_MAX_VALUE)
        {
            pDestBuf[i * 4 / 5 + 2] = VIDEO_PIXEL_MAX_VALUE;
        }
        pDestBuf[i * 4 / 5 + 3] = static_cast<unsigned short>((pSrcBuf[i + 3] << 2) | ((pSrcBuf[i + 4] & 0xc0) >> 6));
        if (pDestBuf[i * 4 / 5 + 3] > VIDEO_PIXEL_MAX_VALUE)
        {
            pDestBuf[i * 4 / 5 + 3] = VIDEO_PIXEL_MAX_VALUE;
        }
    }
}

void VideoProcessor::dataConvertForRaw10(const unsigned char *pSrcBuf, unsigned char *pDestBuf, unsigned int length)
{
    unsigned int i = 0;
    unsigned short temp = 0;

    if ((pSrcBuf == nullptr) || (pDestBuf == nullptr) || (length == 0))
    {
        return ;
    }

    for (i = 0; i < length; i++)
    {
        pDestBuf[i] = pSrcBuf[i * 2 + 1];  //Swap byte order
        pDestBuf[i + 1] = pSrcBuf[i * 2];
        temp = static_cast<unsigned short>(pDestBuf[i] << 8 | pDestBuf[i + 1]);
        if (temp > VIDEO_PIXEL_MAX_VALUE)
        {
            temp = VIDEO_PIXEL_MAX_VALUE;
            pDestBuf[i] = static_cast<unsigned char>((temp >> 8) & 0xff);
            pDestBuf[i + 1] = static_cast<unsigned char>(temp & 0xff);
        }
    }
}

void VideoProcessor::int2Byte(const unsigned short *pSrcBuf, unsigned char *pDestBuf, unsigned int length)
{
    unsigned int i = 0;

    if ((pSrcBuf == nullptr) || (pDestBuf == nullptr) || (length == 0))
    {
        return ;
    }

    for (i = 0; i < length; i++)
    {
        pDestBuf[i * 2] = static_cast<unsigned char>((pSrcBuf[i] >> 8) & 0xff);
        pDestBuf[i * 2 + 1] = static_cast<unsigned char>(pSrcBuf[i] & 0xff);
    }
}

