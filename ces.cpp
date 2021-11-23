#include "ces.h"

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

    selectedScreen = nullptr;
}

int CES::time() const & {return selectedTime;}
int CES::wave() const & {return selectedWave;}
int CES::freq() const & {return selectedFreq;}
int CES::amps() const & {return microAmps;}

void CES::setTime(int secs) {
    timer = secs;
    mainScreen->updateClock(timer);
}

void CES::setStartTime(int timeIndex){
    selectedTime = timeIndex;
    timer = (timeIndex * 20 + 20) * 60;
    mainScreen->updateTimeUi(selectedTime);
}

void CES::setAmperage(int a) {
    microAmps = a;
    mainScreen->updateAmpUi(a);
}

void CES::setFrequency(int f) {
    selectedFreq = f;
    mainScreen->updateFreqUi(selectedFreq);
}

void CES::setWave(int w) {
    selectedWave = w;
    mainScreen->updateWaveUi(selectedWave);
}

void CES::setScreen(QWidget *w) {
    if(selectedScreen) selectedScreen->hide();
    if(w) {
        selectedScreen = w;
        selectedScreen->show();
    }
}


void CES::changeValue(int setIndex, int val) {
    if(isLocked || !powerStatus) return;
    (this->*funcs[setIndex])(val);
}

void CES::togglePower() {
    powerStatus = !powerStatus;
    if(powerStatus) {
        isLocked = false;
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
}

