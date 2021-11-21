#include "ces.h"

CES::CES(QObject *parent) : QObject(parent)
{
    powerStatus = false;
    mainScreen = new MainScreenWidget;
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

void CES::togglePower() {
    powerStatus = !powerStatus;
    if(powerStatus) {
        setTime(SIXTY);
        setWave(ALPHA);
        setFrequency(POINT_FIVE);
        setAmperage(0);
        emit loadScreen(mainScreen);
    }
    else {
        emit loadScreen(nullptr);
    }
    emit unlockButtons(powerStatus);
}


