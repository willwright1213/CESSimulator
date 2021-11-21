#ifndef CES_H
#define CES_H

#include <QObject>
#include "mainscreenwidget.h"
#include "loggingwidget.h"

typedef enum {TWENTY, FOURTY, SIXTY} SelectedTime;
typedef enum {POINT_FIVE, SEVENTY_SEVEN, HUNDRED} selectedFrequency;
typedef enum {ALPHA, BETA, GAMMA} SelectedWave;


class CES : public QObject
{
    Q_OBJECT
public:
    explicit CES(QObject *parent = nullptr);

private:
    bool onStatus;
    int selectedTime;
    int selectedWave;
    int selectedFreq;
    int microAmps;
    bool powerStatus;
    bool clipperStatus;
    MainScreenWidget *mainScreen;
    LoggingWidget *logScreen;
    QWidget *selectedScreen;

public:
    int time() const;
    int wave() const;
    int freq() const;
    int amps() const;
    void setTime(int);
    void setAmperage(int);
    void setFrequency(int);
    void setWave(int);
    void togglePower();
    void loadScreens();


signals:
    void updateTimeUi(int);
    void updateWaveUi(int);
    void updateFreqUi(int);
    void updateAmpUi(int);
    void unlockButtons(bool);
    void loadScreen(QWidget *screen);
    void selectScreen(QWidget *screen = nullptr);

public slots:

};

#endif // CES_H
