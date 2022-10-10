#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QDebug>
#include <QThread>
#include "videoconfig.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pVideoSurface = new CaptureWindow(this);

    pProcessor = new VideoProcessor();

    pProcessor->moveToThread(new QThread(this));

    connect(pProcessor->thread(), SIGNAL(started()), pProcessor, SLOT(startVideo()));
    connect(pProcessor->thread(), SIGNAL(finished()), pProcessor, SLOT(deleteLater()));

    connect(pProcessor, SIGNAL(dispay(QPixmap)), pVideoSurface, SLOT(setFrame(QPixmap)));

}

MainWindow::~MainWindow()
{
    delete ui;

    if (!pProcessor->isVideoStopped())
    {
        pProcessor->stopVideo();
    }
    pProcessor->thread()->quit();
    pProcessor->thread()->wait();

    QThread::sleep(1);

    delete pVideoSurface;
    //delete pProcessor;
}

void MainWindow::on_btnStart_clicked()
{
    if (pProcessor->isVideoStopped())
    {
        pVideoSurface->setFrameSize(VIDEO_OUT_WIDTH, VIDEO_OUT_HEIGHT);
        pVideoSurface->show();

        pProcessor->thread()->start();
    }
}

void MainWindow::on_btnStop_clicked()
{
    if (!pProcessor->isVideoStopped())
    {
        pProcessor->stopVideo();
        pVideoSurface->hide();
    }

}

void MainWindow::on_btnResume_clicked()
{
    if (pProcessor->isVideoPaused())
    {
        pProcessor->resumeVideo();
    }
}

void MainWindow::on_btnPause_clicked()
{
    if (!pProcessor->isVideoPaused())
    {
        pProcessor->pauseVideo();
    }
}

void MainWindow::on_btnSet_clicked()
{
    int gain = 0;
    int exposure = 0;
    unsigned int frame_rate = 0;

    gain = ui->leGain->text().toInt();
    exposure = ui->leExp->text().toInt();
    frame_rate = ui->leFPS->text().toUInt();

    if (pProcessor->pVideo->SetGain(gain) == -1)
    {
        qDebug() << "Set gain failed.";
    }
    if (pProcessor->pVideo->SetExposure(exposure) == -1)
    {
        qDebug() << "Set exposure failed.";
    }
    if (pProcessor->pVideo->SetFrameRate(frame_rate) == -1)
    {
        qDebug() << "Set frame rate failed.";
    }

}
