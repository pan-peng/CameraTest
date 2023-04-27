/********************************************************************************
** Form generated from reading UI file 'capturewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAPTUREWINDOW_H
#define UI_CAPTUREWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_CaptureWindow
{
public:
    QLabel *lbCapture;

    void setupUi(QDialog *CaptureWindow)
    {
        if (CaptureWindow->objectName().isEmpty())
            CaptureWindow->setObjectName(QString::fromUtf8("CaptureWindow"));
        CaptureWindow->resize(800, 600);
        lbCapture = new QLabel(CaptureWindow);
        lbCapture->setObjectName(QString::fromUtf8("lbCapture"));
        lbCapture->setGeometry(QRect(0, 0, 67, 17));

        retranslateUi(CaptureWindow);

        QMetaObject::connectSlotsByName(CaptureWindow);
    } // setupUi

    void retranslateUi(QDialog *CaptureWindow)
    {
        CaptureWindow->setWindowTitle(QCoreApplication::translate("CaptureWindow", "Capture", nullptr));
        lbCapture->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CaptureWindow: public Ui_CaptureWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAPTUREWINDOW_H
