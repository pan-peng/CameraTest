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

    frmBayer16.create(VIDEO_OUT_HEIGHT, VIDEO_OUT_WIDTH, CV_16UC1);
    frmRGB16.create(VIDEO_OUT_HEIGHT, VIDEO_OUT_WIDTH, CV_16UC3);
    frmRGB8.create(VIDEO_OUT_HEIGHT, VIDEO_OUT_WIDTH, CV_8UC3);

    pSrcBuf = new unsigned char [VIDEO_IN_WIDTH * VIDEO_IN_HEIGHT * VIDEO_IN_COLOR_DEPTH / 8];
    pDestBuf = new unsigned char [VIDEO_OUT_WIDTH * VIDEO_OUT_HEIGHT * 2];

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
    delete [] pDestBuf;
}

void VideoProcessor::startVideo()
{
    double fps_calculated;
    cv::TickMeter ticks;

    stopped = false;

    pVideo->Start();

    while (!stopped)
    {
        pause.lock();

        ticks.start();
        if (pVideo->Capture(pSrcBuf, VIDEO_IN_WIDTH * VIDEO_IN_HEIGHT * VIDEO_IN_COLOR_DEPTH / 8) == 0)
        {
            //Porcess
            dataConvertForYUYV(pSrcBuf, pDestBuf, VIDEO_IN_WIDTH * VIDEO_IN_HEIGHT * VIDEO_IN_COLOR_DEPTH / 8);

            memcpy(frmBayer16.data, pDestBuf, VIDEO_OUT_WIDTH * VIDEO_OUT_HEIGHT * 2);

            cv::cvtColor(frmBayer16, frmRGB16, cv::COLOR_BayerRG2BGR);  //BGGR

            cv::resize(frmRGB16, frmRGB16, cv::Size(VIDEO_OUT_WIDTH, VIDEO_OUT_HEIGHT));

            cv::convertScaleAbs(frmRGB16, frmRGB8, double(1.0 / 256), 0);

            ticks.stop();

            fps_calculated = ticks.getCounter() / ticks.getTimeSec();

            QDateTime time = QDateTime::currentDateTime();

            QString time_str = time.toString("yyyy-MM-dd hh:mm:ss");

            QString text = time_str + QString(" ") + QString::number(fps_calculated, 'f', 1) + QString("FPS");

            cv::putText(frmRGB8, text.toStdString(), cv::Point(10, 20), 2, 0.5, cv::Scalar(0,0,255));

            //Display
            //emit dispay(QPixmap::fromImage(QImage(pSrcBuf, VIDEO_WIDTH, VIDEO_HEIGHT, VIDEO_WIDTH * 3, QImage::Format_RGB888).rgbSwapped()));
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

void VideoProcessor::dataConvertForYUYV(const unsigned char *pSrcBuf, unsigned char *pDestBuf, unsigned int length)
{
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned short temp0 = 0;
    unsigned short temp1 = 0;
    unsigned short temp2 = 0;
    unsigned short temp3 = 0;

    if ((pSrcBuf == nullptr) || (pSrcBuf == nullptr) || (length == 0))
    {
        return ;
    }

    for (i = 0; i < length; i += 5, j += 8)
    {
        temp0 = static_cast<unsigned short>((pSrcBuf[i] << 2) | ((pSrcBuf[i + 4] & 0xc0) >> 6));
        temp1 = static_cast<unsigned short>((pSrcBuf[i + 1] << 2) | ((pSrcBuf[i + 4] & 0x30) >> 4));
        temp2 = static_cast<unsigned short>((pSrcBuf[i + 2] << 2) | ((pSrcBuf[i + 4] & 0x0c) >> 2));
        temp3 = static_cast<unsigned short>((pSrcBuf[i + 3] << 2) | (pSrcBuf[i + 4] & 0x03));

        pDestBuf[j] = static_cast<unsigned char>((temp0 >> 8) & 0xff);
        pDestBuf[j + 1] = static_cast<unsigned char>(temp0 & 0xff);
        pDestBuf[j + 2] = static_cast<unsigned char>((temp1 >> 8) & 0xff);
        pDestBuf[j + 3] = static_cast<unsigned char>(temp1 & 0xff);
        pDestBuf[j + 4] = static_cast<unsigned char>((temp2 >> 8) & 0xff);
        pDestBuf[j + 5] = static_cast<unsigned char>(temp2 & 0xff);
        pDestBuf[j + 6] = static_cast<unsigned char>((temp3 >> 8) & 0xff);
        pDestBuf[j + 7] = static_cast<unsigned char>(temp3 & 0xff);
    }
}

void VideoProcessor::dataConvertForRaw10(const unsigned char *pSrcBuf, unsigned char *pDestBuf, unsigned int length)
{
    unsigned int i = 0;
    unsigned int j = 0;

    if ((pSrcBuf == nullptr) || (pSrcBuf == nullptr) || (length == 0))
    {
        return ;
    }

    for (i = 0; i < length; i += 2, j += 2)
    {
        pDestBuf[j] = pSrcBuf[i + 1];
        pDestBuf[j + 1] = pSrcBuf[i];
    }
}


