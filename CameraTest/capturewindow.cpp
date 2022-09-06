#include "capturewindow.h"
#include "ui_capturewindow.h"

CaptureWindow::CaptureWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CaptureWindow)
{
    ui->setupUi(this);

}

CaptureWindow::~CaptureWindow()
{
    delete ui;
}

void CaptureWindow::setFrame(QPixmap pixmap)
{
    ui->lbCapture->setPixmap(pixmap);

}

void CaptureWindow::setFrameSize(QSize size)
{
    resize(size);
    ui->lbCapture->resize(size);
}

void CaptureWindow::setFrameSize(int w, int h)
{
    resize(QSize(w, h));
    ui->lbCapture->resize(QSize(w, h));
}
