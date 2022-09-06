QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    capturewindow.cpp \
    main.cpp \
    mainwindow.cpp \
    video.cpp \
    videoconverter.cpp \
    videoflip.cpp \
    videoprocessor.cpp

HEADERS += \
    capturewindow.h \
    mainwindow.h \
    video.h \
    videoconfig.h \
    videoconverter.h \
    videoflip.h \
    videoprocessor.h

FORMS += \
    capturewindow.ui \
    mainwindow.ui

INCLUDEPATH +=  /opt/opencv-4.1.1/include   \
                /opt/opencv-4.1.1/include/opencv4   \
                /opt/opencv-4.1.1/include/opencv4/opencv2

LIBS += /opt/opencv-4.1.1/lib/libopencv_highgui.so  \
        /opt/opencv-4.1.1/lib/libopencv_highgui.so.4.1.1  \
        /opt/opencv-4.1.1/lib/libopencv_core.so \
        /opt/opencv-4.1.1/lib/libopencv_imgproc.so  \
        /opt/opencv-4.1.1/lib/libopencv_imgcodecs.so    \
        /opt/opencv-4.1.1/lib/libopencv_videoio.so

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
