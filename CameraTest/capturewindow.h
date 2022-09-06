#ifndef CAPTUREWINDOW_H
#define CAPTUREWINDOW_H

#include <QDialog>
#include <QLabel>

namespace Ui {
class CaptureWindow;
}

class CaptureWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CaptureWindow(QWidget *parent = nullptr);
    ~CaptureWindow();

private:
    Ui::CaptureWindow *ui;

public slots:
    void setFrame(QPixmap pixmap);

public:
    void setFrameSize(QSize size);
    void setFrameSize(int w, int h);
};

#endif // CAPTUREWINDOW_H
