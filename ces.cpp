#include "ces.h"

CES::CES(QObject *parent) : QObject(parent)
{
    mainScreen = new MainScreenWidget;
    logScreen = new LoggingWidget;
    //add function pointers to vector
    funcs.append(&CES::setTime);
    funcs.append(&CES::setAmperage);
    funcs.append(&CES::setWave);
    funcs.append(&CES::setFrequency);

    selectedScreen = nullptr;
}

int CES::time() const {return selectedTime;}
int CES::wave() const {return selectedWave;}
int CES::freq() const {return selectedFreq;}
int CES::amps() const {return microAmps;}

void CES::setTime(int newTime) {
    selectedTime = newTime;
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

void CES::loadScreens() {
    emit loadScreen(mainScreen);
}

void CES::changeValue(int setIndex, int val) {
    if(isLocked || !powerStatus) return;
    (this->*funcs[setIndex])(val);
}

void CES::togglePower() {
    powerStatus = !powerStatus;
    if(powerStatus) {
        isLocked = false;
        setTime(SIXTY);
        setWave(ALPHA);
        setFrequency(POINT_FIVE);
        setAmperage(0);
        emit selectScreen(mainScreen);
    }
    else {
        emit selectScreen();
    }
    emit unlockButtons(powerStatus);
}

void CES::toggleClipStatus() {
    clipStatus = !clipStatus;
}

void CES::toggleLock() {
    isLocked = !isLocked;
}

