#include <QDebug>
#include <QRandomGenerator>
#include "testcases.h"
#include "cesexception.h"

/* Global variables used to randomize selection for test case */
const int amps = QRandomGenerator::global()->bounded(11) * 50;
const int startTime = QRandomGenerator::global()->bounded(2);
const int wave = QRandomGenerator::global()->bounded(2);
const int freq = QRandomGenerator::global()->bounded(2);

void TestCases::setValues() {
    w->getCES()->setValue(AMP, amps);
    w->getCES()->setValue(TIME, startTime);
    w->getCES()->setValue(WAVE, wave);
    w->getCES()->setValue(FREQ, freq);
}

void TestCases::initTestCase() {
    qDebug("==== Starting Test Cases ====");
    w = new MainWindow;
    QVERIFY(w->getCES()->getPowerStatus() == false);
    QVERIFY(w->getCES()->getSelectedScreen() == nullptr);
}

void TestCases::init() {
    emit w->powerButton()->pressed();
}

void TestCases::cleanup() {
    emit w->powerButton()->pressed();
}


void TestCases::cleanupTestCase() {
    QVERIFY(w->getCES()->getPowerStatus() == false);
    QVERIFY(w->getCES()->getSelectedScreen() == nullptr);
    delete w;
}

/*!
 * Checks if the CES starts as off and initialize values correctly
 */
void TestCases::defaultStateTest() {
    QVERIFY(w->getCES()->getPowerStatus() == true);
    QVERIFY(w->getCES()->getSelectedScreen() == w->getCES()->getMainScreen());
    QVERIFY(w->getCES()->getPowerStatus() == true);
    QVERIFY(w->getCES()->getStartTime() == 2);
    QVERIFY(w->getCES()->getTime() == 3600);
    QVERIFY(w->getCES()->getFreq() == 0);
    QVERIFY(w->getCES()->getWave() == 0);
    QVERIFY(w->getCES()->getAmps() == 0);
}

/*!
 * check that values are reset to default after powering it on/off
 */
void TestCases::resetToDefaultTest() {
    setValues();
    w->getCES()->togglePower();
    w->getCES()->togglePower();
    defaultStateTest();
}

void TestCases::ampButtonPressTest() {
    emit w->upButton()->pressed();
    QVERIFY(w->getCES()->getAmps() == 50);
    emit w->downButton()->pressed();
    emit w->downButton()->pressed();
    QVERIFY(w->getCES()->getAmps() == 0);
    w->getCES()->setValue(AMP, 500);
    emit w->upButton()->pressed();
    QVERIFY(w->getCES()->getAmps() == 500);
}

void TestCases::timerButtonPressTest() {
    int st = w->getCES()->getStartTime();
    emit w->timerButton()->pressed();
    QVERIFY(w->getCES()->getStartTime() == (st + 1) % 3);
}

void TestCases::waveButtonPressTest() {
    int wa = w->getCES()->getWave();
    emit w->waveButton()->pressed();
    QVERIFY(w->getCES()->getWave() == (wa + 1) % 3);
}

void TestCases::freqButtonPressTest() {
    int f = w->getCES()->getFreq();
    emit w->frequencyButton()->pressed();
    QVERIFY(w->getCES()->getFreq() == (f + 1) % 3);
}

void TestCases::startTimeUiTest() {
    setValues();
    int secs = (startTime * 20 + 20) * 60;
    for(int i = 0; i < 3; i ++) {
        if(i == startTime)
            QVERIFY(w->getCES()->getMainScreen()->timerLabels[i]->styleSheet() ==
                    "color: #1b1b1b; font-size: 14pt; text-decoration: underline;");
        else
            QVERIFY(w->getCES()->getMainScreen()->timerLabels[i]->styleSheet() ==
                    "color: #bfbfbf; font-size: 10pt;");
    }
    //check the clock label
    QString mString = QString::number(secs / 60).rightJustified(2, '0');
    QString sString = QString::number(secs % 60).rightJustified(2, '0');
    QVERIFY((w->getCES()->getMainScreen()->clockLabel()->text() == mString + ":" + sString));
}

void TestCases::ampUiTest() {
    setValues();
    for(int i = 0; i < 10; i++) {
        if(i < amps/50)
            QVERIFY(w->getCES()->getMainScreen()->bars[i]->styleSheet() ==
                    "background:  #1b1b1b;");
        else
            QVERIFY(w->getCES()->getMainScreen()->bars[i]->styleSheet() ==
                    "border: 1px solid #1b1b1b;");
    }
}

void TestCases::waveUiTest() {
    setValues();
    for(int i = 0; i < 3; i ++) {
        if(i == wave)
            QVERIFY(w->getCES()->getMainScreen()->waveLabels[i]->styleSheet() ==
                    "color: #1b1b1b; font-size: 10pt; text-decoration: underline;");
        else
            QVERIFY(w->getCES()->getMainScreen()->waveLabels[i]->styleSheet() ==
                    "color: #bfbfbf; font-size: 10pt;");
    }
}

void TestCases::freqUiTest() {
    setValues();
    for(int i = 0; i < 3; i ++) {
        if(i == freq)
            QVERIFY(w->getCES()->getMainScreen()->freqLabels[i]->styleSheet() ==
                    "color: #1b1b1b; font-size: 10pt; text-decoration: underline;");
        else
            QVERIFY(w->getCES()->getMainScreen()->freqLabels[i]->styleSheet() ==
                    "color: #bfbfbf; font-size: 10pt;");
    }
}

void TestCases::amperageOverloadTest() {
    QVERIFY_EXCEPTION_THROWN(w->getCES()->setValue(AMP, 750), AmperageOverloadException);
}
