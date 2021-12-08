#ifndef RECORDING_H
#define RECORDING_H

#include <QObject>

class Recording : public QObject
{
    Q_OBJECT
    friend class CES;
public:
    explicit Recording(unsigned int, unsigned int, unsigned int, unsigned int, QObject *parent = nullptr);

public:
    QString date;
    unsigned int selectedTime;
    unsigned int selectedWave;
    unsigned int selectedFreq;
    unsigned int selectedAmps;

signals:

};

#endif // RECORDING_H
