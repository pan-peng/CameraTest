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

private:
    Video *pVideo;
    VideoConverter *pVideoConverter;
    VideoFlip *pVideoFlip;
    cv::Mat frmBayer16;
    cv::Mat frmRGB16;
    cv::Mat frmRGB8;
    bool stopped;
    unsigned char *pSrcBuf;
    unsigned char *pDestBuf;
    QMutex pause;
    bool paused;

private:
    void dataConvertForYUYV(const unsigned char *pSrcBuf, unsigned char *pDestBuf, unsigned int length);
    void dataConvertForRaw10(const unsigned char *pSrcBuf, unsigned char *pDestBuf, unsigned int length);
};


#endif // VIDEOPROCESSOR_H
