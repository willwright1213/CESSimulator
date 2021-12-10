#include "recording.h"
#include <QDateTime>

Recording::Recording(unsigned int st, unsigned int sw,
                     unsigned int sf, unsigned int sa,
                     QObject *parent) : QObject(parent),
    selectedTime(st), selectedWave(sw), selectedFreq(sf), selectedAmps(sa)
{
    date = QDateTime::currentDateTime().toString("yy/MM/dd hh:mm");
}

