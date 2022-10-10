#ifndef VIDEOPROCESSOR_H
#define VIDEOPROCESSOR_H

#include <QMainWindow>
#include <QPixmap>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <QMutex>
#include "video.h"
#include "videoconverter.h"
#include "videoflip.h"
#include "isp.h"


class VideoProcessor : public QObject
{
    Q_OBJECT

public:
    VideoProcessor();
    ~VideoProcessor();

signals:
    void dispay(QPixmap pixmap);

public slots:
    void startVideo(void);
    void stopVideo(void);

public:
    bool isVideoStopped(void);
    bool isVideoPaused(void);
    void pauseVideo(void);
    void resumeVideo(void);

public:
    Video *pVideo;
    VideoConverter *pVideoConverter;
    VideoFlip *pVideoFlip;
    Isp *pIsp;

private:

    cv::Mat frmBayer16;
    cv::Mat frmRGB16;
    cv::Mat frmRGB8;
    bool stopped;
    unsigned char *pSrcBuf;
    unsigned short *pDestBuf16;
    unsigned char *pDestBuf8;
    QMutex pause;
    bool paused;

private:
    void dataConvertForYUYV(const unsigned char *pSrcBuf, unsigned short *pDestBuf, unsigned int length);
    void dataConvertForRaw10(const unsigned char *pSrcBuf, unsigned short *pDestBuf, unsigned int length);

    void int2Byte(const unsigned short *pSrcBuf, unsigned char *pDestBuf, unsigned int length);
};


#endif // VIDEOPROCESSOR_H
