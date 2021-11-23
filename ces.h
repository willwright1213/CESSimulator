#ifndef CES_H
#define CES_H

#include <QObject>
#include <QPointer>
#include <QLayout>
#include "mainscreenwidget.h"
#include "loggingwidget.h"

typedef enum {TWENTY, FOURTY, SIXTY} SelectedTime;
typedef enum {POINT_FIVE, SEVENTY_SEVEN, HUNDRED} selectedFrequency;
typedef enum {ALPHA, BETA, GAMMA} SelectedWave;
typedef enum {TIME, AMP, WAVE, FREQ} Setter;


class CES : public QObject
{
    Q_OBJECT
public:
    explicit CES(QLayout *screen, QObject *parent = nullptr);
    typedef  void (CES::*FuncP)(int);
private:
    bool isLocked = true;
    bool powerStatus = false;
    bool clipStatus = false;
    int timer;
    int selectedTime;
    int selectedWave;
    int selectedFreq;
    int microAmps;
    MainScreenWidget *mainScreen;
    LoggingWidget *logScreen;
    QVector<void (CES::*)(int)> funcs;
    void setTime(int);
    void setStartTime(int);
    void setAmperage(int);
    void setFrequency(int);
    void setWave(int);
    void setScreen(QWidget *w = nullptr);

public:
    QPointer<QWidget> selectedScreen;
    int time() const &;
    int wave() const &;
    int freq() const &;
    int amps() const &;
    void changeValue(int setIndex, int val);
    void togglePower();
    void toggleClipStatus();
    void toggleLock();


signals:
    void updateTimeUi(int);
    void updateWaveUi(int);
    void updateFreqUi(int);
    void updateAmpUi(int);


public slots:

};

#endif // CES_H
