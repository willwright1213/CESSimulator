QT       += core gui
QT       += testlib
INCLUDEPATH += src
INCLUDEPATH += header
INCLUDEPATH += ui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += testcase
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

win32 {
    SOURCES += \
        src\ces.cpp \
        src\debugconsole.cpp \
        src\loggingwidget.cpp \
        src\main.cpp \
        src\mainscreenwidget.cpp \
        src\mainwindow.cpp \
        src\recording.cpp \
        src\testcases.cpp \
        src\timer.cpp

    HEADERS += \
        header\ces.h \
        header\debugconsole.h \
        header\loggingwidget.h \
        header\mainwindow.h \
        header\mainscreenwidget.h \
        header\recording.h \
        header\testcases.h \
        header\timer.h

    FORMS += \
        ui\debugconsole.ui \
        ui\loggingwidget.ui \
        ui\mainscreenwidget.ui \
        ui\mainwindow.ui
}

!win32 {
    SOURCES += \
        src/ces.cpp \
        src/debugconsole.cpp \
        src/loggingwidget.cpp \
        src/main.cpp \
        src/mainscreenwidget.cpp \
        src/mainwindow.cpp \
        src/recording.cpp \
        src/testcases.cpp \
        src/timer.cpp

    HEADERS += \
        header/ces.h \
        header/debugconsole.h \
        header/loggingwidget.h \
        header/mainwindow.h \
        header/mainscreenwidget.h \
        header/recording.h \
        header/testcases.h \
        header/timer.h

    FORMS += \
        ui/debugconsole.ui \
        ui/loggingwidget.ui \
        ui/mainscreenwidget.ui \
        ui/mainwindow.ui
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
