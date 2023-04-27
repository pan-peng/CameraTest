/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *btnStart;
    QPushButton *btnStop;
    QPushButton *btnResume;
    QPushButton *btnPause;
    QGroupBox *groupBox;
    QPushButton *btnSet;
    QLineEdit *leGain;
    QLineEdit *leFPS;
    QLabel *lbFPS;
    QLabel *lbGain;
    QLineEdit *leExp;
    QLabel *lbExp;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        btnStart = new QPushButton(centralwidget);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));
        btnStart->setGeometry(QRect(540, 120, 89, 25));
        btnStop = new QPushButton(centralwidget);
        btnStop->setObjectName(QString::fromUtf8("btnStop"));
        btnStop->setGeometry(QRect(540, 240, 89, 25));
        btnResume = new QPushButton(centralwidget);
        btnResume->setObjectName(QString::fromUtf8("btnResume"));
        btnResume->setGeometry(QRect(540, 200, 89, 25));
        btnPause = new QPushButton(centralwidget);
        btnPause->setObjectName(QString::fromUtf8("btnPause"));
        btnPause->setGeometry(QRect(540, 160, 89, 25));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(30, 30, 361, 241));
        btnSet = new QPushButton(groupBox);
        btnSet->setObjectName(QString::fromUtf8("btnSet"));
        btnSet->setGeometry(QRect(240, 180, 89, 25));
        leGain = new QLineEdit(groupBox);
        leGain->setObjectName(QString::fromUtf8("leGain"));
        leGain->setGeometry(QRect(90, 40, 113, 25));
        leFPS = new QLineEdit(groupBox);
        leFPS->setObjectName(QString::fromUtf8("leFPS"));
        leFPS->setGeometry(QRect(90, 120, 113, 25));
        lbFPS = new QLabel(groupBox);
        lbFPS->setObjectName(QString::fromUtf8("lbFPS"));
        lbFPS->setGeometry(QRect(40, 120, 31, 17));
        lbGain = new QLabel(groupBox);
        lbGain->setObjectName(QString::fromUtf8("lbGain"));
        lbGain->setGeometry(QRect(40, 40, 41, 17));
        leExp = new QLineEdit(groupBox);
        leExp->setObjectName(QString::fromUtf8("leExp"));
        leExp->setGeometry(QRect(90, 80, 113, 25));
        lbExp = new QLabel(groupBox);
        lbExp->setObjectName(QString::fromUtf8("lbExp"));
        lbExp->setGeometry(QRect(40, 80, 31, 17));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btnStart->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        btnStop->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
        btnResume->setText(QCoreApplication::translate("MainWindow", "Resume", nullptr));
        btnPause->setText(QCoreApplication::translate("MainWindow", "Pause", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Params", nullptr));
        btnSet->setText(QCoreApplication::translate("MainWindow", "Set", nullptr));
        lbFPS->setText(QCoreApplication::translate("MainWindow", "FPS", nullptr));
        lbGain->setText(QCoreApplication::translate("MainWindow", "Gain", nullptr));
        lbExp->setText(QCoreApplication::translate("MainWindow", "Exp", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
