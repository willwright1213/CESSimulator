#include "ces.h"

CES::CES(QObject *parent) : QObject(parent)
{
    powerStatus = false;
}

int CES::time() const {return selectedTime;}
int CES::wave() const {return selectedWave;}
int CES::freq() const {return selectedFreq;}
int CES::amps() const {return microAmps;}

void CES::setTime(int newTime) {
    selectedTime = newTime;
    emit updateTimeUi(selectedTime);
}

void CES::setAmperage(int a) {
    microAmps = a;
    emit updateAmpUi(microAmps);
}

void CES::setFrequency(int f) {
    selectedFreq = f;
    emit updateFreqUi(selectedFreq);
}

void CES::setWave(int w) {
    selectedWave = w;
    emit updateWaveUi(selectedWave);
}

void CES::togglePower() {
    powerStatus = !powerStatus;
    if(powerStatus) {
        setTime(SIXTY);
        setWave(ALPHA);
        setFrequency(POINT_FIVE);
        setAmperage(0);
    }
    emit initializeUi(powerStatus);
}


