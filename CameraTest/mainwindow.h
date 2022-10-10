#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSocketNotifier>
#include <QLabel>
#include <QVBoxLayout>
#include <QTimer>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include "capturewindow.h"
#include "videoprocessor.h"




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private:
    CaptureWindow *pVideoSurface;
    VideoProcessor *pProcessor;

private slots:
    void on_btnStart_clicked();

    void on_btnStop_clicked();
    void on_btnResume_clicked();
    void on_btnPause_clicked();
    void on_btnSet_clicked();
};
#endif // MAINWINDOW_H
