#include "ces.h"
#include "cesexception.h"
#include <QDebug>
#include <QThreadPool>


CES::CES(QLayout *screen, QObject *parent) : QObject(parent)
{

    mainScreen = new MainScreenWidget;
    logScreen = new LoggingWidget;
    mainScreen->hide();
    logScreen->hide();
    screen->addWidget(mainScreen);
    screen->addWidget(logScreen);

    clockTimer = new Timer(CLOCK);
    QThreadPool::globalInstance()->start(clockTimer);

    connect(clockTimer, &Timer::reqDecrementClock, this, &CES::decrementClock);
    connect(this, &CES::stopClock, clockTimer, &Timer::stop);
    connect(this, &CES::startClock, clockTimer, &Timer::start);
    connect(this, &CES::pauseClock, clockTimer, &Timer::pause);

}

CES::~CES() {
    emit stopClock();
}

void CES::setTime(uint16_t secs) {
    if (secs > MAX_TIME) throw IllegalValueException();
    timer = secs;
    mainScreen->updateClock(timer);
    if(timer == 0) togglePower();
}

/*!
    \brief sets the starting time for the therapy and update the
    main screen's selected time and clock
    \param timeIndex - the index of the selected time. Accepted
    values are {0, 1, 2}
 */
void CES::setStartTime(uint16_t timeIndex){
    if(timeIndex > 2) throw IllegalValueException();
    selectedTime = timeIndex;
    timer = (timeIndex * 20 + 20) * 60;
    clockTimer->setTimer(timer);
    mainScreen->updateTimeUi(selectedTime);
}

/*!
    \brief Sets the micro amperage and update the main screen's ui.
    \param a - the desired micro amps value. Accepted values are
    [0-500] in increments of 50.
 */
void CES::setAmperage(uint16_t a) {
    if(a > OVERLOAD_AMP_LIMIT) throw AmperageOverloadException();
    if(a % 50 != 0 || a > MAX_AMPERAGE) throw IllegalValueException();
    microAmps = a;
    mainScreen->updateAmpUi(a);
}

/*!
    \brief sets the frequency for the therapy and update the
    main screen's selected frequency labels
    \param f - the index of the selected frequency. Accepted
    values are {0, 1, 2}
 */
void CES::setFrequency(uint16_t f) {
    if(f > 2) throw IllegalValueException();
    selectedFreq = f;
    mainScreen->updateFreqUi(selectedFreq);
}

/*!
    \brief sets the wave for the therapy and update the
    main screen's selected wave labels
    \param w - the index of the selected wave. Accepted
    values are {0, 1, 2}
 */
void CES::setWave(uint16_t w) {
    if(w > 2) throw IllegalValueException();
    selectedWave = w;
    mainScreen->updateWaveUi(selectedWave);
}

/*!
    \brief Displays the given screen on the MainWindow
    \param w - the widget to be displayed.
    \default nullptr - hides the current display.

    The current shown display is set to CES::selectedScreen
    If nullptr is passed, CES::selectedScreen is set to nullptr
 */
void CES::setScreen(QWidget *w) {
    if(selectedScreen) {
        selectedScreen->hide();
        selectedScreen = nullptr;
    }
    if(w) {
        selectedScreen = w;
        selectedScreen->show();
    }      
}

/*!
    \brief a public function called by the MainWindow to change values
    in the CES
    \param setIndex - the function index (see enum Setter)
    \param val - the value to set
 */

/*!
    \brief toggles the power status of the CES

    If the status is toggled to on, initialize the default values and sets the screen to mainScreen
    Ff status is toggled to off, unset the current screen on the MainWindow UI.
 */
void CES::togglePower() {
    powerStatus = !powerStatus;
    if(powerStatus) {
        //isLocked = false;
        setStartTime(SIXTY);
        setWave(ALPHA);
        setFrequency(POINT_FIVE);
        setAmperage(0);
        setScreen(mainScreen);
        if(clipStatus) emit startClock();
    }
    else {
        emit pauseClock();
        setScreen();
        if(isRecording) {
            recordings.append(new Recording(selectedTime,  selectedWave, selectedFreq, microAmps));
            logScreen->addToLogs(recordings[recordings.size() -1]);
            toggleRecording();
        }
    }
}

void CES::toggleClipStatus() {
    clipStatus = !clipStatus;
    if(clipStatus) emit startClock();
    else emit pauseClock();
}

void CES::toggleLock() {
    isLocked = !isLocked;
    mainScreen->showLock(isLocked);
}

void CES::toggleRecording() {
    isRecording = !isRecording;
    mainScreen->showRecordIcon(isRecording);
}

void CES::showLogScreen() {
    if(!powerStatus) return;
    if(selectedScreen != logScreen)
        setScreen(logScreen);
    else
        setScreen(mainScreen);
}

void CES::decrementClock() { setTime(timer - 1); }

/*!
 *
 * Sends a request to the CES to set the value of time.
 */
void CES::timeButtonPress() {
    setStartTime((selectedTime + 1) % 3);
    //if(clockTimer) clockTimer->stop();
}

/*!
 *
 * Sends a request to the CES to increase the value of amperage.
 */
void CES::upButtonPress() {
    if(selectedScreen == mainScreen)
        setAmperage(microAmps < 500 ? microAmps + 50 : 500);
    if(selectedScreen == logScreen)
        logScreen->moveUp();
}
/*!
 *
 * Sends a request to the CES to decrease the value of amperage.
 */
void CES::downButtonPress() {
if(selectedScreen == mainScreen)
   setAmperage(microAmps > 0 ? microAmps - 50 : 0);
if(selectedScreen == logScreen)
    logScreen->moveDown();
}

/*!
 *
 * Sends a request to the CES to change the value of wave.
 */
void CES::waveButtonPress() {
    setWave((selectedWave + 1) % 3);
}

/*!
 *
 * Sends a request to the CES to decrease the value of frequency.
 */
void CES::freqButtonPress() {
    setFrequency((selectedFreq + 1) % 3);
}

/*!
 *
 * Sends a request to the CES to toggle the power status.
 */
void CES::powerButtonPress() {
    togglePower();
}

/*!
 *
 * Sends a request to the CES to toggle the clip status.
 */
void CES::clipperButtonPress() {
    toggleClipStatus();
}

/*!
 *
 * Sends a request to the CES to toggle the lock status.
 */
void CES::lockButtonPress() {
    toggleLock();
}

void CES::logButtonPress() {
    if(selectedScreen == mainScreen) setScreen(logScreen);
    else {
        if(logScreen->selectedIndex != 0) {
            setStartTime(recordings[logScreen->selectedIndex - 3]->selectedTime);
            setAmperage(recordings[logScreen->selectedIndex - 3]->selectedAmps);
            setWave(recordings[logScreen->selectedIndex - 3]->selectedWave);
            setFrequency(recordings[logScreen->selectedIndex - 3]->selectedFreq);
        }
        setScreen(mainScreen);
    }
}

void CES::recordButtonPress() {
    toggleRecording();
}
