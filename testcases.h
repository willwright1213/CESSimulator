/* ---------------------------------------------------------------------
 * File: testcases.h
 * Published: 2021-12-10
 *
 * authors:
 *      William Wright
 *      Soorya Balaji
 *      Anwar Kulane
 *      Mahmoud sabaayon
 *
 * dependencies:
        <QWidget>
        <QtTest/QtTest>
        mainwindow.h

 * The TestCases class is a series of test written to automate various test scenarios
 * To make sure the system complies with the requirements
 * ----------------------------------------------------------------------
 */
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
    //void resetIdleTimer();
    //void batteryDrainTest()
    //void batterySoundTest()
    void recordingTest();
    void loadRecordingTest();
};

#endif // TESTCASES_H
