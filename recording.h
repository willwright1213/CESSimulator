#ifndef RECORDING_H
#define RECORDING_H

#include <QObject>

class Recording : public QObject
{
    Q_OBJECT
public:
    explicit Recording(QObject *parent = nullptr);

signals:

};

#endif // RECORDING_H
