#include "ces.h"
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

    clockTimer = new Timer(10, 3600);
    idleTimer = new Timer(1000, idleTime);
    batteryTimer = new Timer(500, 196);
    contactTimer = new Timer(1000, 5);

    QThreadPool::globalInstance()->start(clockTimer);
    QThreadPool::globalInstance()->start(idleTimer);
    QThreadPool::globalInstance()->start(batteryTimer);
    QThreadPool::globalInstance()->start(contactTimer);

    connect(clockTimer, &Timer::tick, this, &CES::decrementClock);
    connect(clockTimer, &Timer::end, this, &CES::endTherapy);

    connect(batteryTimer, &Timer::tick, this, &CES::decrementBattery);
    connect(batteryTimer, &Timer::end, this, &CES::shutDown);

    connect(idleTimer, &Timer::end, this, &CES::shutDown);

    connect(this, &CES::stopClock, clockTimer, &Timer::stop);
    connect(this, &CES::startClock, clockTimer, &Timer::start);
    connect(this, &CES::pauseClock, clockTimer, &Timer::pause);

    connect(contactTimer, &Timer::end, this, &CES::setDefaultValues);


}

CES::~CES() {
    clockTimer->stop();
    idleTimer->stop();
    batteryTimer->stop();
    contactTimer->stop();
}

void CES::setTime(int secs) {
    timer = secs;
    mainScreen->updateClock(timer);
}

/*!
    \brief sets the starting time for the therapy and update the
    main screen's selected time and clock
    \param timeIndex - the index of the selected time. Accepted
    values are {0, 1, 2}
 */
void CES::setStartTime(int timeIndex){
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
void CES::setAmperage(int a) {
    selectedAmp = a;
    if(selectedAmp > OVERLOAD_AMP_LIMIT) shutDown();
    mainScreen->updateAmpUi(a);
}

/*!
    \brief sets the frequency for the therapy and update the
    main screen's selected frequency labels
    \param f - the index of the selected frequency. Accepted
    values are {0, 1, 2}
 */
void CES::setFrequency(int f) {
    selectedFreq = f;
    mainScreen->updateFreqUi(selectedFreq);
}

/*!
    \brief sets the wave for the therapy and update the
    main screen's selected wave labels
    \param w - the index of the selected wave. Accepted
    values are {0, 1, 2}
 */
void CES::setWave(int w) {
    selectedWave = w;
    mainScreen->updateWaveUi(selectedWave);
}

void CES::setDefaultValues() {
    setStartTime(SIXTY);
    setWave(ALPHA);
    setFrequency(POINT_FIVE);
    setAmperage(0);
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
    Calls shutDown() or bootUp() depending on the status of power
 */
void CES::togglePower() {
    powerStatus ? shutDown() : bootUp();
}

/*!
 * \brief shuts the system down:
 * 1. sets power to false
 * 2. pauses all timers
 * 3. sets the screen to null
 */
void CES::shutDown() {
    powerStatus = false;
    idleTimer->pause();
    clockTimer->pause();
    batteryTimer->pause();
    contactTimer->pause();
    contactTimer->setTimer(contactTime);
    if(isLocked) toggleLock();
    setScreen();
}


void CES::bootUp() {
    if(batteryLife <= 2) return;
    powerStatus = true;
    setDefaultValues();
    setScreen(mainScreen);
    idleTimer->setTimer(idleTime);
    idleTimer->start();
    if(clipStatus) {
        batteryTimer->start();
        clockTimer->start();
        if(selectedAmp > OVERLOAD_AMP_LIMIT) shutDown();
    }
    if(selectedAmp > OVERLOAD_AMP_LIMIT) shutDown();
}

void CES::toggleClipStatus() {
    clipStatus = !clipStatus;
    if(clipStatus) {
        contactTimer->pause();
        contactTimer->setTimer(contactTime);
        clockTimer->start();
        idleTimer->setTimer(idleTime);
        idleTimer->pause();
        if(powerStatus) {
            batteryTimer->start();
            if(selectedAmp > OVERLOAD_AMP_LIMIT) shutDown();
        }
    }
    else {
        clockTimer->pause();
        if(powerStatus) contactTimer->start();
        idleTimer->start();
        batteryTimer->pause();
    }
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
    if(selectedScreen != logScreen)
        setScreen(logScreen);
    else
        setScreen(mainScreen);
}

void CES::decrementClock() { setTime(timer - 1); }

void CES::endTherapy() {
    if(isRecording) {
        recordings.append(new Recording(selectedTime,  selectedWave, selectedFreq, selectedAmp));
        logScreen->addToLogs(recordings[recordings.size() -1]);
        toggleRecording();
    }
    shutDown();
}

void CES::decrementBattery() {
    batteryLife -= 0.5;
    mainScreen->updateBatteryLifeUi((int)batteryLife);
    mainScreen->updateBatteryIconUi(batteryLife/20);
    if(batteryLife == 5.0) {
        qDebug() << "low battery!";
    }
}

/*!
 *
 * Sends a request to the CES to set the value of time.
 */
void CES::timeButtonPress() {
    idleTimer->setTimer(idleTime);
    if(isLocked || selectedScreen != mainScreen) return;
    setStartTime((selectedTime + 1) % 3);
    //if(clockTimer) clockTimer->stop();
}

/*!
 *
 * Sends a request to the CES to increase the value of amperage.
 */
void CES::upButtonPress() {
    idleTimer->setTimer(idleTime);
    if(isLocked) return;
    if(selectedScreen == mainScreen)
        setAmperage(selectedAmp < 500 ? selectedAmp + 50 : 500);
    if(selectedScreen == logScreen)
        logScreen->moveUp();
}
/*!
 *
 * Sends a request to the CES to decrease the value of amperage.
 */
void CES::downButtonPress() {
    idleTimer->setTimer(idleTime);
    if(isLocked) return;
    if(selectedScreen == mainScreen)
       setAmperage(selectedAmp > 0 ? selectedAmp - 50 : 0);
    else if(selectedScreen == logScreen)
        logScreen->moveDown();
}

/*!
 *
 * Sends a request to the CES to change the value of wave.
 */
void CES::waveButtonPress() {
    idleTimer->setTimer(idleTime);
    if(isLocked || selectedScreen != mainScreen) return;
    setWave((selectedWave + 1) % 3);
}

/*!
 *
 * Sends a request to the CES to decrease the value of frequency.
 */
void CES::freqButtonPress() {
    idleTimer->setTimer(idleTime);
    if(isLocked || selectedScreen != mainScreen) return;
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
    idleTimer->setTimer(idleTime);
    if(selectedScreen != mainScreen) return;
    toggleLock();
}

void CES::logButtonPress() {
    idleTimer->setTimer(idleTime);
    if(isLocked) return;
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
    idleTimer->setTimer(idleTime);
    if(isLocked || selectedScreen != mainScreen) return;
    toggleRecording();
}
