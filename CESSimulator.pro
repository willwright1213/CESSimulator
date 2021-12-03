QT       += core gui
QT       += testlib
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += testcase
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ces.cpp \
    loggingwidget.cpp \
    main.cpp \
    mainscreenwidget.cpp \
    mainwindow.cpp \
    recording.cpp \
    testcases.cpp \
    timer.cpp

HEADERS += \
    ces.h \
    loggingwidget.h \
    mainwindow.h \
    mainscreenwidget.h \
    recording.h \
    testcases.h \
    timer.h

FORMS += \
    loggingwidget.ui \
    mainscreenwidget.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc \
    sound.qrc
