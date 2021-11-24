#include "ces.h"
#include "cesexception.h"
#include <QDebug>

CES::CES(QLayout *screen, QObject *parent) : QObject(parent)
{
    mainScreen = new MainScreenWidget;
    logScreen = new LoggingWidget;
    mainScreen->hide();
    logScreen->hide();
    screen->addWidget(mainScreen);
    screen->addWidget(logScreen);

    funcs.append(&CES::setStartTime);
    funcs.append(&CES::setAmperage);
    funcs.append(&CES::setWave);
    funcs.append(&CES::setFrequency);
}

/*!
    \return selectedTime's label index.
 */
uint8_t CES::getStartTime() const & {return selectedTime;}
uint16_t CES::getTime() const & {return timer;}
uint8_t CES::getWave() const & {return selectedWave;}
uint8_t CES::getFreq() const & {return selectedFreq;}
uint16_t CES::getAmps() const & {return microAmps;}
bool CES::getPowerStatus() const & {return powerStatus;}
bool CES::getClipStatus() const & {return clipStatus;}
bool CES::getlockStatus() const & {return isLocked;}
QPointer<QWidget> CES::getSelectedScreen() const { return selectedScreen;}
MainScreenWidget * CES::getMainScreen() const {return mainScreen;}
/*!
 * \brief sets the Timer and updates the main screen's Clock
 * \param secs  - the time in seconds

    The accepted values are [0-3600]
 */
void CES::setTime(uint16_t secs) {
    if (secs > 3600) throw IllegalValueException();
    timer = secs;
    mainScreen->updateClock(timer);
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
    mainScreen->updateTimeUi(selectedTime);
}

/*!
    \brief Sets the micro amperage and update the main screen's ui.
    \param a - the desired micro amps value. Accepted values are
    [0-500] in increments of 50.
 */
void CES::setAmperage(uint16_t a) {
    if(a > 700) throw AmperageOverloadException();
    if(a % 50 != 0) throw IllegalValueException();
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
void CES::setValue(uint8_t setIndex, uint16_t val) {
    if (setIndex > 3) throw IllegalValueException();
    if(isLocked || !powerStatus) return;
    (this->*funcs[setIndex])(val);
}

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
    }
    else {
        setScreen();
    }
}

void CES::toggleClipStatus() {
    clipStatus = !clipStatus;
}

void CES::toggleLock() {
    isLocked = !isLocked;
    mainScreen->showLock(isLocked);
}

