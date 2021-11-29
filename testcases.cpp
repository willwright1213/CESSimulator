#include <QDebug>
#include <QRandomGenerator>
#include "testcases.h"
#include "cesexception.h"
#include <QThread>
/* Global variables used to randomize selection for test case */
const int amps = QRandomGenerator::global()->bounded(11) * 50;
const int startTime = QRandomGenerator::global()->bounded(3);
const int wave = QRandomGenerator::global()->bounded(3);
const int freq = QRandomGenerator::global()->bounded(3);

void TestCases::setValues() {
    w->ces->setAmperage(amps);
    w->ces->setStartTime(startTime);
    w->ces->setWave(wave);
    w->ces->setFrequency(freq);
}

void TestCases::initTestCase() {
    QThreadPool::globalInstance()->setMaxThreadCount(5);
    qDebug("==== Starting Test Cases ====");
    w = new MainWindow;
    QVERIFY(w->ces->powerStatus == false);
    QVERIFY(w->ces->selectedScreen == nullptr);
}

void TestCases::init() {
    emit w->powerButton()->pressed();
}

void TestCases::cleanup() {
    emit w->powerButton()->pressed();
}


void TestCases::cleanupTestCase() {
   // QVERIFY(w->ces->powerStatus == false);
   // QVERIFY(w->ces->selectedScreen == nullptr);
    delete w;
}

/*!
 * Checks if the CES starts as off and initialize values correctly
 */
void TestCases::defaultStateTest() {
    QVERIFY(w->ces->powerStatus == true);
    QVERIFY(w->ces->selectedScreen == w->ces->mainScreen);
    QVERIFY(w->ces->selectedTime == 2);
    QVERIFY(w->ces->timer == 3600);
    QVERIFY(w->ces->selectedFreq == 0);
    QVERIFY(w->ces->selectedWave == 0);
    QVERIFY(w->ces->microAmps == 0);
    QVERIFY(w->ces->isLocked == false);
    QVERIFY(w->ces->isRecording == false);
}

/*!
 * check that values are reset to default after powering it on/off
 */
void TestCases::resetToDefaultTest() {
    setValues();
    w->ces->toggleLock();
    w->ces->togglePower();
    w->ces->togglePower();
    defaultStateTest();
}

void TestCases::ampButtonPressTest() {
    emit w->upButton()->pressed();
    QVERIFY(w->ces->microAmps == 50);
    emit w->downButton()->pressed();
    emit w->downButton()->pressed();
    QVERIFY(w->ces->microAmps == 0);
    w->ces->setAmperage(500);
    emit w->upButton()->pressed();
    QVERIFY(w->ces->microAmps == 500);
}

void TestCases::timerButtonPressTest() {
    int st = w->ces->selectedTime;
    emit w->timerButton()->pressed();
    QVERIFY(w->ces->selectedTime == (st + 1) % 3);
}

void TestCases::waveButtonPressTest() {
    int wa = w->ces->selectedWave;
    emit w->waveButton()->pressed();
    QVERIFY(w->ces->selectedWave == (wa + 1) % 3);
}

void TestCases::freqButtonPressTest() {
    int f = w->ces->selectedFreq;
    emit w->frequencyButton()->pressed();
    QVERIFY(w->ces->selectedFreq == (f + 1) % 3);
}

void TestCases::startTimeUiTest() {
    setValues();
    int secs = (startTime * 20 + 20) * 60; 
    for(int i = 0; i < 3; i ++) {

        if(i == startTime) {
            QVERIFY(w->ces->mainScreen->timerLabels[i]->styleSheet() ==
                    "color: #1b1b1b; font-size: 14pt; text-decoration: underline;");
        }
        else
            QVERIFY(w->ces->mainScreen->timerLabels[i]->styleSheet() ==
                    "color: #bfbfbf; font-size: 14pt;");
    }
    //check the clock label
    QString mString = QString::number(secs / 60).rightJustified(2, '0');
    QString sString = QString::number(secs % 60).rightJustified(2, '0');
    QVERIFY((w->ces->mainScreen->clockLabel()->text() == mString + ":" + sString));
}

