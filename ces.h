#ifndef CES_H
#define CES_H

#include <QObject>
#include <QPointer>
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
    explicit CES(QObject *parent = nullptr);
    typedef  void (CES::*FuncP)(int);
private:
    bool isLocked = true;
    bool powerStatus = false;
    bool clipStatus = false;
    int selectedTime;
    int selectedWave;
    int selectedFreq;
    int microAmps;
    MainScreenWidget *mainScreen;
    LoggingWidget *logScreen;
    QVector<void (CES::*)(int)> funcs;


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
    void loadScreens();

private:
    void setTime(int);
    void setAmperage(int);
    void setFrequency(int);
    void setWave(int);

signals:
    void updateTimeUi(int);
    void updateWaveUi(int);
    void updateFreqUi(int);
    void updateAmpUi(int);
    void unlockButtons(bool);
    void loadScreen(QWidget *screen = nullptr);
    void selectScreen(QWidget *screen = nullptr);

public slots:

};

#endif // CES_H
