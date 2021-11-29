#ifndef TESTCASES_H
#define TESTCASES_H

#include <QWidget>
#include <QVector>
#include <QtTest/QtTest>
#include "mainwindow.h"



class TestCases : public QObject
{
    Q_OBJECT
private:
    MainWindow *w;
    void setValues();
private slots:
    void initTestCase();
    void init();
    void cleanupTestCase();
    void cleanup();
    void defaultStateTest();
    void resetToDefaultTest();
    void ampButtonPressTest();
    void timerButtonPressTest();
    void waveButtonPressTest();
    void freqButtonPressTest();
    void startTimeUiTest();
    void ampUiTest();
    void waveUiTest();
    void freqUiTest();
    void lockUiTest();
    void recUiTest();
    void lockTest();
    void amperageOverloadTest();
    void startPauseClockTest();
    void clockUpdatesUiTest();
    void testIdleTimer();
};

#endif // TESTCASES_H