void TestCases::ampUiTest() {
    setValues();
    for(int i = 0; i < 10; i++) {
        if(i < amps/50)
            QVERIFY(w->ces->mainScreen->bars[i]->styleSheet() ==
                    "background:  #1b1b1b;");
        else
            QVERIFY(w->ces->mainScreen->bars[i]->styleSheet() ==
                    "border: 1px solid #1b1b1b;");
    }
}

void TestCases::waveUiTest() {
    setValues();
    for(int i = 0; i < 3; i ++) {
        if(i == wave)
            QVERIFY(w->ces->mainScreen->waveLabels[i]->styleSheet() ==
                    "color: #1b1b1b; font-size: 10pt; text-decoration: underline;");
        else
            QVERIFY(w->ces->mainScreen->waveLabels[i]->styleSheet() ==
                    "color: #bfbfbf; font-size: 10pt;");
    }
}

void TestCases::freqUiTest() {
    setValues();
    for(int i = 0; i < 3; i ++) {
        if(i == freq)
            QVERIFY(w->ces->mainScreen->freqLabels[i]->styleSheet() ==
                    "color: #1b1b1b; font-size: 10pt; text-decoration: underline;");
        else
            QVERIFY(w->ces->mainScreen->freqLabels[i]->styleSheet() ==
                    "color: #bfbfbf; font-size: 10pt;");
    }
}

void TestCases::startPauseClockTest() {
    QVERIFY2(w->ces->clockTimer->isPaused && !w->ces->clipStatus, "Clock is not running if clip status is off");
    emit w->clipperButton()->pressed();
    QVERIFY2(!w->ces->clockTimer->isPaused && w->ces->clipStatus, "Clock is running when clipper is on");
    emit w->powerButton()->pressed();
    QVERIFY2(w->ces->clockTimer->isPaused, "clock is paused when power is off");
    emit w->powerButton()->pressed();
    QVERIFY2(!w->ces->clockTimer->isPaused && w->ces->clipStatus, "clock resumes when power turns on");
    emit w->clipperButton()->pressed();
}

void TestCases::clockUpdatesUiTest() {
    emit w->clipperButton()->pressed();
    int t1 = w->ces->timer;
    QTRY_VERIFY_WITH_TIMEOUT(t1 != w->ces->timer, 10);
    emit w->clipperButton()->pressed();
}

void TestCases::amperageOverloadTest() {
    w->ces->setAmperage(750);
    QVERIFY2(!w->ces->powerStatus, "amperage overload shutdown");
    emit w->powerButton()->pressed();
}

void TestCases::testIdleTimer() {
    w->ces->idleTimer->setTimer(60);
    QTRY_VERIFY_WITH_TIMEOUT(!w->ces->powerStatus, 600);
    emit w->powerButton()->pressed();
}

void TestCases::lockUiTest() {
    QVERIFY(w->ces->mainScreen->lockIcon()->styleSheet() == "");
    emit w->lockButton()->pressed();
    QVERIFY(w->ces->mainScreen->lockIcon()->styleSheet() == "border-image: url(:/images/icons8-lock-24.png)");
}

void TestCases::recUiTest() {
    QVERIFY(w->ces->mainScreen->recIcon()->styleSheet() == "");
    emit w->recordButton()->pressed();
    QVERIFY(w->ces->mainScreen->recIcon()->styleSheet() == "border-image: url(:/images/rec.png)");
    emit w->recordButton()->pressed();
}

void TestCases::lockTest() {
    qDebug() << w->ces->selectedTime;
    emit w->lockButton()->pressed();
    emit w->timerButton()->pressed();
    emit w->waveButton()->pressed();
    emit w->upButton()->pressed();
    emit w->frequencyButton()->pressed();
    emit w->recordButton()->pressed();
    emit w->logButton()->pressed();
    emit w->lockButton()->pressed();
    defaultStateTest();
    QVERIFY(w->ces->selectedScreen == w->ces->mainScreen);
}
